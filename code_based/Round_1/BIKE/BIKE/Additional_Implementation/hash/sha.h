/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* Based on:
* github.com/Shay-Gueron/A-toolbox-for-software-optimization-of-QC-MDPC-code-based-cryptosystems
* ***************************************************************************/

#ifndef _MB_SHA_H_
#define _MB_SHA_H_

#include "types.h"

#define SHA384_HASH_SIZE    48ULL
#define SHA384_HASH_QWORDS  (SHA384_HASH_SIZE/8)

#define SHA512_HASH_SIZE    64ULL
#define SHA512_HASH_QWORDS  (SHA512_HASH_SIZE/8)

typedef struct sha384_hash_s
{
    union
    {
         uint8_t  raw[SHA384_HASH_SIZE];
         uint64_t qwords[SHA384_HASH_QWORDS];
    };
} sha384_hash_t;

typedef struct sha512_hash_s
{
    union
    {
         uint8_t  raw[SHA512_HASH_SIZE];
         uint64_t qwords[SHA512_HASH_QWORDS];
    };
} sha512_hash_t;

typedef struct {
    uint8_t *ptr;
    uint32_t blocks;
} hash_desc;

#include "sha384.h"

int sha(OUT sha_hash_t *hash_out,
        IN const uint32_t byte_length,
        IN const uint8_t *msg);


void sha_mb(OUT sha_hash_t* hash_out,
            IN const uint8_t *msg,
            IN const uint32_t byte_length,
            IN const uint32_t num);

#endif //_MB_SHA_H_
