/**
 * \file ffi_elt.c
 * \brief Implementation of ffi_elt.h using the MPFQ library
 */
 
#include "ffi_elt.h"


/** 
 * \fn void ffi_elt_init(ffi_field f, ffi_elt e)
 * \brief This function initializes a finite field element
 *
 * \param[in] f Finite field
 * \param[in, out] e Finite field element
 */
void ffi_elt_init(ffi_field f, ffi_elt e) {
  mpfq_init(f, e);
}



/** 
 * \fn void ffi_elt_clear(ffi_field f, ffi_elt e)
 * \brief This function clears the allocated memory for a finite field element
 *
 * \param[in] f Finite field
 * \param[in] e Finite field element
 */
void ffi_elt_clear(ffi_field f, ffi_elt e) {
  mpfq_clear(f, e);
}



/** 
 * \fn void ffi_elt_set(ffi_field f, ffi_elt o, const ffi_elt e)
 * \brief This function copies a finite field element into another one
 *
 * \param[in] f Finite field
 * \param[out] o Finite field element
 * \param[in] e Finite field element
 */
void ffi_elt_set(ffi_field f, ffi_elt o, const ffi_elt e) {
  mpfq_set(f, o, e);
}



/** 
 * \fn void ffi_elt_set_zero(ffi_field f, ffi_elt o)
 * \brief This function sets a finite field element to zero
 *
 * \param[in] f Finite field
 * \param[out] o Finite field element
 */
void ffi_elt_set_zero(ffi_field f, ffi_elt o) {
  mpfq_set_zero(f, o);
}



/** 
 * \fn void ffi_elt_set_one(ffi_field f, ffi_elt o)
 * \brief This function sets a finite field element to one
 *
 * \param[in] f Finite field
 * \param[out] o Finite field element
 */
void ffi_elt_set_one(ffi_field f, ffi_elt o) {
  mpfq_sscan(f, o, "1");
}



/** 
 * \fn int ffi_elt_is_zero(ffi_field f, const ffi_elt e)
 * \brief This functions tests if a finite field element is equal to zero
 *
 * \param[in] f Finite field
 * \param[in] e Finite field element
 * \return 1 if <b>e</b> is equal to zero, 0 otherwise
 */
int ffi_elt_is_zero(ffi_field f, const ffi_elt e) {
  return mpfq_is_zero(f, e);
}



/** 
 * \fn int ffi_elt_is_equal_to(ffi_field f, const ffi_elt e1, const ffi_elt e2)
 * \brief This function tests if two finite field elements are equal
 *
 * \param[in] f Finite field
 * \param[in] e1 Finite field element
 * \param[in] e2 Finite field element
 * \return 1 if <b>e1</b> and <b>e2</b> are equal, 0 otherwise
 */
int ffi_elt_is_equal_to(ffi_field f, const ffi_elt e1, const ffi_elt e2) {
  if(mpfq_cmp(f, e1, e2) == 0) {
    return 1;
  }
  return 0;
}



/** 
 * \fn int ffi_elt_is_greater_than(ffi_field f, const ffi_elt e1, const ffi_elt e2)
 * \brief This functions tests if a finite field element is greater than another one
 *
 * \param[in] f Finite field
 * \param[in] e1 Finite field element
 * \param[in] e2 Finite field element
 * \return 1 if <b>e1</b> is greater than <b>e2</b>, 0 otherwise
 */
int ffi_elt_is_greater_than(ffi_field f, const ffi_elt e1, const ffi_elt e2) {
  if(mpfq_cmp(f, e1, e2) == 1) {
    return 1;
  }
  return 0;
}



/** 
 * \fn int ffi_elt_get_coefficient(ffi_field f, const ffi_elt e, int index)
 * \brief This function returns the coefficient of the polynomial <b>e</b> at a given position.
 *
 * \param[in] f Finite field
 * \param[in] e Finite field element
 * \param[in] index Index of the coefficient
 * \return Coefficient of <b>e</b> at the given index
 */

int ffi_elt_get_coefficient(ffi_field f, const ffi_elt e, int index) {
  int position = index / MPFQ_BITS_PER_ULONG;
  unsigned long mask = 1 << (index % MPFQ_BITS_PER_ULONG);
  return (e[position] & mask) >> (index % MPFQ_BITS_PER_ULONG); 
}



