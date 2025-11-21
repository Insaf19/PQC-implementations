
/**
  * \file bch.h
  * \brief Header file for bch.c
  *
  * For more details on the BCH code used and the decoding procedure please check <a href="../doc_bch.pdf" target="_blank"><b>BCH code</b></a>.
  *
  */

#ifndef BCH_H
#define BCH_H

#include "vector.h"

/* Portions of this code are somewhat inspired from the implementation of BCH code found here https://github.com/torvalds/linux/blob/master/lib/bch.c */



/**
 * \struct gf_tables
 * \brief a structure of a Galois Field Log and Anti-Log tables
 *
 * This structure allows to storage Log and Anti-Log tables.
 */
typedef struct gf_tables {
	uint16_t size; /*!< The size of the arrays of this structure*/
	int16_t* log_tab; /*!< An array that contains the Log values */
	int16_t* antilog_tab; /*!< An array that contains the Anti-Log values */
} gf_tables;

/**
 * \struct sigma_poly
 * \brief a structure of a Galois Field polynomial
 *
 * This structure allows to storage of a polynomial with coordinates in \f$ GF(2^{10}) \f$. We use 
 * tis structure to compute the error location polynomial in the decoding phase of BCH code.
 */
typedef struct sigma_poly {
	uint16_t dim; /*!< The size of the array value of this structure*/
	uint16_t deg; /*!< The degree of the polynomial stored in the array value*/
	int16_t* value; /*!< An array that contains the coordinates of the polynomial*/
} sigma_poly;

/**
 * \struct syndrome_set
 * \brief a structure of a Syndromes set
 *
 * This structure allows to storage of a set of syndromes.
 */
typedef struct syndrome_set {
uint16_t size; /*!< The size of the array tab of this structure*/
int16_t* tab; /*!< An array that contains the values of syndromes*/
} syndrome_set;

/**
 * \fn int16_t gf_get_antilog(gf_tables* tables, int16_t i)
 * \brief Gets the Anti-Log value of the input i
 *
 * \param[in] gf_tables a pointer to a Galois Field Log and Anti-Log tables
 * \param[in] i an integer
 * \return integer corresponding to the Anti-Log value of i
 */
int16_t gf_get_antilog(gf_tables* tables, int16_t i);

/**
 * \fn int16_t gf_get_log(gf_tables* tables, int16_t i)
 * \brief Gets the Log value of the input i
 *
 * \param[in] gf_tables a pointer to a Galois Field Log and Anti-Log tables
 * \param[in] i an integer
 * \return integer corresponding to the Log value of i
 */
int16_t gf_get_log(gf_tables* tables, int16_t i);

/**
 * \fn int16_t	gf_mod(int16_t i)
 * \brief Computes the reminder modulo \f$ 2^{10} - 1\f$
 *
 * \param[in] i an integer
 * \return integer corresponding to the reminder modulo \f$ 2^{10} - 1\f$
 */
int16_t	gf_mod(int16_t i);

/**
 * \fn void bch_code_encode(vector_u32* em, vector_u32* m)
 * \brief Encode a message using the BCH code 
 *
 * This function encode a message of PARAM_K bits to a message of size PARAM_N1 bits. We perform a systematic encoding using a linear (PARAM_N1 - PARAM_K)-stage shift register with feedback
 * connections based on the generator polynomial of the BCH code \cite lin1983error (Chapter 4 Cyclic Codes - page 95).
 *
 * For reasons of clarity and comprehensibility, we achieve the encoding process in four steps:
 *    <ol>
 * 		<li> First, we convert the input vector m which contains the message to be encoded to an array where each coordinate of the vector is stored in an unsigned char.
 * 		<li> Second, we retrieve the generator polynomial \f$ g \f$ of the BCH code from its hexadecimal representation (the polynomial is given by its hexadecimal representation in the file parameters.h)
 * 		<li> Third, we use an LFSR as described in \cite lin1983error to encode the message and build the codeword
 *		<li> Fourth, we convert the codeword which is stored in an unsigned char array to vector em
 *		</ol>
 *
 * \param[out] em a pointer to a vector that is the encoded message
 * \param[in] m a pointer to a vector that is the message
 */
