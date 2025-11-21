/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* Based on:
* github.com/Shay-Gueron/A-toolbox-for-software-optimization-of-QC-MDPC-code-based-cryptosystems
* ***************************************************************************/

#include "aes.h"
#include <wmmintrin.h>
#include <tmmintrin.h>

void AES256_Enc_Intrinsic(OUT const uint8_t* CT,
                          IN const uint8_t* PT,
                          IN const uint8_t* KS)
{
    uint32_t  i;
    __m128i block = _mm_loadu_si128((__m128i*)PT);
    block = _mm_xor_si128(block , ((__m128i*)KS)[0]);
    for (i=1;i<14;i++)
    {
        block = _mm_aesenc_si128(block , ((__m128i*)KS)[i]);
    }
    block = _mm_aesenclast_si128(block , ((__m128i*)KS)[14]);
    _mm_storeu_si128((__m128i *)(CT), block);
}
