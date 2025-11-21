/** 
 * \file q_polynomial.c
 * \brief Implementation of q_polynomial.h
 *
 * The q_polynomials are polynomials over a field of the form \f$ P(x) = \sum_{i=0}^{n} p_i \times x^{q^i} \f$ with \f$ q \f$ a rational prime.
 * See \cite ore:qpolynomials for a description of their main properties.
 *
 */

#include "q_polynomial.h"
#include "ffi_field.h"
#include "ffi_elt.h"
#include "ffi_vec.h"

#define INVALID_PARAMETERS -1; /**< Return status indicating that invalid parameters have been used in input */
#define SUCCESS 0; /**< Return status indicating that computation ended normally */


/** 
 * \fn q_polynomial* q_polynomial_init(ffi_field f, int max_degree)
 * \brief This function initializes a q_polynomial
 *
 * \param[in] f Finite field
 * \param[in] max_degree The maximum degree that the q_polynomial may have
 * \return q_polynomial
 */
q_polynomial* q_polynomial_init(ffi_field f, int max_degree) {
  q_polynomial* p = (q_polynomial*) malloc(sizeof(q_polynomial));
  
  *(p->field) = *f;
  p->max_degree = max_degree;
  p->degree = -1;
  ffi_vec_init(f, &(p->values), max_degree + 1);

  return p;
}



/** 
 * \fn void q_polynomial_clear(q_polynomial* p)
 * \brief This function clears the allocated memory for a q_polynomial
 *
 * \param[in] p q_polynomial
 */
void q_polynomial_clear(q_polynomial* p) {
  ffi_vec_clear(p->field, p->values, p->max_degree + 1);
  free(p);
}



/** 
 * \fn int q_polynomial_set(q_polynomial* o, q_polynomial* p)
 * \brief This function copies a q_polynomial into another one
 *
 * \param[in] p q_polynomial
 * \param[out] o q_polynomial
 * \return INVALID_PARAMETERS if <b>o->max_degree < p->degree</b>, SUCCESS otherwise
 */
int q_polynomial_set(q_polynomial* o, q_polynomial* const p) {
  if(o->max_degree < p->degree) {
    return INVALID_PARAMETERS;
  }

  if(q_polynomial_is_zero(p) == 1) {
    q_polynomial_set_zero(o);
  } else {
    o->degree = p->degree;

    for(int i = 0 ; i <= p->degree ; ++i) {
      ffi_elt_set(p->field, o->values[i], p->values[i]);
    }

    for(int i = p->degree + 1 ; i <= o->max_degree ; ++i) {
      ffi_elt_set_zero(p->field, o->values[i]);
    }
  }

  return SUCCESS;
}



/** 
 * \fn void q_polynomial_set_zero(q_polynomial* p)
 * \brief This function sets a q_polynomial to zero
 *
 * \param[out] p q_polynomial
 */
void q_polynomial_set_zero(q_polynomial* p) {
  p->degree = -1;
  ffi_vec_set_zero(p->field, p->values, p->max_degree + 1);
}



/** 
 * \fn r_status q_polynomial_set_one(q_polynomial* p)
 * \brief This function sets a q_polynomial to one
 *
 * \param[out] p q_polynomial
 */
void q_polynomial_set_one(q_polynomial* p) {
  p->degree = 0;
  ffi_elt_set_one(p->field, p->values[0]);

  for(int i = 1 ; i <= p->max_degree ; ++i) {
    ffi_elt_set_zero(p->field, p->values[i]);
  }
}



