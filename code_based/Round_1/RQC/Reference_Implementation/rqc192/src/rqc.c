/** 
 * \file rqc.c
 * \brief Implementation of rqc.h
 */

#include "parameters.h"
#include "rqc.h"
#include "gabidulin.h"
#include "parsing.h"
#include "ffi_field.h"
#include "ffi_elt.h"
#include "ffi_vec.h"


/** 
 * \fn void rqc_pke_keygen(unsigned char* pk, unsigned char* sk)
 * \brief Keygen of the RQC_PKE IND-CPA scheme
 *
 * The public key is composed of the syndrom s as well as the seed used to generate vectors g and h.
 *
 * The secret key is composed of the seed used to generate vectors x and y.
 * As a technicality, the public key is appended to the secret key in order to respect the NIST API.
 *
 * \param[out] pk String containing the public key
 * \param[out] sk String containing the secret key
 */
void rqc_pke_keygen(unsigned char* pk, unsigned char* sk) {

  // Create seed expanders for public key and secret key
  unsigned char sk_seed[SEEDEXPANDER_SEED_BYTES];
  randombytes(sk_seed, SEEDEXPANDER_SEED_BYTES);
  AES_XOF_struct* sk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  unsigned char pk_seed[SEEDEXPANDER_SEED_BYTES];
  randombytes(pk_seed, SEEDEXPANDER_SEED_BYTES);
  AES_XOF_struct* pk_seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(pk_seedexpander, pk_seed, pk_seed + 32, SEEDEXPANDER_MAX_LENGTH);

  ffi_field field;
  ffi_field_init(field);

  // Compute secret key
  ffi_vec x, y, support_w;
  ffi_vec_init(field, &x, PARAM_N);
  ffi_vec_init(field, &y, PARAM_N);
  ffi_vec_init(field, &support_w, PARAM_W);

  ffi_vec_set_random_full_rank_with_one(field, support_w, PARAM_W, sk_seedexpander);
  ffi_vec_set_random_from_support(field, x, PARAM_N, support_w, PARAM_W, sk_seedexpander);
  ffi_vec_set_random_from_support(field, y, PARAM_N, support_w, PARAM_W, sk_seedexpander);

  // Compute public key
  ffi_vec g, h, s;
  ffi_vec_init(field, &g, PARAM_N);
  ffi_vec_init(field, &h, PARAM_N);
  ffi_vec_init(field, &s, PARAM_N);

  ffi_vec_set_random_full_rank(field, g, PARAM_N, pk_seedexpander);
  ffi_vec_set_random(field, h, PARAM_N, pk_seedexpander); 
  
  ffi_vec_mul(field, s, h, y, PARAM_N);
  ffi_vec_add(field, s, s, x, PARAM_N);

  // Parse keys to string
  rqc_public_key_to_string(pk, s, pk_seed);
  rqc_secret_key_to_string(sk, sk_seed, pk);

  #ifdef VERBOSE
    printf("\n\nsk_seed: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", sk_seed[i]);
    printf("\n\nsupport_w: "); ffi_vec_print(field, support_w, PARAM_W);
    printf("\n\nx: "); ffi_vec_print(field, x, PARAM_N);
    printf("\n\ny: "); ffi_vec_print(field, y, PARAM_N);

    printf("\n\npk_seed: "); for(int i = 0 ; i < SEEDEXPANDER_SEED_BYTES ; ++i) printf("%02x", pk_seed[i]);
    printf("\n\ng: "); ffi_vec_print(field, g, PARAM_N);
    printf("\n\nh: "); ffi_vec_print(field, h, PARAM_N);
    printf("\n\ns: "); ffi_vec_print(field, s, PARAM_N);

    printf("\n\nsk: "); for(int i = 0 ; i < SECRET_KEY_BYTES ; ++i) printf("%02x", sk[i]);
    printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
  #endif

  ffi_vec_clear(field, support_w, PARAM_W);
  ffi_vec_clear(field, x, PARAM_N);
  ffi_vec_clear(field, y, PARAM_N);
  ffi_vec_clear(field, g, PARAM_N);
  ffi_vec_clear(field, h, PARAM_N);
  ffi_vec_clear(field, s, PARAM_N);
  ffi_field_clear(field);
  free(pk_seedexpander);
  free(sk_seedexpander);
}



/** 
 * \fn void rqc_pke_encrypt(ffi_vec u, ffi_vec v, const ffi_vec m, unsigned char* theta, const unsigned char* pk)
 * \brief Encryption of the RQC_PKE IND-CPA scheme
 *
 * The ciphertext is composed of the vectors u and v.
 *
 * \param[out] u Vector u (first part of the ciphertext)
 * \param[out] v Vector v (second part of the ciphertext)
 * \param[in] m Vector representing the message to encrypt
 * \param[in] theta Seed used to derive randomness required for encryption
 * \param[in] pk String containing the public key
 */
