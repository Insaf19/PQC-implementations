/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#include "ntl.h"
#include <NTL/GF2X.h>

using namespace NTL;

typedef unsigned char uint8_t;

EXTERNC void ntl_inv_mod(OUT uint8_t res_bin[R_SIZE], 
                         IN const uint8_t a_bin[R_SIZE])
{
   GF2X _m, a, res;

   GF2XFromBytes(a, a_bin, R_SIZE);

   //Create the modulus
   GF2XModulus m;
   SetCoeff(_m, 0, 1);
   SetCoeff(_m, R_BITS, 1);
   build(m, _m);

   InvMod(res, a, m);
   BytesFromGF2X(res_bin, res, R_SIZE);
}

EXTERNC void ntl_mod_mul(OUT uint8_t res_bin[R_SIZE], 
                         IN const uint8_t a_bin[R_SIZE],
                         IN const uint8_t b_bin[R_SIZE])
{
   GF2X _m, a, b, res;

   GF2XFromBytes(a, a_bin, R_SIZE);
   GF2XFromBytes(b, b_bin, R_SIZE);

   //Create the modulus
   GF2XModulus m;
   SetCoeff(_m, 0, 1);
   SetCoeff(_m, R_BITS, 1);
   build(m, _m);

   MulMod(res, a, b, m);

   BytesFromGF2X(res_bin, res, R_SIZE);
}
