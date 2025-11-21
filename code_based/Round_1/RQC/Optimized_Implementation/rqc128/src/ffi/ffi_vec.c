/**
 * \file ffi_vec.c
 * \brief Implementation of ffi_vec.h using the MPFQ library
 */

#include "ffi_field.h"
#include "ffi_elt.h"
#include "ffi_vec.h"


/** 
 * \fn void ffi_vec_init(ffi_field f, ffi_vec* v, unsigned int size)
 * \brief This function initializes a vector over a finite field
 *
 * \param[in] f Finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void ffi_vec_init(ffi_field f, ffi_vec* v, unsigned int size) {
  mpfq_vec_init(f, v, size);
}



/** 
 * \fn void ffi_vec_clear(ffi_field f, ffi_vec v, unsigned int size)
 * \brief This function clears the allocated memory for a vector over a finite field
 *
 * \param[in] f Finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void ffi_vec_clear(ffi_field f, ffi_vec v, unsigned int size) {
  mpfq_vec_clear(f, &v, size);
}



/** 
 * \fn void ffi_vec_set(ffi_field f,  ffi_vec o, const ffi_vec v, unsigned int size)
 * \brief This function copies a vector over a finite field into another one
 *
 * \param[in] f Finite field
 * \param[out] o Vector over a finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vectors
 */
void ffi_vec_set(ffi_field f, ffi_vec o, const ffi_vec v, unsigned int size) {
  mpfq_vec_set(f, o, v, size);
}



/** 
 * \fn void ffi_vec_set_zero(ffi_field f,  ffi_vec v, unsigned int size)
 * \brief This function sets a vector over a finite field to zero
 *
 * \param[in] f Finite field
 * \param[out] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void ffi_vec_set_zero(ffi_field f, ffi_vec v, unsigned int size) {
  mpfq_vec_set_zero(f, v, size);
}



/** 
 * \fn void ffi_vec_set_random(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx)
 * \brief This function sets a vector with random values using the NIST seed expander
 *
 * \param[in] f Finite field
 * \param[out] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] ctx NIST seed expander
 */
void ffi_vec_set_random(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx) {
  ffi_vec_set_zero(f, v, size);

  int bytes = (FIELD_M % 8 == 0) ? FIELD_M / 8 : FIELD_M / 8 + 1;
  unsigned char random[size * bytes];
  seedexpander(ctx, random, size * bytes);

  unsigned char mask = (1 << FIELD_M % 8) - 1;
  for(unsigned int i = 1 ; i <= size ; ++i) {
    random[i * bytes - 1] &= mask;
    memcpy((unsigned long*) v[i - 1], random + ((i - 1) * bytes), bytes);
  }
}



/** 
 * \fn void ffi_vec_set_random2(ffi_field f, ffi_vec v, unsigned int size)
 * \brief This function sets a vector with random values using the NIST random number generator
 *
 * \param[in] f Finite field
 * \param[out] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void ffi_vec_set_random2(ffi_field f, ffi_vec v, unsigned int size) {
  ffi_vec_set_zero(f, v, size);

  int bytes = (FIELD_M % 8 == 0) ? FIELD_M / 8 : FIELD_M / 8 + 1;
  unsigned char random[size * bytes];
  randombytes(random, size * bytes);

  unsigned char mask = (1 << FIELD_M % 8) - 1;
  for(unsigned int i = 1 ; i <= size ; ++i) {
    random[i * bytes - 1] &= mask;
    memcpy((unsigned long*) v[i - 1], random + ((i - 1) * bytes), bytes);
  }
}



/** 
 * \fn void ffi_vec_set_random_full_rank(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx)
 * \brief This function sets a vector with random values using the NIST seed expander. In addition, the vector returned by this function has full rank.
 *
 * \param[in] f Finite field
 * \param[out] v Full rank vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] ctx NIST seed expander
 */
void ffi_vec_set_random_full_rank(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx) {
  unsigned int rank_max = min(FIELD_M, size);

  unsigned int rank = -1;
  while(rank != rank_max) {
    ffi_vec_set_random(f, v, size, ctx);
    rank = ffi_vec_get_rank(f, v, size);
  }
}



