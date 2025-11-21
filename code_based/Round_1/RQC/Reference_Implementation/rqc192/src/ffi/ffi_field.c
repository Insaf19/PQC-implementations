/**
 * \file ffi_field.c
 * \brief Implementation of ffi_field.h using the MPFQ library
 *
 * In the context of the RQC scheme, a finite field always describes an extension of a binary field namely a finite field of the form \f$ GF(2^m) \f$.
 *
 * Finite fields used for RQC-128, RQC-192 and RQC-256 are respectively \f$ GF(2^{89}) \f$, \f$ GF(2^{113}) \f$ and \f$ GF(2^{139}) \f$.
 *
 */

#include "ffi.h"
#include "ffi_field.h"


/** 
 * \fn void ffi_field_init(ffi_field f)
 * \brief This function initializes a finite field
 *
 * \param[in, out] f Finite field
 */
void ffi_field_init(ffi_field f) {
  mpfq_field_init(f);

  mp_limb_t base = 16;
  mpfq_field_setopt(f, MPFQ_IO_TYPE, &base);
}



/** 
 * \fn void ffi_field_clear(ffi_field f)
 * \brief This function clears the allocated memory for a finite field
 *
 * \param[in] f Finite field
 */
void ffi_field_clear(ffi_field f) {
  mpfq_field_clear(f);
}



/** 
 * \fn int ffi_field_get_characteristic(const ffi_field f)
 * \brief This function returns the characteristic of a finite field
 *
 * \param[in] f Finite field
 * \return The characteristic of the finite field <b>f</b>
 */
int ffi_field_get_characteristic(const ffi_field f) {
  return FIELD_Q;
}



/** 
 * \fn int ffi_field_get_degree(ffi_field f)
 * \brief This function returns the degree of a finite field
 *
 * \param[in] f Finite field
 * \return The degree of the finite field <b>f</b>
 */
int ffi_field_get_degree(const ffi_field f) {
  return FIELD_M;
}