void bch_code_encode(vector_u32* em, vector_u32* m);

/**
 * \fn void codeword_to_vector(vector_u32* o, uint8_t* v)
 * \brief Converts an array that contains a codeword to a vector v
 *
 * \param[out] o a pointer to a vector
 * \param[in] v a pointer to an array of unsigned char elements
 */
void codeword_to_vector(vector_u32* o, uint8_t* v);

/**
 * \fn void get_generator_poly(uint8_t* g)
 * \brief Parse the generator polynomial \f$ g \f$ of the BCH code from its hexadecimal representation
 *
 * This functions stores each coordinate of the generator polynomial in an unsigned char
 *
 * \param[out] g a pointer to an array of unsigned char
 */
void get_generator_poly(uint8_t* g);

/**
 * \fn void vector_message_to_array(uint8_t* o, vector_u32* v)
 * \brief Converts a vector v that contains the message to be encoded to an array of unsigned char. Each coordinate of the vector is stored in an unsigned char.
 *
 * \param[out] o a pointer to an array of unsigned char
 * \param[in] v a pointer to a vector 
 */
void vector_message_to_array(uint8_t* o, vector_u32* v);

/**
 * \fn void lfsr_encoder(uint8_t* em, uint8_t* g, uint8_t* m)
 * \brief Encode the message stored in the array m to a codeword em using the generator polynomial \f$ g \f$ of the BCH code
 *
 * \param[out] em a pointer to an array that is the codeword
 * \param[in] g a pointer to an array that is the generator polynomial
 * \param[in] m a pointer to an array that is the message to encode
 */
void lfsr_encoder(uint8_t* em, uint8_t* g, uint8_t* m);

/**
 * \fn void bch_code_decode(vector_u32* m, vector_u32* em)
 * \brief Decode a supposed BCH codeword
 *
 * This function takes as input a pointer to a vector that the received BCH codeword
 * and return a pointer to vector that is the original message being encoded. The decoding procedure follows the steps described by
 * Shu. Lin and Daniel J. Costello in Error Control Coding: Fundamentals and Applications \cite lin1983error. In the following the vectors are considered as polynomials.
 *
 * - The decoding procedure consists of four major steps:
 *    <ol>
 * 		<li> The first step is the computation of 2 * PARAM_DELTA (with PARAM_DELTA being the error correction capacity of the BCH code) syndromes using the received polynomial.
 * 		<li> The second step is the computation of the error-location polynomial elp(x) from the 2 * PARAM_DELTA syndromes computed in the first step
 * 		<li> The third step is to find the error-location numbers by calculating the roots of the polynomial elp(x) and returning their inverse
 *		<li> The fourth step is the correction of errors in the received polynomial
 *		</ol>
 *
 *
 * \param[out] m a pointer to a vector that is the decoded codeword
 * \param[in] em a pointer to a vector that is supposed to be a codeword
 */
void bch_code_decode(vector_u32* m, vector_u32* em);

/**
 * \fn sigma_poly* sigma_poly_init(int16_t dim)
 * \brief Initializes a structure that can store a polynomial having coordinates in \f$ GF(2^{10}) \f$
 *
 * This function is used to initialize sigma_poly structure by allocating the necessary
 * memory.
 *
 * \return a pointer to a sigma_poly
 */
sigma_poly* sigma_poly_init(int16_t dim);

/**
 * \fn int sigma_poly_clear(sigma_poly* poly)
 * \brief Free the allocated memory for a sigma_poly
 *
 * \param[in] sigma_poly a pointer to a sigma_poly structure
 * \return void
 */
int sigma_poly_clear(sigma_poly* poly);