/** 
 * \fn void ffi_vec_set_random_full_rank_with_one(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx)
 * \brief This function sets a vector with random values using the NIST seed expander. In addition, the vector returned by this function has full rank and contains one.
 *
 * \param[in] f Finite field
 * \param[out] v Full rank vector over a finite field containing one
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] ctx NIST seed expander
 */
void ffi_vec_set_random_full_rank_with_one(ffi_field f, ffi_vec v, unsigned int size, AES_XOF_struct* ctx) {
  unsigned int rank_max = min(FIELD_M, size);

  unsigned int rank = -1;
  while(rank != rank_max) {
    ffi_vec_set_random_full_rank(f, v, size - 1, ctx);
    ffi_elt_set_one(f, v[size - 1]);
    rank = ffi_vec_get_rank(f, v, size);
  }
}



/** 
 * \fn void ffi_vec_set_random_from_support(ffi_field f, ffi_vec v, unsigned int size, const ffi_vec support, unsigned int rank, AES_XOF_struct* ctx)
 * \brief This function sets a vector with random values using the NIST seed expander. In addition, the support of the vector returned by this function is the one given in input.
 *
 * This function copies the support vector in rank random positions of <b>v</b>. Next, all the remaining coordinates of <b>v</b> are setted using random linear combinations of the support coordinates.
 *
 * \param[in] f Finite field
 * \param[out] v Vector of given support
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] support Support of <b>v</b>
 * \param[in] rank Size of the vector support
 * \param[in] ctx NIST seed expander
 */
void ffi_vec_set_random_from_support(ffi_field f, ffi_vec v, unsigned int size, const ffi_vec support, unsigned int rank, AES_XOF_struct* ctx) {
  ffi_vec_set_zero(f, v, size);

  // Copy the support vector in rank random positions of v
  int random_position_size = 2 * rank;
  unsigned char random_position[random_position_size];
  seedexpander(ctx, random_position, random_position_size);

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int position;
  while(i != rank) {
    position = random_position[j];
    // Perform rejection sampling and check that the position is not already taken
    if(position < size * (256 / size) && ffi_elt_is_zero(f, v[position % size]) == 1) {
      ffi_elt_set(f, v[position % size], support[i]);
      i++;
    }

    // Get more randomness if necessary
    j++;
    if(j % random_position_size == 0 && i != rank) {
      seedexpander(ctx, random_position, random_position_size);
      j = 0;
    }
  }

  // Set all the remaining coordinates with random linear combinations of the support coordinates
  int random_lin_comb_size = rank * (size - rank);
  unsigned char random_lin_comb[random_lin_comb_size];
  seedexpander(ctx, random_lin_comb, random_lin_comb_size);

  int k = 0;
  int q = ffi_field_get_characteristic(f);
  for(i = 0 ; i < size ; ++i) {
    if(ffi_elt_is_zero(f, v[i])) {
      for(j = 0 ; j < rank ; ++j) {
        if((random_lin_comb[k * rank + j] % q) == 1) {
          ffi_elt_add(f, v[i], v[i], support[j]);
        }
      }
      k++;
    }
  }
}



/** 
 * \fn int ffi_vec_get_rank(ffi_field f, const ffi_vec v, unsigned int size)
 * \brief This function computes the rank of a vector over a finite field namely the rank of the matrix induced by the vector over GF(2).
 *
 * This function performs a Gaussian elimination on the matrix induced by the vector <b>v</b> starting from the bottom rows of the matrix.
 *
 * \param[in] f Finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector
 * \return The rank of <b>v</b>
 */
