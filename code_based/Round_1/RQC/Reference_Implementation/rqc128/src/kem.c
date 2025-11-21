/** 
 * \file kem.c
 * \brief Implementation of api.h
 */

#include "hash.h"
#include "api.h"
#include "parameters.h"
#include "rqc.h"
#include "parsing.h"
#include "ffi_field.h"
#include "ffi_vec.h"


/** 
 * \fn int crypto_kem_keypair(unsigned char* pk, unsigned char* sk)
 * \brief Keygen of the RQC_KEM IND-CCA2 scheme
 *
 * The public key is composed of the syndrom <b>s</b> as well as the seed used to generate vectors <b>g</b> and <b>h</b>.
 *
 * The secret key is composed of the seed used to generate the vectors <b>x</b> and <b>y</b>.
 * As a technicality, the public key is appended to the secret key in order to respect the NIST API.
 *
 * \param[out] pk String containing the public key
 * \param[out] sk String containing the secret key
 * \return 0 if keygen is sucessfull
 */
int crypto_kem_keypair(unsigned char* pk, unsigned char* sk) {
  #ifdef VERBOSE
    printf("\n\n\n### KEYGEN ###");
  #endif

  rqc_pke_keygen(pk, sk);
  return 0;
}



/** 
 * \fn int crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk)
 * \brief Encapsulation of the RQC_KEM IND-CCA2 scheme
 *
 * \param[out] ct String containing the ciphertext
 * \param[out] ss String containing the shared secret
 * \param[in] pk String containing the public key
 * \return 0 if encapsulation is sucessfull
 */
int crypto_kem_enc(unsigned char* ct, unsigned char* ss, const unsigned char* pk) {
  #ifdef VERBOSE
    printf("\n\n\n\n### ENCAPS ###");
  #endif

  ffi_field field;
  ffi_field_init(field);

  // Computing m
  ffi_vec m;
  ffi_vec_init(field, &m, PARAM_K);
  ffi_vec_set_random2(field, m, PARAM_K);

  // Generating G function
  unsigned char seed_G[VEC_K_BYTES];
  ffi_vec_to_string(seed_G, m, PARAM_K);
  AES_XOF_struct* G_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(G_seedexpander, seed_G, seed_G + 32, SEEDEXPANDER_MAX_LENGTH);

  // Computing theta
  unsigned char theta[SEEDEXPANDER_SEED_BYTES];
  seedexpander(G_seedexpander, theta, SEEDEXPANDER_SEED_BYTES);

  #ifdef VERBOSE
    printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
    printf("\n\nm: "); ffi_vec_print(field, m, PARAM_K);
    printf("\n\ntheta: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", theta[i]);
  #endif

  // Encrypting m
  ffi_vec u, v;
  ffi_vec_init(field, &u, PARAM_N);
  ffi_vec_init(field, &v, PARAM_N);
  rqc_pke_encrypt(u, v, m, theta, pk);

  // Computing d
  unsigned char d[SHA512_BYTES];
  sha512(d, (unsigned char*) m, FFI_VEC_K_BYTES);

  // Computing ciphertext
  rqc_kem_ciphertext_to_string(ct, u, v, d);
  
  // Computing shared secret
  unsigned char mc[FFI_VEC_K_BYTES + 2 * FFI_VEC_N_BYTES];
  memcpy(mc, (unsigned char*) m, FFI_VEC_K_BYTES);
  memcpy(mc + FFI_VEC_K_BYTES, (unsigned char*) u, FFI_VEC_N_BYTES);
  memcpy(mc + FFI_VEC_K_BYTES + FFI_VEC_N_BYTES, (unsigned char*) v, FFI_VEC_N_BYTES);
  sha512(ss, mc, FFI_VEC_K_BYTES + 2 * FFI_VEC_N_BYTES);

  #ifdef VERBOSE
    printf("\n\nd: "); for(int i = 0 ; i < SHA512_BYTES ; ++i) printf("%02x", d[i]);
    printf("\n\nciphertext: "); for(int i = 0 ; i < CIPHERTEXT_BYTES ; ++i) printf("%02x", ct[i]);
    printf("\n\nsecret 1: "); for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%02x", ss[i]);
  #endif
  
  ffi_vec_clear(field, m, PARAM_K);
  ffi_vec_clear(field, u, PARAM_N);
  ffi_vec_clear(field, v, PARAM_N);
  free(G_seedexpander);
  ffi_field_clear(field);

  return 0;
}



/** 
 * \fn int crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk)
 * \brief Decapsulation of the RQC_KEM IND-CCA2 scheme
 *
 * \param[out] ss String containing the shared secret
 * \param[in] ct String containing the ciphertext
 * \param[in] sk String containing the secret key
 * \return 0 if decapsulation is successfull, -1 otherwise
 */
