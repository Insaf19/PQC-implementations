/** 
 * \file ffi.h
 * \brief Contains some define and typedef easing the use of the MPFQ library
 */

#ifndef FFI_H
#define FFI_H

#include "mpfq_2_89.h"

#define FIELD_Q 2 /**< Parameter q of the scheme (finite field GF(q^m)) */
#define FIELD_M 89 /**< Parameter m of the scheme (finite field GF(q^m)) */
#define MPFQ_ULONGS 2 /**< Number of unsigned longs used by MPFQ to represent a field element */
#define MPFQ_BITS_PER_ULONG 64 /**< Number of bits in an unsigned long */

typedef mpfq_2_89_field ffi_field; /**< Type representing a finite field */
typedef mpfq_2_89_elt ffi_elt; /**< Type representing a finite field element */
typedef mpfq_2_89_vec ffi_vec; /**< Type representing a vector over a finite field */

#define mpfq_field_init mpfq_2_89_field_init
#define mpfq_field_setopt mpfq_2_89_field_setopt
#define mpfq_field_clear mpfq_2_89_field_clear

#define mpfq_add mpfq_2_89_add
#define mpfq_clear mpfq_2_89_clear
#define mpfq_cmp mpfq_2_89_cmp
#define mpfq_init mpfq_2_89_init
#define mpfq_inv mpfq_2_89_inv
#define mpfq_is_zero mpfq_2_89_is_zero
#define mpfq_mul mpfq_2_89_mul
#define mpfq_neg mpfq_2_89_neg
#define mpfq_pow mpfq_2_89_pow
#define mpfq_print mpfq_2_89_print
#define mpfq_set mpfq_2_89_set
#define mpfq_set_zero mpfq_2_89_set_zero
#define mpfq_sqrt mpfq_2_89_sqrt
#define mpfq_sscan mpfq_2_89_sscan

#define mpfq_vec_add mpfq_2_89_vec_add
#define mpfq_vec_cmp mpfq_2_89_vec_cmp
#define mpfq_vec_clear mpfq_2_89_vec_clear
#define mpfq_vec_conv mpfq_2_89_vec_conv
#define mpfq_vec_init mpfq_2_89_vec_init
#define mpfq_vec_neg mpfq_2_89_vec_neg
#define mpfq_vec_print mpfq_2_89_vec_print
#define mpfq_vec_scal_mul mpfq_2_89_vec_scal_mul
#define mpfq_vec_set mpfq_2_89_vec_set
#define mpfq_vec_set_zero mpfq_2_89_vec_set_zero

#endif