/**
 * \fn void sigma_poly_copy(sigma_poly* p1, sigma_poly* p2)
 * \brief Copy a Galois Field polynomial p2 the Galois Field polynomial p1
 *
 * \param[out] p1 a pointer to a sigma_poly
 * \param[in] p2 a pointer to a sigma_poly
 */
void sigma_poly_copy(sigma_poly* p1, sigma_poly* p2);

/**
 * \fn gf_tables* gf_tables_init()
 * \brief Initializes a Galois Field Log and Anti-Log tables
 *
 * This function is used to initialize gf_tables structure by allocating the necessary
 * memory for the Galois Field Log and Anti-Log tables.
 *
 * \return a pointer to a gf_tables
 */
gf_tables* gf_tables_init();

/**
 * \fn void gf_tables_clear(gf_tables* gf_tables)
 * \brief Free the allocated memory for a gf_tables
 *
 * \param[in] gf_tables a pointer to a Galois Field Log and Anti-Log tables
 */
void gf_tables_clear(gf_tables* gf_tables);

/**
 * \fn void gf_generation(gf_tables* gf_tables)
 * \brief Generates the Log and Anti-Log tables for a \f$ GF(2^{10}) \f$
 *
 * We will be working in the Galois Field \f$ GF(2^{m}) \f$ (with \f$ m = 10 \f$), this field can be constructed using the primitive polynomial \f$ p(X) = 1 + X^3 + X^{10}\f$ of degree \f$ 10 \f$ over \f$ GF(2) \f$. 
 * Let \f$p(\alpha) = 1 + \alpha^3 + \alpha^{10} = 0\f$, then using the identity \f$\alpha^{10} = \alpha^3 + 1\f$, we can construct a polynomial representation of the elements of \f$ GF(2^{10}) \f$.
 * We can construct a binary representation using the polynomial representation. In fact, let  \f$ a_0 + a_1 \alpha +a_2 \alpha^2 + ... + a_9 \alpha^{9}\f$ be the polynomial representation of \f$ \beta\f$,
 * then \f$ \beta \f$ can be represented by the binary 10-tuple \f$ (a_0, a_1, ... , a_9) \f$. In the other hand, we have that \f$ GF(2^{10}) = \{0, 1, \alpha, \alpha^2, ..., \alpha^{2^{10} - 2} \}\f$.
 * Thus, we have three representations of \f$ GF(2^{10}) \f$; a polynomial representation, a binary representation and a power representation. 
 * To perform computations (additions and multiplications) in a Galois Field, we use look-up tables. As it is was explained in \cite morelos2006art, we will use Log and Anti-Log tables:
 *		<ol>
 * 		<li> Anti-Log table: is used when performing additions. At index \f$ i \f$, it gives the value of the binary vector that corresponds to the element \f$ \alpha^i \f$.
 * 		<li> Log table: is used when performing multiplications. At index \f$ i \f$, it gives \f$ log(i) \f$ which is the power of \f$ \alpha^{log(i)} \f$ that corresponds to the binary vector represented by the integer \f$ i \f$.
 *		</ol>
 *
 * \param[in] gf_tables a pointer to a Log and Anti-Log tables
 */
void gf_generation(gf_tables* gf_tables);

/**
 * \fn syndrome_set* syndrome_init()
 * \brief Initializes a syndrome_set structure
 *
 * This function is used to initialize syndrome_set structure by allocating the necessary
 * memory to store a set of syndromes of a BCH code.
 *
 * \return a pointer to a syndrome_set
 */
syndrome_set* syndrome_init();

/**
 * \fn void syndrome_clear(syndrome_set* synd_set)
 * \brief Free the allocated memory for a syndrome_set
 *
 * \param[in] synd_set a pointer to a syndrome_set
 */
void syndrome_clear(syndrome_set* synd_set);

