/**
 * \file ffi_field.h
 * \brief Interface for finite fields
 *
 * In the context of the RQC scheme, a finite field always describes an extension of a binary field namely a finite field of the form \f$ GF(2^m) \f$.
 *
 * Finite fields used for RQC-128, RQC-192 and RQC-256 are respectively \f$ GF(2^{89}) \f$, \f$ GF(2^{113}) \f$ and \f$ GF(2^{139}) \f$.
 *
 */

#ifndef FFI_FIELD_H
#define FFI_FIELD_H

#include "ffi.h"

void ffi_field_init(ffi_field f);
void ffi_field_clear(ffi_field f);
int ffi_field_get_characteristic(const ffi_field f);
int ffi_field_get_degree(const ffi_field f);

#endif

