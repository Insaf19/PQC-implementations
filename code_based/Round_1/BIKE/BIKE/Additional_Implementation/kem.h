/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#ifndef __KEM_H_INCLUDED__
#define __KEM_H_INCLUDED__

#include "types.h"

////////////////////////////////////////////////////////////////
//Below three APIs (keygen, encaps, decaps) are defined by NIST:
////////////////////////////////////////////////////////////////
//Keygenerate - pk is the public key,
//              sk is the private key,
int crypto_kem_keypair(OUT unsigned char *pk, OUT unsigned char *sk);

//Encapsulate - pk is the public key,
//              ct is a key encapsulation message (ciphertext),
//              ss is the shared secret.
int crypto_kem_enc(OUT unsigned char *ct,
                   OUT unsigned char *ss,
                   IN const unsigned char *pk);

//Decapsulate - ct is a key encapsulation message (ciphertext),
//              sk is the private key,
//              ss is the shared secret
int crypto_kem_dec(OUT unsigned char *ss,
                   IN const unsigned char *ct,
                   IN const unsigned char *sk);

#endif //__KEM_H_INCLUDED__