/**
 * \fn void syndrome_gen(syndrome_set* synd_set, gf_tables* tables, vector_u32* v)
 * \brief Generates 2 * PARAM_DELTA syndromes from the received vector
 *
 * \param[out] synd_set pointer to the structure syndrome_set that contains the computed syndromes
 * \param[in] tables a pointer to a gf_tables
 * \param[in] v a pointer to a vector
 */
void syndrome_gen(syndrome_set* synd_set, gf_tables* tables, vector_u32* v);

/**
 * \fn void get_error_location_poly(sigma_poly* elp, gf_tables* tables, syndrome_set* synd_set)
 * \brief Computes the error location polynomial
 *	
 * We use the simplified Berlekamp's algorithm for finding the error location polynomial for binary BCH codes \cite joiner1995decoding \cite lin1983error.
 *  
 * \param[out] elp a pointer to the structure sigma_poly that contains the computed polynomial
 * \param[in] tables a pointer to a gf_tables
 * \param[in] synd_set a pointer to the structure syndrome_set that contains the set of syndromes computed by the function syndrome_gen
 */
void get_error_location_poly(sigma_poly* elp, gf_tables* tables, syndrome_set* synd_set);

/**
 * \fn void chien_search(uint16_t* error_pos, uint16_t* size, gf_tables* tables, sigma_poly* elp)
 * \brief Computes the error location numbers
 *	
 * We use Chien procedure for searching error-location numbers \cite lin1983error \cite chien1964cyclic. The Chien search algorithm computes the roots of the 
 * error location polynomial and then returns their inverse. There are two remarks on how we implemented this algorithm:
 *		<ol>
 * 		<li> There is no need to evaluate the error location polynomial in the field elements \f$ \alpha^i \f$ for 
 *	  \f$ i \in \{1, ... , \text{2^PARAM_M -1 - PARAM_N1} \} \f$. In fact since we are using a shortened BCH code the inverses of the roots in this range will
 *    not be a valid positions (the position will be greater than the PARAM_N1). For that, we started the evaluation of the error location polynomial at 2^PARAM_M - PARAM_N1.
 *    
 * 		<li> We use the fact that the ith term in elp\f$ (\alpha^{l + 1})\f$ can be computed from the ith term in elp\f$(\alpha^{l})\f$ by multiplying that term by \f$ \alpha^i \f$
 *		</ol>
 *  
 * \param[out] error_pos a pointer to an array that contains the error location numbers
 * \param[in] tables a pointer to gf_tables
 * \param[in] elp a pointer to sigma_poly a structure that contains the error location polynomial
 */
void chien_search(uint16_t* error_pos, uint16_t* size, gf_tables* tables, sigma_poly* elp);

/**
 * \fn void error_poly_gen(vector_u32* error_poly, uint16_t* error_pos, uint16_t size)
 * \brief Computes the error polynomial which consist of the error pattern
 *
 * This function puts the error location numbers in a binary polynomial. For example if the error location numbers are \f$ \alpha^{130} \f$, \f$ \alpha^{80} \f$, and \f$ \alpha^{11} \f$,
 * then the error polynomial is \f$ X^{11} + X^{80} + X^{130} \f$ 
 *  
 * \param[out] error_poly a pointer to a vector that contains the error polynomial
 * \param[in] error_pos a pointer to an array that contains the error location numbers
 * \param[in] size an integer that is the size of the array error_pos
 */
void error_poly_gen(vector_u32* error_poly, uint16_t* error_pos, uint16_t size);

/**
 * \fn void get_message_from_codeword(vector_u32* o, vector_u32* v)
 * \brief Retrieve the message from the decoded codeword
 *  
 * This function recover the message from a codeword. Since we have performed a systematic encoding, the message is the last PARAM_K bits of the vector v.
 *
 * \param[out] o a pointer to a vector that contains the message
 * \param[in] v a pointer to a vector that contains a codeword
 */
void get_message_from_codeword(vector_u32* o, vector_u32* v); 

#endif