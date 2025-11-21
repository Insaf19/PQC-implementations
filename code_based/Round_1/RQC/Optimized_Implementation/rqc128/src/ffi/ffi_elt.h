/**
 * \file ffi_elt.h
 * \brief Interface for finite field elements
 */

#ifndef FFI_ELT_H
#define FFI_ELT_H

#include "ffi.h"

void ffi_elt_init(ffi_field f, ffi_elt e);
void ffi_elt_clear(ffi_field f, ffi_elt e);

void ffi_elt_set(ffi_field f, ffi_elt o, const ffi_elt e);
void ffi_elt_set_zero(ffi_field f, ffi_elt e);
void ffi_elt_set_one(ffi_field f, ffi_elt e);

int ffi_elt_is_zero(ffi_field f, const ffi_elt e);
int ffi_elt_is_equal_to(ffi_field f, const ffi_elt e1, const ffi_elt e2);
int ffi_elt_is_greater_than(ffi_field f, const ffi_elt e1, const ffi_elt e2);

int ffi_elt_get_coefficient(ffi_field f, const ffi_elt e, int position);
int ffi_elt_get_degree(ffi_field f, const ffi_elt e);

void ffi_elt_neg(ffi_field f, ffi_elt o, const ffi_elt e);
void ffi_elt_add(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2);

void ffi_elt_inv(ffi_field f, ffi_elt o, const ffi_elt e);
void ffi_elt_mul(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2);

void ffi_elt_sqrt(ffi_field f, ffi_elt o, const ffi_elt e);
void ffi_elt_pow(ffi_field f, ffi_elt o, const ffi_elt e, unsigned long exponent);

void ffi_elt_print(ffi_field f, const ffi_elt e);

#endif

