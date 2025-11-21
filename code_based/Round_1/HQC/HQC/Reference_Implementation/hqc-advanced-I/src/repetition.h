
/**
  * \file repetition.h
  * \brief Header file for repetition.c
  */

#ifndef REPETITION_H
#define REPETITION_H

#include <string.h>
#include "vector.h"

/**
 * \fn void repetition_code_encode(vector_u32* em, vector_u32* m)
 * \brief Encoding each bit in the message m using the repetition code
 *
 * We obtain a vector of repetition codewords
 *
 * \param[out] em a pointer to a vector that is the codeword
 * \param[in] m a pointer to a vector that is the message
 */
void repetition_code_encode(vector_u32* em, vector_u32* m);

void array_to_vector(vector_u32* o, uint8_t* v);

/**
 * \fn void repetition_code_decode(vector_u32* m, vector_u32* em)
 * \brief Decoding the codewords in the vector em to a message m using the repetition code
 *
 * We use a majority decoding. In fact we have that PARAM_N2 = 2 * PARAM_T + 1, thus,
 * if the Hamming weight of the vector is greater than PARAM_T, the codeword is decoded
 * to 1 and 0 otherwise.
 *
 * \param[out] m a pointer to a vector that is the message
 * \param[in] em a pointer to a vector that is the codeword
 */
void repetition_code_decode(vector_u32* m, vector_u32* em);

#endif