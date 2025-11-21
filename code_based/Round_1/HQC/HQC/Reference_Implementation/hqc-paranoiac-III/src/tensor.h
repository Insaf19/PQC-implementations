
/**
  * \file tensor.h
  * \brief Header file for tensor.c
  */

#ifndef TENSOR_H
#define TENSOR_H

#include "bch.h"
#include "repetition.h"

/**
 * \fn void tensor_code_encode(vector_u32* em, vector_u32* m)
 * \brief Encoding the message m to a codeword em using the tensor code
 *
 * First we encode the message using the BCH code, then we the repetition code to obtain
 * a tensor codeword. We extend the obtained codeword of dimension PARAM_N1N2 to a vector of dimension PARAM_N. 
 *
 * \param[out] em a pointer to a vector that is the codeword
 * \param[in] m a pointer to a vector that is the message
 */
void tensor_code_encode(vector_u32* em, vector_u32* m);

/**
 * \fn void tensor_code_decode(vector_u32* m, vector_u32* em)
 * \brief Decoding the codeword em to a message em using the tensor code
 *
 * \param[out] m a pointer to a vector that is the message
 * \param[in] em a pointer to a vector that is the codeword
 */
void tensor_code_decode(vector_u32* m, vector_u32* em);

#endif