/** 
 * \fn void q_polynomial_set_interpolate_zero(q_polynomial* o, const ffi_vec v, unsigned int size)
 * \brief This function computes a q_polynomial whose roots are the coefficients of a given vector 
 *
 * This interpolation is computed by recurrence with \f$ o_1(x) = x^q - v_1^{q-1} \times x \f$ and for \f$ 2 \leq i \leq size, o_i(x) = o_{i-1}(x)^q - o_{i-1}^{q-1}(v_i) \times o_{i-1}(x) \f$.
 *
 * \param[out] o q_polynomial such that \f$ o(v_i) = 0 \f$ with \f$ 1 \leq i \leq size \f$
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void q_polynomial_set_interpolate_zero(q_polynomial* o, const ffi_vec v, unsigned int size) {
  int exponent = ffi_field_get_characteristic(o->field) - 1;

  ffi_elt tmp;
  ffi_elt_init(o->field, tmp);
  ffi_elt_pow(o->field, tmp, v[0], exponent);

  q_polynomial_set_zero(o);
  o->degree = 1;
  ffi_elt_set(o->field, o->values[0], tmp);
  ffi_elt_set_one(o->field, o->values[exponent]);

  q_polynomial* qtmp = q_polynomial_init(o->field, o->max_degree);
  q_polynomial_set_zero(qtmp);

  for(unsigned int i = 1 ; i < size ; ++i) {
    q_polynomial_qexp(qtmp, o);

    q_polynomial_evaluate(tmp, o, v[i]);
    ffi_elt_pow(o->field, tmp, tmp, exponent);
    q_polynomial_scalar_mul(o, o, tmp);
    // q_polynomial_neg(o, o);
    
    q_polynomial_add(o, qtmp, o);
  }

  q_polynomial_clear(qtmp);
  ffi_elt_clear(o->field, tmp);
}



/** 
 * \fn void q_polynomial_set_interpolate_kronecker(q_polynomial* o, const ffi_vec v, unsigned int size, const ffi_elt e)
 * \brief This function computes a q_polynomial whose roots are the coefficients of a given vector and whose evaluation at a given element is equal to 1
 *
 * This interpolation performs a zero interpolation of <b>o</b> on <b>v</b> followed by a scalar multiplication by \f$ o(e)^{-1} \f$.
 *
 * \param[out] o q_polynomial such that \f$ o(v_i) = 0 \f$ with \f$ 1 \leq i \leq size\f$ and \f$ o(e) = 1 \f$
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] e Finite field element
 */
void q_polynomial_set_interpolate_kronecker(q_polynomial* o, const ffi_vec v, unsigned int size, const ffi_elt e) {
  ffi_elt tmp;
  ffi_elt_init(o->field, tmp);

  q_polynomial_set_interpolate_zero(o, v, size);
  q_polynomial_evaluate(tmp, o, e);
  ffi_elt_inv(o->field, tmp, tmp);
  q_polynomial_scalar_mul(o, o, tmp);

  ffi_elt_clear(o->field, tmp);
}



/** 
 * \fn void q_polynomial_set_interpolate_vect(q_polynomial* o, const ffi_vec v1, const ffi_vec v2, unsigned int size)
 * \brief This function computes a q_polynomial interpolating a given vector at another given vector
 *
 * This interpolation computes all \f$ P_i(x) \f$ for \f$ 1 \leq i \leq size \f$ such that each \f$ P_i(x) \f$ is the Kronecher interpolation q_polynomial over \f$ v1 \f$ and \f$ v1_i \f$. Next, the q_polynomial o is computed as \f$ o(x) = \sum_{i = 1}^{size} v2_i \times P_i(x) \f$. 
 *
 * \param[out] o q_polynomial such that \f$ o(v1_i) = v2_i \f$ with \f$ 1 \leq i \leq size \f$
 * \param[in] v1 Vector over a finite field
 * \param[in] v2 Vector over a finite field
 * \param[in] size Size of the vectors
 */
void q_polynomial_set_interpolate_vect(q_polynomial* o, const ffi_vec v1, const ffi_vec v2, unsigned int size) {
  ffi_vec v;
  ffi_vec_init(o->field, &v, size - 1);

  q_polynomial* p = q_polynomial_init(o->field, o->max_degree); 

  q_polynomial_set_zero(o);
  for(unsigned int i = 0 ; i < size ; ++i)  {
    // Compute Kronecher q_polynomial
    if(i == 0) {
      for(unsigned int j = 1 ; j < size ; ++j) {
        ffi_elt_set(o->field, v[j-1], v1[j]); 
      }
    } else {
      ffi_elt_set(o->field, v[i-1], v1[i-1]); 
    }

    q_polynomial_set_interpolate_kronecker(p, v, size - 1, v1[i]);

    // Compute interpolation q_polynomial
    q_polynomial_scalar_mul(p, p, v2[i]);
    q_polynomial_add(o, o, p);
  }

  ffi_vec_clear(o->field, v, size - 1);
  q_polynomial_clear(p);
}



