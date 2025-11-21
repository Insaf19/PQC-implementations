/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#include "stdio.h"
#include "string.h"
#include "kem.h"
#include "utilities.h"
#include "measurements.h"
#include "stdlib.h"
#include "time.h"

////////////////////////////////////////////////////////////////
//                 Main function for testing
////////////////////////////////////////////////////////////////
int main()
{
    srand(0);

    sk_t sk    = {0}; // private-key: (h0, h1)
    pk_t pk    = {0}; // public-key:  (g0, g1)
    ct_t ct    = {0}; // ciphertext:  (c0, c1)
    ss_t k_enc = {0}; // shared secret after encapsulate
    ss_t k_dec = {0}; // shared secret after decapsulate

    for (uint32_t i=1; i <= NUM_OF_TESTS; ++i)
    {
        status_t res = SUCCESS;

        MSG("Code test: %d\n\n", i);

        //Key generation
        MEASURE("  keypair", res = crypto_kem_keypair(pk.raw, sk.raw););

        if(res != SUCCESS)
        {
            MSG("Keypair failed with error: %d\n", res);
            continue;
        }

        uint32_t dec_rc = 0;

        //Encapsulate
        MEASURE("  encaps",  res = crypto_kem_enc(ct.raw, k_enc.raw, pk.raw););
        if(res != SUCCESS)
        {
            MSG("encapsulate failed with error: %d\n", res);
            continue;
        }

        //Decapsulate
        MEASURE("  decaps", dec_rc = crypto_kem_dec(k_dec.raw, ct.raw, sk.raw););

        if (dec_rc != 0)
        {
            printf("Decoding failed after %d code tests!\n", i);
        }
        else
        {
            if (safe_cmp(k_enc.raw, k_dec.raw, sizeof(k_dec)/sizeof(uint64_t)))
            {
                MSG("Success! decapsulated key is the same as encapsulated key!\n");
            } else {
                MSG("Failure! decapsulated key is NOT the same as encapsulated key!\n");
            }
        }
        
        DMSG("Initiator's generated key (K) of 256 bits = ");
        print((uint64_t*)k_enc.raw, ELL_K_SIZE*8);
        DMSG("Responder's computed key (K) of 256 bits  = ");
        print((uint64_t*)k_dec.raw, ELL_K_SIZE*8);
    }

    return 0;
}
