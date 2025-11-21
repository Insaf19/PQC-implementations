/**
 * \file ffi_vec.h
 * \brief Interface for vectors over a finite field
 */

#ifndef FFI_VEC_H
#define FFI_VEC_H

#include "ffi.h"
#include "rng.h"

void ffi_vec_init(ffi_field f, ffi_vec* v, unsigned int size);
void ffi_vec_clear(ffi_field f, ffi_vec v, unsigned int size);

void ffi_vec_set(ffi_field f, ffi_vec o, const ffi_vec v, unsigned int size);
void ffi_vec_set_zero(ffi_field f, ffi_vec v, unsigned int size);

void ffi_vec_set_random(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx);
void ffi_vec_set_random2(ffi_field f, ffi_vec v, unsigned int size);
void ffi_vec_set_random_full_rank(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx);
void ffi_vec_set_random_full_rank_with_one(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx);
void ffi_vec_set_random_from_support(ffi_field f, ffi_vec v, unsigned int size, const ffi_vec support, unsigned int rank, AES_XOF_struct* ctx);

int ffi_vec_get_rank(ffi_field f, const ffi_vec v, unsigned int size);
int ffi_vec_is_equal_to(ffi_field f, const ffi_vec v1, const ffi_vec v2, unsigned int size);

void ffi_vec_neg(ffi_field f, ffi_vec o, const ffi_vec v, unsigned int size);
void ffi_vec_add(ffi_field f, ffi_vec o, const ffi_vec v1, const ffi_vec v2, unsigned int size);

void ffi_vec_scalar_mul(ffi_field f, ffi_vec o, const ffi_vec v, const ffi_elt e, unsigned int size);
void ffi_vec_mul(ffi_field f, ffi_vec o, const ffi_vec v1, const ffi_vec v2, unsigned int size);

void ffi_vec_to_string(unsigned char* str, const ffi_vec v, unsigned int size);
void ffi_vec_from_string(ffi_vec v, unsigned int size, const unsigned char* str);

void ffi_vec_print(ffi_field f, const ffi_vec v, unsigned int size);

#endif

