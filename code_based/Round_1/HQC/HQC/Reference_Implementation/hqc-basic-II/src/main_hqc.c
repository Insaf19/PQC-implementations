#include <stdio.h>
#include <time.h>
#include <string.h>


#include "api.h"
#include "parameters.h"

long long cpucycles(void) {
  unsigned long long result;
  __asm__ volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax" : "=a" (result) ::  "%rdx");
  return result;
}

int main() {
  printf("\n");
  printf("*******************\n");
  printf("**** HQC-%d-%d ***\n", PARAM_SECURITY, PARAM_DFR_EXP);
  printf("*******************\n");

  printf("\n");
  printf("N: %d   ", PARAM_N);
  printf("N1: %d   ", PARAM_N1);
  printf("N2: %d   ", PARAM_N2);
  printf("OMEGA: %d   ", PARAM_OMEGA);
  printf("OMEGA_R: %d   ", PARAM_OMEGA_R);
  

  printf("\n\nSecurity: %d bits", PARAM_SECURITY);
  printf("\nFailure rate: %d", PARAM_DFR_EXP);

  printf("\n");

  unsigned char pk[PUBLIC_KEY_BYTES];
  unsigned char sk[SECRET_KEY_BYTES];

  unsigned char ct[CIPHERTEXT_BYTES];
  unsigned char key1[SHARED_SECRET_BYTES];
  unsigned char key2[SHARED_SECRET_BYTES];


  #ifndef VERBOSE
    printf("\n\n### Execution 1\n\n");

    clock_t t_keygen_1 = clock();
    crypto_kem_keypair(pk, sk);
    clock_t t_keygen_2 = clock();

    clock_t t_encaps_1 = clock();
    crypto_kem_enc(ct, key1, pk);
    clock_t t_encaps_2 = clock();
 
    clock_t t_decaps_1 = clock();
    crypto_kem_dec(key2, ct, sk);
    clock_t t_decaps_2 = clock();

    printf("Keygen: %.2f ms\n", 1000 * (t_keygen_2 - t_keygen_1) / (double) CLOCKS_PER_SEC);
    printf("Encaps: %.2f ms\n", 1000 * (t_encaps_2 - t_encaps_1) / (double) CLOCKS_PER_SEC);
    printf("Decaps: %.2f ms\n", 1000 * (t_decaps_2 - t_decaps_1) / (double) CLOCKS_PER_SEC);

    printf("\n\nsecret1: ");
    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key1[i]);

    printf("\nsecret2: ");
    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key2[i]);
    printf("\n\n");

    printf("\n\n### Execution 2\n\n");
    long long c_keygen_1 = cpucycles();
    crypto_kem_keypair(pk, sk);
    long long c_keygen_2 = cpucycles();

    long long c_encaps_1 = cpucycles();
    crypto_kem_enc(ct, key1, pk);
    long long c_encaps_2 = cpucycles();

    long long c_decaps_1 = cpucycles();
    crypto_kem_dec(key2, ct, sk);
    long long c_decaps_2 = cpucycles();

    printf("Keygen: %lld CPU cycles\n", c_keygen_2 - c_keygen_1);
    printf("Encaps: %lld CPU cycles\n", c_encaps_2 - c_encaps_1);
    printf("Decaps: %lld CPU cycles\n", c_decaps_2 - c_decaps_1);

    printf("\n\nsecret1: ");
    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key1[i]);
    printf("\nsecret2: ");

    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key2[i]);
    printf("\n\n");
  #endif

  #ifdef VERBOSE
    crypto_kem_keypair(pk, sk);
    crypto_kem_enc(ct, key1, pk);
    crypto_kem_dec(key2, ct, sk);

    printf("\n\nsecret1: ");
    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key1[i]);

    printf("\nsecret2: ");
    for(int i = 0 ; i < SHARED_SECRET_BYTES ; ++i) printf("%x", key2[i]);
    printf("\n\n");
  #endif
}