/** 
 * \fn int q_polynomial_is_zero(q_polynomial* p)
 * \brief This function tests if a q_polynomial is equal to zero
 *
 * \param[in] p q_polynomial
 * \return returns 1 if <b>p</b> is equal to zero, 0 otherwise
 */
int q_polynomial_is_zero(q_polynomial* p) {
  if(p->degree == -1) {
    return 1;
  }
  return 0;
}



/** 
 * \fn void q_polynomial_evaluate(ffi_elt o, q_polynomial* p, const ffi_elt e)
 * \brief This function evaluates a q_polynomial on a finite field element
 *
 * \param[out] o Finite field element equal to \f$ p(e) \f$
 * \param[in] p q_polynomial
 * \param[in] e Finite field element
 */
void q_polynomial_evaluate(ffi_elt o, q_polynomial* p, const ffi_elt e) {
  if(q_polynomial_is_zero(p) == 1) {
    ffi_elt_set_zero(p->field, o);
  } 
  else {
    ffi_elt tmp1, tmp2;
    ffi_elt_init(p->field, tmp1);
    ffi_elt_init(p->field, tmp2);
    int exponent = ffi_field_get_characteristic(p->field);

    ffi_elt_set(p->field, tmp1, e);
    ffi_elt_mul(p->field, o, p->values[0], tmp1);

    for(int i = 1 ; i <= p->degree ; ++i) {
      ffi_elt_pow(p->field, tmp1, tmp1, exponent);
      ffi_elt_mul(p->field, tmp2, p->values[i], tmp1);
      ffi_elt_add(p->field, o, o, tmp2);
    }

    ffi_elt_clear(p->field, tmp1);
    ffi_elt_clear(p->field, tmp2);
  }
}



/** 
 * \fn void q_polynomial_update_degree(q_polynomial* p, unsigned int position)
 * \brief This function updates the degree of a q_polynomial starting from a given position
 *
 * \param[out] p q_polynomial
 * \param[in] position position to start from
 */
void q_polynomial_update_degree(q_polynomial* p, unsigned int position) {
  for(int i = position ; i >= 0 ; --i) {
    if(ffi_elt_is_zero(p->field, p->values[i]) == 0) { 
      p->degree = i;
      return;
    }
  }

  p->degree = -1;
}


/** 
 * \fn int q_polynomial_neg(q_polynomial* o, q_polynomial* p)
 * \brief This function computes the additive inverse of a q_polynomial
 *
 * \param[out] o q_polynomial equal to \f$ -p \f$
 * \param[in] p q_polynomial
 * \return INVALID_PARAMETERS if <b>o->max_degree < p->degree</b>, SUCCESS otherwise
 */
int q_polynomial_neg(q_polynomial* o, q_polynomial* p) {
  if(o->max_degree < p->degree) {
    return INVALID_PARAMETERS;
  }

  ffi_vec_neg(o->field, o->values, p->values, p->degree + 1);
  return SUCCESS;
}



/** 
 * \fn int q_polynomial_add(q_polynomial* o, q_polynomial* p, q_polynomial* q)
 * \brief This function adds two q_polynomials
 *
 * \param[out] o Sum of q_polynomials <b>p</b> and <b>r</b>
 * \param[in] p q_polynomial
 * \param[in] q q_polynomial
 * \return INVALID_PARAMETERS if <b>o->max_degree < max(p->degree, q->degree)</b>, SUCCESS otherwise
 */
int q_polynomial_add(q_polynomial* o, q_polynomial* p, q_polynomial* q) {
  int degree = p->degree > q->degree ? p->degree : q->degree; 
  if(o->max_degree < degree) {
    return INVALID_PARAMETERS;
  }

  if(degree == -1) {
    q_polynomial_set_zero(o);
  } 
  else {
    o->degree = degree;
    for(int i = 0 ; i <= o->degree ; ++i) {
      ffi_elt_add(o->field, o->values[i], p->values[i], q->values[i]);
    }

    for(int i = o->degree + 1 ; i <= o->max_degree ; ++i) {
      ffi_elt_set_zero(o->field, o->values[i]);
    }

    q_polynomial_update_degree(o, o->degree);
  }

  return SUCCESS;
}



