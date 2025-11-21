/** 
 * \file q_polynomial.h
 * \brief Functions to manipulate q-polynomials. 
 *
 * The q_polynomials are polynomials over a field of the form \f$ P(x) = \sum_{i=0}^{n} p_i \times x^{q^i} \f$ with \f$ q \f$ a rational prime.
 * See \cite ore:qpolynomials for a description of their main properties.
 *
 */

#ifndef Q_POLYNOMIAL_H
#define Q_POLYNOMIAL_H

#include "ffi.h"

/**
  * \typedef q_polynomial
  * \brief Structure of a q-polynomial
  */
typedef struct q_polynomial {
  ffi_field field; /**< Finite field over which the q-polynomial is defined */
  ffi_vec values; /**< Coefficients of the q-polynomial */
  int max_degree; /**< Maximum q-degree that the q-polynomial may have. This value never changes */
  int degree; /**< Q-degree of the q-polynomial. This value is updated whenever necessary */
} q_polynomial;


q_polynomial* q_polynomial_init(ffi_field f, int max_degree);
void q_polynomial_clear(q_polynomial* p);

int q_polynomial_set(q_polynomial* o, q_polynomial* p);
void q_polynomial_set_zero(q_polynomial* o);
void q_polynomial_set_one(q_polynomial* o);
void q_polynomial_set_interpolate_zero(q_polynomial* o, const ffi_vec v, unsigned int size);
void q_polynomial_set_interpolate_kronecker(q_polynomial* o, const ffi_vec v, unsigned int size, const ffi_elt e);
void q_polynomial_set_interpolate_vect(q_polynomial* o, const ffi_vec v1, const ffi_vec v2, unsigned int size);

int q_polynomial_is_zero(q_polynomial* a);
void q_polynomial_evaluate(ffi_elt o, q_polynomial* p, const ffi_elt e);
void q_polynomial_update_degree(q_polynomial* p, unsigned int position);

int q_polynomial_neg(q_polynomial* o, q_polynomial* p);
int q_polynomial_add(q_polynomial* o, q_polynomial* p, q_polynomial* q);  

int q_polynomial_scalar_mul(q_polynomial* o, q_polynomial* p, const ffi_elt e);
int q_polynomial_mul(q_polynomial* o, q_polynomial* p, q_polynomial* q);  
int q_polynomial_qexp(q_polynomial* o, q_polynomial* p);
int q_polynomial_left_div(q_polynomial* q, q_polynomial* r, q_polynomial* a, q_polynomial* b);

void q_polynomial_print(q_polynomial* p);

#endif

