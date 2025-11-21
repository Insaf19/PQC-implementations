/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#ifndef __API_H_INCLUDED__
#define __API_H_INCLUDED__

#include "types.h"

#define CRYPTO_SECRETKEYBYTES  sizeof(sk_t)
#define CRYPTO_PUBLICKEYBYTES  sizeof(pk_t)
#define CRYPTO_CIPHERTEXTBYTES sizeof(ct_t)
#define CRYPTO_BYTES           sizeof(ss_t)

#endif
