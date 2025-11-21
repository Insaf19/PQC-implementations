
/**
  * \file parsing.h
  * \brief Functions to parse secret key, public key and ciphertext of the HQC scheme
  */

#ifndef PARSING_H
#define PARSING_H

#include "vector.h"

/**
	*\fn void hqc_secret_key_to_string(unsigned char* sk, const unsigned char* sk_seed, const unsigned char* pk)
	*\brief Parse a secret key into a string
	*
	* The secret key is composed of the seed used to generate vectors x and y.
	* As technicality, the public key is appended to the secret key in order to respect NIST API.
	* 
	* \param[out] sk String containing the secret key
	* \param[in] sk_seed Seed used to generate the secret key
	* \param[in] pk String containing the public key
	*/
void hqc_secret_key_to_string(unsigned char* sk, const unsigned char* sk_seed, const unsigned char* pk);

/**
	*\fn void hqc_secret_key_from_string(vector_u32* x, vector_u32* y, unsigned char* pk, const unsigned char* sk)
	*\brief Parse a secret key from a string
	*
	* The secret key is composed of the seed used to generate vectors x and y.
	* As technicality, the public key is appended to the secret key in order to respect NIST API.
	* 
	* \param[out] x vector_u32 representation of vector x 
	* \param[out] y vector_u32 representation of vector y
	* \param[out] pk String containing the public key
	* \param[in] sk String containing the secret key
	*/
void hqc_secret_key_from_string(vector_u32* x, vector_u32* y, unsigned char* pk, const unsigned char* sk);

/**
	*\fn void hqc_public_key_to_string(unsigned char* pk, const unsigned char* pk_seed, vector_u32* s)
	*\brief Parse a public key into a string
	* 
	* The public key is composed of the syndrome s as well as the seed used to generate the vector qr
	*
	* \param[out] pk String containing the public key 
	* \param[in] pk_seed Seed used to generate the public key
	* \param[in] s vector_u32 representation of vector s
	*/
void hqc_public_key_to_string(unsigned char* pk, const unsigned char* pk_seed, vector_u32* s);

/**
	*\fn void hqc_public_key_from_string(vector_u32* qr, vector_u32* s, const unsigned char* pk)
	*\brief Parse a public key from a string
	* 
	* The public key is composed of the syndrome s as well as the seed used to generate the vector qr
	*
	* \param[out] qr vector_u32 representation of vector qr
	* \param[out] s vector_u32 representation of vector s
	* \param[in] pk String containing the public key
	*/
void hqc_public_key_from_string(vector_u32* qr, vector_u32* s, const unsigned char* pk);

/**
	*\fn void hqc_ciphertext_to_string(unsigned char* ct, vector_u32* rho, vector_u32* v, unsigned char* d)
	*\brief Parse a ciphertext into a string 
	* 
	* The ciphertext is composed of vectors rho, v and hash d.
	*
	* \param[out] ct String containing the ciphertext
	* \param[in] rho vector_u32 representation of vector rho
	* \param[in] v vector_u32 representation of vector v
	* \param[in] d String containing the hash d
	*/
void hqc_ciphertext_to_string(unsigned char* ct, vector_u32* rho, vector_u32* v, unsigned char* d);

/**
	*\fn void hqc_ciphertext_from_string(vector_u32* rho, vector_u32* v, unsigned char* d, const unsigned char* ct)
	*\brief Parse a ciphertext from a string 
	* 
	* The ciphertext is composed of vectors rho, v and hash d.
	*
	* \param[out] rho vector_u32 representation of vector rho
	* \param[out] v vector_u32 representation of vector v
	* \param[out] d String containing the hash d
	* \param[in] ct String containing the ciphertext
	*/
void hqc_ciphertext_from_string(vector_u32* rho, vector_u32* v, unsigned char* d, const unsigned char* ct);

/**
	*\fn void hqc_vector_to_string(unsigned char* tab, vector_u32* v)
	*\brief Parse a vector to a string 
	* 
	* \param[out] tab String representing the vector
	* \param[in] v Pointer to a vector
	*/
void hqc_vector_to_string(unsigned char* tab, vector_u32* v);

#endif