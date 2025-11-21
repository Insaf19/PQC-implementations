/** 
 * \file ffi.h
 * \brief Contains some define and typedef easing the use of the MPFQ library
 */

#ifndef FFI_H
#define FFI_H

#include "mpfq_2_139.h"

#define FIELD_Q 2 /**< Parameter q of the scheme (finite field GF(q^m)) */
#define FIELD_M 139 /**< Parameter m of the scheme (finite field GF(q^m)) */
#define MPFQ_ULONGS 3 /**< Number of unsigned longs used by MPFQ to represent a field element */
#define MPFQ_BITS_PER_ULONG 64 /**< Number of bits in an unsigned long */

typedef mpfq_2_139_field ffi_field; /**< Type representing a finite field */
typedef mpfq_2_139_elt ffi_elt; /**< Type representing a finite field element */
typedef mpfq_2_139_vec ffi_vec; /**< Type representing a vector over a finite field */

#define mpfq_field_init mpfq_2_139_field_init
#define mpfq_field_setopt mpfq_2_139_field_setopt
#define mpfq_field_clear mpfq_2_139_field_clear

#define mpfq_add mpfq_2_139_add
#define mpfq_clear mpfq_2_139_clear
#define mpfq_cmp mpfq_2_139_cmp
#define mpfq_init mpfq_2_139_init
#define mpfq_inv mpfq_2_139_inv
#define mpfq_is_zero mpfq_2_139_is_zero
#define mpfq_mul mpfq_2_139_mul
#define mpfq_neg mpfq_2_139_neg
#define mpfq_pow mpfq_2_139_pow
#define mpfq_print mpfq_2_139_print
#define mpfq_set mpfq_2_139_set
#define mpfq_set_zero mpfq_2_139_set_zero
#define mpfq_sqrt mpfq_2_139_sqrt
#define mpfq_sscan mpfq_2_139_sscan

#define mpfq_vec_add mpfq_2_139_vec_add
#define mpfq_vec_cmp mpfq_2_139_vec_cmp
#define mpfq_vec_clear mpfq_2_139_vec_clear
#define mpfq_vec_conv mpfq_2_139_vec_conv
#define mpfq_vec_init mpfq_2_139_vec_init
#define mpfq_vec_neg mpfq_2_139_vec_neg
#define mpfq_vec_print mpfq_2_139_vec_print
#define mpfq_vec_scal_mul mpfq_2_139_vec_scal_mul
#define mpfq_vec_set mpfq_2_139_vec_set
#define mpfq_vec_set_zero mpfq_2_139_vec_set_zero

#endif