/** 
 * \fn int q_polynomial_scalar_mul(q_polynomial* o, q_polynomial* p, const ffi_elt e)
 * \brief This function computes the scalar product between a q_polynomial and a finite field element
 *
 * \param[out] o q_polynomial equal to \f$ e \times p \f$
 * \param[in] p q_polynomial
 * \param[in] e Finite field element
 * \return INVALID_PARAMETERS if <b>o->max_degree < p->degree</b>, SUCESS otherwise
 */
int q_polynomial_scalar_mul(q_polynomial* o, q_polynomial* p, const ffi_elt e) {
  if(o->max_degree < p->degree) {
    return INVALID_PARAMETERS;
  }

  if(q_polynomial_is_zero(p) == 1) {
    q_polynomial_set_zero(o);
  } else {
    ffi_vec_scalar_mul(o->field, o->values, p->values, e, p->degree + 1); 

    for(int i = p->degree + 1 ; i <= o->max_degree ; ++i) {
      ffi_elt_set_zero(o->field, o->values[i]);
    }

    q_polynomial_update_degree(o, p->degree);
  }

  return SUCCESS;
}



/** 
 * \fn int q_polynomial_mul(q_polynomial* o, q_polynomial* p, q_polynomial* q)
 * \brief This function computes the multiplication of two q_polynomials
 *
 * Multiplication of two q_polynomials is non commutative and is defined using composition namely \f$ p \times q = p \circ q \f$.
 *
 * \param[out] o q_polynomial equal to \f$ p \circ q \f$
 * \param[in] p q_polynomial
 * \param[in] q q_polynomial
 * \return INVALID_PARAMETERS if <b>o->max_degree < p->degree + q->degree</b>, SUCCESS otherwise
 */
int q_polynomial_mul(q_polynomial* o, q_polynomial* p, q_polynomial* q) {
  if(o->max_degree < p->degree + q->degree) {
    return INVALID_PARAMETERS;
  }

  if(q_polynomial_is_zero(p) == 1 || q_polynomial_is_zero(q) == 1) {
    q_polynomial_set_zero(o);
    return SUCCESS;
  } else {
    ffi_elt tmp1, tmp2;
    ffi_elt_init(o->field, tmp1);
    ffi_elt_init(o->field, tmp2);
    int exponent = ffi_field_get_characteristic(o->field);

    for(int j = 0 ; j <= q->degree ; ++j) {
      ffi_elt_set(o->field, tmp1, q->values[j]);
      ffi_elt_mul(o->field, tmp2, p->values[0], tmp1);
      ffi_elt_add(o->field, o->values[j], o->values[j], tmp2); 
      for(int i = 1 ; i <= p->degree ; ++i) {
        ffi_elt_pow(o->field, tmp1, tmp1, exponent);
        ffi_elt_mul(o->field, tmp2, p->values[i], tmp1);
        int position = (j + i) % ffi_field_get_degree(o->field);
        ffi_elt_add(o->field, o->values[position], o->values[position], tmp2); 
      }
    }

    q_polynomial_update_degree(o, p->degree + q->degree);
    ffi_elt_clear(o->field, tmp1);
    ffi_elt_clear(o->field, tmp2);

    return SUCCESS;
  }
}



/** 
 * \fn int q_polynomial_qexp(q_polynomial* o, q_polynomial* p)
 * \brief This function computes the qth power of a q_polynomial
 *
 * \param[out] o q_polynomial equal to \f$ p^q \f$ where <b>q</b> is the characteristic of the field
 * \param[in] p q_polynomial
 * \return INVALID_PARAMETERS if <b>o->max_degree < p->degree + 1</b>, SUCCESS otherwise
 */