int crypto_kem_dec(unsigned char* ss, const unsigned char* ct, const unsigned char* sk) {
  #ifdef VERBOSE
    printf("\n\n\n\n### DECAPS ###");
  #endif

  ffi_field field;
  ffi_field_init(field);

  // Retrieving u, v and d from ciphertext
  ffi_vec u, v;
  ffi_vec_init(field, &u, PARAM_N);
  ffi_vec_init(field, &v, PARAM_N);
  unsigned char d[SHA512_BYTES];
  rqc_kem_ciphertext_from_string(u, v, d, ct);

  // Retrieving pk from sk
  unsigned char pk[PUBLIC_KEY_BYTES];
  memcpy(pk, sk + SEEDEXPANDER_SEED_BYTES, PUBLIC_KEY_BYTES);

  #ifdef VERBOSE
    printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
    printf("\n\nsk: "); for(int i = 0 ; i < SECRET_KEY_BYTES ; ++i) printf("%02x", sk[i]);
    printf("\n\nciphertext: "); for(int i = 0 ; i < CIPHERTEXT_BYTES ; ++i) printf("%02x", ct[i]);
  #endif

  // Decrypting
  ffi_vec m;
  ffi_vec_init(field, &m, PARAM_K);
  rqc_pke_decrypt(m, u, v, sk);

  // Generating G function
  unsigned char seed_G[VEC_K_BYTES];
  ffi_vec_to_string(seed_G, m, PARAM_K);
  AES_XOF_struct* G_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(G_seedexpander, seed_G, seed_G + 32, SEEDEXPANDER_MAX_LENGTH);

  // Computing theta
  unsigned char theta[SEEDEXPANDER_SEED_BYTES];
  seedexpander(G_seedexpander, theta, SEEDEXPANDER_SEED_BYTES);

  #ifdef VERBOSE
    printf("\n\ntheta: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", theta[i]);
    printf("\n\n## Checking Ciphertext- Begin ##");
  #endif

  // Encrypting m'
  ffi_vec u2, v2;
  ffi_vec_init(field, &u2, PARAM_N);
  ffi_vec_init(field, &v2, PARAM_N);
  rqc_pke_encrypt(u2, v2, m, theta, pk);

  // Checking that c = c' and abort otherwise
  int abort = 0;
  if(ffi_vec_is_equal_to(field, u, u2, PARAM_N) == 0 || ffi_vec_is_equal_to(field, v, v2, PARAM_N) == 0) {
    abort = 1;
  }

  // Computing d'
  unsigned char d2[SHA512_BYTES];
  sha512(d2, (unsigned char*) m, FFI_VEC_K_BYTES);

  // Checking that d = d' and abort otherwise
  if(memcmp(d, d2, SHA512_BYTES) != 0) {
    abort = 1;
  }

  #ifdef VERBOSE
    printf("\n\nu2: "); ffi_vec_print(field, u2, PARAM_N);
    printf("\n\nv2: "); ffi_vec_print(field, v2, PARAM_N);
    printf("\n\nd2: "); for(int i = 0 ; i < SHA512_BYTES ; ++i) printf("%02x", d2[i]);
  #endif

  if(abort == 1) {
    #ifdef VERBOSE
      printf("\n\nCheck result : ABORT");
      printf("\n\n## Checking Ciphertext - End ##");
    #endif

    memset(ss, 0, SHARED_SECRET_BYTES);
    return -1;
  }

  // Computing shared secret
  unsigned char mc[FFI_VEC_K_BYTES + 2 * FFI_VEC_N_BYTES];
  memcpy(mc, m, FFI_VEC_K_BYTES);
  memcpy(mc + FFI_VEC_K_BYTES, (unsigned char*) u, FFI_VEC_N_BYTES);
  memcpy(mc + FFI_VEC_K_BYTES + FFI_VEC_N_BYTES, (unsigned char*) v, FFI_VEC_N_BYTES);
  sha512(ss, mc, FFI_VEC_K_BYTES + 2 * FFI_VEC_N_BYTES);

  #ifdef VERBOSE
    printf("\n\nCheck result: SUCCESS");
    printf("\n\n## Checking Ciphertext - End ##");
  #endif

  ffi_vec_clear(field, m, PARAM_K);
  ffi_vec_clear(field, u, PARAM_N);
  ffi_vec_clear(field, v, PARAM_N);
  ffi_vec_clear(field, u2, PARAM_N);
  ffi_vec_clear(field, v2, PARAM_N);
  free(G_seedexpander);
  ffi_field_clear(field);

  return 0;
}