int ffi_vec_get_rank(ffi_field f, const ffi_vec v, unsigned int size) {
  ffi_vec v2;
  ffi_vec_init(f, &v2, size);
  ffi_vec_set(f, v2, v, size);

  ffi_elt tmp;
  ffi_elt_init(f, tmp);

  for(unsigned int i = 0 ; i < size ; ++i) {
    // Take the pivot as the greatest coordinate of v
    int pivot = i;
    for(unsigned int j = pivot + 1 ; j < size ; ++j) {
      if(ffi_elt_is_greater_than(f, v2[j], v2[pivot]) == 1) {
        pivot = j;
      }
    }

    // Stop computation if the pivot is equal to zero
    if(ffi_elt_is_zero(f, v[pivot]) == 1) {
      ffi_elt_clear(f, tmp);
      ffi_vec_clear(f, v2, size);
      return i; 
    }

    // Swap current coordinate with pivot
    ffi_elt_set(f, tmp, v2[i]);
    ffi_elt_set(f, v2[i], v2[pivot]);
    ffi_elt_set(f, v2[pivot], tmp);

    // Add matrix columns whenever necessary
    int degree = ffi_elt_get_degree(f, v2[i]);
    for(unsigned int j = i + 1 ; j < size ; ++j) {
      if(ffi_elt_get_coefficient(f, v2[j], degree) == 1) {
        ffi_elt_add(f, v2[j], v2[j], v2[i]);  
      }     
    }
  }

  ffi_elt_clear(f, tmp);
  ffi_vec_clear(f, v2, size);
  return size;
}



/** 
 * \fn int ffi_vec_is_equal_to(ffi_field f, const ffi_vec v1, const ffi_vec v2, unsigned int size)
 * \brief This functions tests if two vectors over a finite field are equal
 *
 * \param[in] f Finite field
 * \param[in] v1 Vector over a finite field
 * \param[in] v2 Vector over a finite field
 * \param[in] size Size of the vectors
 * \return 1 if <b>v1</b> and <b>v2</b> are equal, 0 otherwise
 */
int ffi_vec_is_equal_to(ffi_field f, const ffi_vec v1, const ffi_vec v2, unsigned int size) {
  return (mpfq_vec_cmp(f, v1, v2, size) == 0) ? 1 : 0;  
}



/** 
 * \fn void ffi_vec_neg(ffi_field f, ffi_vec o, ffi_vec v, unsigned int size)
 * \brief This function computes the additive inverse of a vector over a finite field
 *
 * \param[in] f Finite field
 * \param[out] o Vector over a finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vectors
 */
void ffi_vec_neg(ffi_field f, ffi_vec o, ffi_vec v, unsigned int size) {
  mpfq_vec_neg(f, o, v, size);
}



/** 
 * \fn void ffi_vec_add(ffi_field f, ffi_vec o, ffi_vec v1, ffi_vec v2, unsigned int size)
 * \brief This functions adds two vectors over a finite field
 *
 * \param[in] f Finite field
 * \param[out] o Sum of <b>v1</b> and <b>v2</b>
 * \param[in] v1 Vector over a finite field
 * \param[in] v2 Vector over a finite field
 * \param[in] size Size of the vectors
 */
void ffi_vec_add(ffi_field f, ffi_vec o, ffi_vec v1, ffi_vec v2, unsigned int size) {
  mpfq_vec_add(f, o, v1, v2, size);
}



/** 
 * \fn void ffi_vec_scalar_mul(ffi_field f, ffi_vec o, const ffi_vec v, const ffi_elt e, unsigned int size)
 * \brief This functions multiplies a vector over a finite field by a scalar
 *
 * \param[in] f Finite field
 * \param[out] o Vector equal to \f$ e \times v \f$
 * \param[in] v Vector over a finite field
 * \param[in] e Finite field element
 * \param[in] size Size of the vectors
 */
void ffi_vec_scalar_mul(ffi_field f, ffi_vec o, const ffi_vec v, const ffi_elt e, unsigned int size) {
  mpfq_vec_scal_mul(f, o, v, e, size);
}



/** 
 * \fn void ffi_vec_mul(ffi_field f, ffi_vec o, const ffi_vec v1, const ffi_vec v2, unsigned int size)
 * \brief Multiply two vector over a finite field
 *
 * Vector multiplication is defined as polynomial multiplication over \f$ GF(2^d)/(X^{size} - 1) \f$.
 *
 * \param[in] f Finite field
 * \param[out] o Product of <b>v1</b> and <b>v2</b>
 * \param[in] v1 Vector over a finite field
 * \param[in] v2 Vector over a finite field
 * \param[in] size Size of the vectors
 */