int q_polynomial_qexp(q_polynomial* o, q_polynomial* p) {
  if(o->max_degree < p->degree + 1) {
    return INVALID_PARAMETERS;
  }

  if(q_polynomial_is_zero(p) == 1) {
    q_polynomial_set_zero(o);
  } 
  else {
    int exponent = ffi_field_get_characteristic(o->field);
    for(int i = 0 ; i <= p->degree ; ++i) {
      ffi_elt_pow(p->field, o->values[(i+1) % ffi_field_get_degree(p->field)], p->values[i], exponent);
    }

    for(int i = p->degree + 2 ; i <= o->max_degree ; ++i) {
      ffi_elt_set_zero(o->field, o->values[i]);
    }

    q_polynomial_update_degree(o, p->degree + 1);
  }

  return SUCCESS;
}



/** 
 * \fn int q_polynomial_left_div(q_polynomial* q, q_polynomial* r, q_polynomial* a, q_polynomial* b)
 * \brief This function computes the left division of two q_polynomials using euclidean algorithm: \f$ a = b \times q + r \f$
 *
 * \param[out] q q_polynomial equal to the quotient of the division
 * \param[out] r q_polynomial equal to the remainder of the division
 * \param[in] a q_polynomial to divide
 * \param[in] b divisor q_polynomial
 * \return INVALID_PARAMETERS if <b>a->degree < b->degree</b> or <b>q->max_degree < a->max_degree - b->max_degree</b> or <b>r->max_degree < b->max_degree</b>, SUCCESS otherwise
 */
int q_polynomial_left_div(q_polynomial* q, q_polynomial* r, q_polynomial* a, q_polynomial* b) {
  if(a->degree < b->degree || q->max_degree < a->max_degree - b->max_degree || r->max_degree < b->max_degree - 1) {
    return INVALID_PARAMETERS;
  }

  q_polynomial_set_zero(q);
  q_polynomial_set(r, a);

  q_polynomial* s = q_polynomial_init(a->field, a->degree - b->degree);
  q_polynomial* t = q_polynomial_init(a->field, a->max_degree);

  ffi_elt b_lead_coeff_inv;
  ffi_elt r_lead_coeff;
  ffi_elt s_lead_coeff;
  ffi_elt_init(b->field, b_lead_coeff_inv);
  ffi_elt_init(r->field, r_lead_coeff);
  ffi_elt_init(s->field, s_lead_coeff);
  
  ffi_elt_set(b->field, b_lead_coeff_inv, b->values[b->degree]);
  ffi_elt_inv(b->field, b_lead_coeff_inv, b_lead_coeff_inv);

  while(r->degree >= b->degree) {
    // Compute monial s
    ffi_elt_set(r->field, r_lead_coeff, r->values[r->degree]);
    ffi_elt_mul(s->field, s_lead_coeff, r_lead_coeff, b_lead_coeff_inv);
    for(int i = 0 ; i < b->degree ; ++i) {
      ffi_elt_sqrt(s->field, s_lead_coeff, s_lead_coeff);
    }

    q_polynomial_set_zero(s);
    ffi_elt_set(s->field, s->values[r->degree - b->degree], s_lead_coeff);
    s->degree = r->degree - b->degree;

    // Update quotient q_polynomial
    q_polynomial_add(q, q, s);

    // Update remainder q_polynomial
    q_polynomial_set_zero(t);
    q_polynomial_mul(t, b, s);
    // q_polynomial_neg(t, t);
    q_polynomial_add(r, r, t);
  }

  ffi_elt_clear(b->field, b_lead_coeff_inv);
  ffi_elt_clear(r->field, r_lead_coeff);
  ffi_elt_clear(s->field, s_lead_coeff);

  q_polynomial_clear(s);
  q_polynomial_clear(t);

  return SUCCESS;
}



/** 
 * \fn void q_polynomial_print(q_polynomial* p)
 * \brief This function prints a q_polynomial
 *
 * \param p q_polynomial
 */
void q_polynomial_print(q_polynomial* p) {
  if(q_polynomial_is_zero(p) == 1) {
    printf("0");
  } 
  else {
    for(int i = p->degree ; i >= 0 ; --i) {
      ffi_elt_print(p->field, p->values[i]);
      if(i != 0) {
        printf(" * x^[%i] + ", i);
      } 
      else {
        printf(" * x^[%i]", i);
      }
    }
  }
  printf("\n");
}