/** 
 * \fn int ffi_elt_get_degree(ffi_field f, const ffi_elt e)
 * \brief This functions returns the degree of the polynomial <b>e</b>.
 *
 * \param[in] f Finite field
 * \param[in] e Finite field element
 * \return Degree of <b>e</b> 
 */
int ffi_elt_get_degree(ffi_field f, const ffi_elt e) {
  int index = MPFQ_ULONGS - 1;
  unsigned int msb = 0;
  unsigned long tmp = e[index];
  while(tmp >>= 1) msb++;

  if(msb != 0) return msb + index * MPFQ_BITS_PER_ULONG;
  
  index--;
  while(index >= 0) {
    if(e[index] != 0) break;
    index--;
  }

  if(index == -1) return -1;

  tmp = e[index];
  while(tmp >>= 1) msb++;
  return msb + index * MPFQ_BITS_PER_ULONG;
}


/** 
 * \fn void ffi_elt_neg(ffi_field f, ffi_elt o, const ffi_elt e)
 * \brief This function computes the additive inverse of a finite field element
 *
 * \param[in] f Finite field
 * \param[out] o Additive inverse of <b>e</b>
 * \param[in] e Finite field element
 */
void ffi_elt_neg(ffi_field f, ffi_elt o, const ffi_elt e) {
  mpfq_neg(f, o, e);
}



/** 
 * \fn void ffi_elt_add(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2)
 * \brief This function adds two finite field elements
 *
 * \param[in] f Finite field
 * \param[out] o Sum of <b>e1</b> and <b>e2</b>
 * \param[in] e1 Finite field element
 * \param[in] e2 Finite field element
 */
void ffi_elt_add(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2) {
  mpfq_add(f, o, e1, e2);
}



/** 
 * \fn void ffi_elt_inv(ffi_field f, ffi_elt o, const ffi_elt e)
 * \brief This function computes the multiplicative inverse of a finite field element
 *
 * \param[in] f Finite field
 * \param[out] o Multiplicative inverse of <b>e</b>
 * \param[in] e Finite field element
 */
void ffi_elt_inv(ffi_field f, ffi_elt o, const ffi_elt e) {
  mpfq_inv(f, o, e);
}



/** 
 * \fn void ffi_elt_mul(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2)
 * \brief This function multiplies two finite field elements
 *
 * \param[in] f Finite field
 * \param[out] o Product of <b>e1</b> and <b>e2</b>
 * \param[in] e1 Finite field element
 * \param[in] e2 Finite field element
 */
void ffi_elt_mul(ffi_field f, ffi_elt o, const ffi_elt e1, const ffi_elt e2) {
  mpfq_mul(f, o, e1, e2);
}



/** 
 * \fn void ffi_elt_sqrt(ffi_field f, ffi_elt o, const ffi_elt e)
 * \brief This function computes the square root of a finite field element
 *
 * \param[in] f Finite field
 * \param[out] o Square root of <b>e</b>
 * \param[in] e Finite field element
 */
void ffi_elt_sqrt(ffi_field f, ffi_elt o, const ffi_elt e) {
  mpfq_sqrt(f, o, e);
}



/** 
 * \fn void ffi_elt_pow(ffi_field f, ffi_elt o, const ffi_elt e, unsigned long exponent)
 * \brief This function computes the exponentiation of a finite field element
 *
 * \param[in] f Finite field
 * \param[out] o Finite field element equal to \f$ e^{exponent} \f$
 * \param[in] e Finite field element
 * \param[in] exponent Exponent
 */
void ffi_elt_pow(ffi_field f, ffi_elt o, const ffi_elt e, unsigned long exponent) {
  mpfq_pow(f, o, e, &exponent, 1);
}



/** 
 * \fn void ffi_elt_print(ffi_field f, const ffi_elt e)
 * \brief This function prints the value of a finite field element
 *
 * \param[in] f Finite field
 * \param[in] e Finite field element
 */
void ffi_elt_print(ffi_field f, const ffi_elt e) {
  mpfq_print(f, e);
}