void ffi_vec_mul(ffi_field f, ffi_vec o, const ffi_vec v1, const ffi_vec v2, unsigned int size) {
  ffi_vec tmp;
  ffi_vec_init(f, &tmp, 2 * size - 1);
  mpfq_vec_conv(f, tmp, v1, size, v2, size);

  ffi_elt_set(f, o[size - 1], tmp[size - 1]);
  for(unsigned int i = 0 ; i < size - 1 ; ++i) {
    ffi_elt_add(f, o[i], tmp[i], tmp[i + size]);
  }

  ffi_vec_clear(f, tmp, 2 * size - 1);
}



/** 
 * \fn void get_bit(unsigned char* b, unsigned char c, unsigned int position)
 * \brief This function reads a bit from a byte
 *
 * \param[out] b Read bit stored as a byte
 * \param[in] c Byte to read from
 * \param[in] position Position of the bit to read
 */
static void get_bit(unsigned char* b, unsigned char c, unsigned int position) {
  *b = (c >> position) & 0x01;
}



/** 
 * \fn void set_bit(unsigned char* c, unsigned int position)
 * \brief This function sets a bit to 1 in a byte
 *
 * \param[out] c Byte to modify
 * \param[in] position Position of the bit to set
 */
static void set_bit(unsigned char* c, unsigned int position) {
  *c = *c | (1 << position);
}



/** 
 * \fn void ffi_vec_to_string(unsigned char* str2, const ffi_vec v, unsigned int size)
 * \brief This function parses a vector into a string
 *
 * This function only copies the bits of <b>v</b> containing information into <b>str2</b>. Indeed, there are only <b>FIELD_M</b> of them while the ffi_vec bit representation is larger due to MPFQ storing elements as pointer of unsigned longs.
 *
 * \param[out] str2 Output string
 * \param[in] v Vector to parse
 * \param[in] size Size of the vector
 */
void ffi_vec_to_string(unsigned char* str2, const ffi_vec v, unsigned int size) {
  unsigned int size1 = size * MPFQ_ULONGS * MPFQ_BITS_PER_ULONG;
  unsigned int size2 = (FIELD_M % 8 == 0) ? size * FIELD_M / 8 : size * FIELD_M / 8 + 1;

  unsigned char* str1 = (unsigned char*) v;
  memset(str2, 0, size2);

  unsigned int position1 = 0;
  unsigned int position2 = 0;

  unsigned char bit = 0;
  while(position1 < size1) {
    if(position1 % (MPFQ_ULONGS * MPFQ_BITS_PER_ULONG) < FIELD_M) {  
      get_bit(&bit, str1[position1 / 8], position1 % 8);
      if(bit == 1) set_bit(&str2[position2 / 8], position2 % 8);
      position2++;
    }  
    position1++;
  } 
}



/** 
 * \fn void ffi_vec_from_string(ffi_vec v, unsigned int size, const unsigned char* str2)
 * \brief This function parses a string into a vector
 *
 * This function turns the <b>FIELD_M</b> bits of information required to describe <b>v</b> into a ffi_vec bit representation which is larger due to MPFQ storing elements as pointer of unsigned longs.
 *
 * \param[out] v Output vector
 * \param[in] size Size of the vector <b>v</b>
 * \param[in] str2 String to parse
 */
void ffi_vec_from_string(ffi_vec v, unsigned int size, const unsigned char* str2) {
  unsigned int size1 = size * MPFQ_ULONGS * MPFQ_BITS_PER_ULONG;

  unsigned char str1[size1];
  memset(str1, 0, size1);

  unsigned int position1 = 0;
  unsigned int position2 = 0;

  unsigned char bit = 0;
  while(position1 < size1) {
    if(position1 % (MPFQ_ULONGS * MPFQ_BITS_PER_ULONG) < FIELD_M) {
      get_bit(&bit, str2[position2 / 8], position2 % 8);
      if(bit == 1) set_bit(&str1[position1 / 8], position1 % 8);
      position2++;
    }
    position1++;
  } 

  memcpy(v, str1, size1 / 8);
}



/** 
 * \fn void ffi_vec_print(ffi_field f, const ffi_vec v, unsigned int size)
 * \brief This function prints the value of a vector over a finite field
 *
 * \param[in] f Finite field
 * \param[in] v Vector over a finite field
 * \param[in] size Size of the vector <b>v</b>
 */
void ffi_vec_print(ffi_field f, const ffi_vec v, unsigned int size) {
  mpfq_vec_print(f, v, size);
}

