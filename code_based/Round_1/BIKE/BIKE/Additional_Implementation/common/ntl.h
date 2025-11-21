/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#ifndef _NTL_H
#define _NTL_H

#ifdef __cplusplus
  #define EXTERNC extern "C"
#else
  #define EXTERNC
#endif

#include "types.h"

EXTERNC void ntl_inv_mod(OUT uint8_t res_bin[R_SIZE], 
                         IN const uint8_t a_bin[R_SIZE]);

EXTERNC void ntl_mod_mul(OUT uint8_t res_bin[R_SIZE], 
                         IN const uint8_t a_bin[R_SIZE],
                         IN const uint8_t b_bin[R_SIZE]);

#endif