void rqc_pke_encrypt(ffi_vec u, ffi_vec v, const ffi_vec m, unsigned char* theta, const unsigned char* pk) {

  // Create seed_expander from theta
  AES_XOF_struct* seedexpander = (AES_XOF_struct*) malloc(sizeof(AES_XOF_struct));
  seedexpander_init(seedexpander, theta, theta + 32, SEEDEXPANDER_MAX_LENGTH);

  ffi_field field;
  ffi_field_init(field);

  // Retrieve g, h and s from public key
  ffi_vec g, h,s ;
  ffi_vec_init(field, &g, PARAM_N);
  ffi_vec_init(field, &h, PARAM_N);
  ffi_vec_init(field, &s, PARAM_N);

  rqc_public_key_from_string(g, h, s, field, pk);

  // Generate r1, r2 and e
  ffi_vec r1, r2, e, support_r;
  ffi_vec_init(field, &support_r, PARAM_R);
  ffi_vec_init(field, &r1, PARAM_N);
  ffi_vec_init(field, &r2, PARAM_N);
  ffi_vec_init(field, &e, PARAM_N);

  ffi_vec_set_random_full_rank(field, support_r, PARAM_R, seedexpander);
  ffi_vec_set_random_from_support(field, r1, PARAM_N, support_r, PARAM_R, seedexpander);
  ffi_vec_set_random_from_support(field, r2, PARAM_N, support_r, PARAM_R, seedexpander);
  ffi_vec_set_random_from_support(field, e, PARAM_N, support_r, PARAM_R, seedexpander);

  // Compute u = r1 + h.r2
  ffi_vec_mul(field, u, h, r2, PARAM_N);
  ffi_vec_add(field, u, u, r1, PARAM_N);

  // Compute v = m.G by encoding the message
  gabidulin_code* code = gabidulin_code_init(field, g, PARAM_K, PARAM_N);
  gabidulin_code_encode(v, code, m);

  // Compute v = m.G + s.r2 + e
  ffi_vec tmp;
  ffi_vec_init(field, &tmp, PARAM_N);
  ffi_vec_set_zero(field, tmp, PARAM_N);

  ffi_vec_mul(field, tmp, s, r2, PARAM_N);
  ffi_vec_add(field, tmp, tmp, e, PARAM_N);
  ffi_vec_add(field, v, v, tmp, PARAM_N);

  #ifdef VERBOSE
    printf("\n\nh: "); ffi_vec_print(field, h, PARAM_N);
    printf("\n\ns: "); ffi_vec_print(field, s, PARAM_N);
    printf("\n\nsupport_r: "); ffi_vec_print(field, support_r, PARAM_R);
    printf("\n\nr1: "); ffi_vec_print(field, r1, PARAM_N);
    printf("\n\nr2: "); ffi_vec_print(field, r2, PARAM_N);
    printf("\n\ne: "); ffi_vec_print(field, e, PARAM_N);

    printf("\n\nu: "); ffi_vec_print(field, u, PARAM_N);
    printf("\n\nv: "); ffi_vec_print(field, v, PARAM_N);
  #endif

  ffi_vec_clear(field, g, PARAM_N);
  ffi_vec_clear(field, h, PARAM_N);
  ffi_vec_clear(field, s, PARAM_N);
  ffi_vec_clear(field, support_r, PARAM_N);
  ffi_vec_clear(field, r1, PARAM_N);
  ffi_vec_clear(field, r2, PARAM_N);
  ffi_vec_clear(field, e, PARAM_N);
  ffi_vec_clear(field, tmp, PARAM_N);
  gabidulin_code_clear(code);
  ffi_field_clear(field);
  free(seedexpander);
}



/** 
 * \fn void rqc_pke_decrypt(ffi_vec m, const ffi_vec u, const ffi_vec v, const unsigned char* sk)
 * \brief Decryption of the RQC_PKE IND-CPA scheme
 *
 * \param[out] m Vector representing the decrypted message
 * \param[in] u Vector u (first part of the ciphertext)
 * \param[in] v Vector v (second part of the ciphertext)
 * \param[in] sk String containing the secret key
 */
void rqc_pke_decrypt(ffi_vec m, const ffi_vec u, const ffi_vec v, const unsigned char* sk) {
  ffi_field field;
  ffi_field_init(field);

  // Retrieve x, y, g, h and s from secret key
  ffi_vec x, y;
  ffi_vec_init(field, &x, PARAM_N);
  ffi_vec_init(field, &y, PARAM_N);

  ffi_vec g, h, s; 
  ffi_vec_init(field, &g, PARAM_N);
  ffi_vec_init(field, &h, PARAM_N);
  ffi_vec_init(field, &s, PARAM_N);

  unsigned char pk[PUBLIC_KEY_BYTES];

  rqc_secret_key_from_string(x, y, pk, field, sk);
  rqc_public_key_from_string(g, h, s, field, pk);

  // Compute v - u.y
  ffi_vec tmp;
  ffi_vec_init(field, &tmp, PARAM_N);
  ffi_vec_set_zero(field, tmp, PARAM_N);

  ffi_vec_mul(field, tmp, u, y, PARAM_N);
  // ffi_vec_neg(field, tmp, tmp, PARAM_N);
  ffi_vec_add(field, tmp, v, tmp, PARAM_N);

  #ifdef VERBOSE
    printf("\n\nu: "); ffi_vec_print(field, u, PARAM_N);
    printf("\n\nv: "); ffi_vec_print(field, v, PARAM_N);
    printf("\n\ny: "); ffi_vec_print(field, y, PARAM_N);
    printf("\n\nv - u.y: "); ffi_vec_print(field, tmp, PARAM_N);
  #endif

  // Compute m by decoding v - u.y
  gabidulin_code* code = gabidulin_code_init(field, g, PARAM_K, PARAM_N);
  gabidulin_code_decode(m, code, tmp);

  ffi_vec_clear(field, x, PARAM_N);
  ffi_vec_clear(field, y, PARAM_N);
  ffi_vec_clear(field, g, PARAM_N);
  ffi_vec_clear(field, h, PARAM_N);
  ffi_vec_clear(field, s, PARAM_N);
  ffi_vec_clear(field, tmp, PARAM_N);
  gabidulin_code_clear(code);
  ffi_field_clear(field);
}

