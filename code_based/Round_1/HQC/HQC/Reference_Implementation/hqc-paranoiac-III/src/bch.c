
/**
* \file bch.c
* \brief Implementation of BCH code
*/

#include "bch.h"

int16_t gf_get_antilog(gf_tables* tables, int16_t i) {
	return tables->antilog_tab[i];
}

int16_t gf_get_log(gf_tables* tables, int16_t i) {
	return tables->log_tab[i];
}

int16_t	gf_mod(int16_t i) {
	return (i < PARAM_GF_MUL_ORDER) ? i : i - PARAM_GF_MUL_ORDER; 
}

void bch_code_encode(vector_u32* em, vector_u32* m) {
	uint8_t tmp1[PARAM_K];
	uint8_t tmp2[PARAM_N1];
	uint8_t g [PARAM_G];
	memset(tmp2, 0, PARAM_N1);

	vector_message_to_array(tmp1, m);
	get_generator_poly(g);
	lfsr_encoder(tmp2, g, tmp1);
	codeword_to_vector(em, tmp2);
}

void vector_message_to_array(uint8_t* o, vector_u32* v) { 
	for (uint8_t i = 0 ; i < v->dim ; ++i)	{
		for (uint8_t j = 0 ; j < 32 ; ++j) {
			o[j + i * 32] = v->value[i] >> (31 - j) & 1;
		}
	}
}

void get_generator_poly(uint8_t* g) {
	char* g_poly_string = GENERATOR_POLY, *pos = g_poly_string;
	uint8_t g_bytes_size = (PARAM_G / 8) + 1;
	unsigned char tmp[g_bytes_size];

	for (int i = 0; i < g_bytes_size; ++i)	{
		sscanf(pos, "%2hhx", &tmp[i]);
		pos += 2;
	}

	for (int i = 0; i < (g_bytes_size - 1) ; ++i)	{
		for (int j = 0; j < 8; ++j)	{
			g[j + i*8] = (tmp[i] & (1 << (7 - j))) >> (7 - j);
		}
	}

	for (int j = 0; j < PARAM_G % 8 ; ++j)	{
			g[j + (g_bytes_size - 1) * 8] = (tmp[g_bytes_size - 1] & (1 << (7 - j))) >> (7 - j);
	}
}

void lfsr_encoder(uint8_t* em, uint8_t* g, uint8_t* m) {
	int gate_value = 0;

	// Compute the Parity-check digits

	for (int i = PARAM_K-1; i >= 0; --i) {

		gate_value = m[i] ^ em[PARAM_N1 - PARAM_K - 1];
		
		if (gate_value) {
			for (int j = PARAM_N1 - PARAM_K - 1; j > 0; --j)	{
				em[j] = em[j-1] ^ g[j];				
			}

		} else {
			for (int j = PARAM_N1 - PARAM_K - 1; j > 0; --j)	{
				em[j] = em[j-1];			
			}	
		}

		em[0] = gate_value;	
	}

	// Add the message 

	int index = 0;
	for (int i = PARAM_N1 - PARAM_K ;  i < PARAM_N1 ; ++i) {
		em[i] = m[index];
		index++;
	}
}

void codeword_to_vector(vector_u32* o, uint8_t* v) {
	for (uint8_t i = 0 ; i < (o->dim - 1) ; ++i) {
		for (uint8_t j = 0 ; j < 32 ; ++j) {
			o->value[i] |= v[j + i * 32] << (31 - j);
		}
	}

	for (uint8_t j = 0 ; j < PARAM_N1 % 32 ; ++j) {
		o->value[o->dim - 1] |= ((uint32_t) v[j + 32 * (o->dim - 1)]) << (31 - j);
	}
}

void bch_code_decode(vector_u32* m, vector_u32* em) {
	// Generate Galois Field GF(2^10) using the primitive polynomial defined in PARAM_POLY
	// GF(2^10) is represented by the lookup tables (Log Anti-Log tables)
	gf_tables* tables = gf_tables_init();
 	gf_generation(tables);

 	// Calculate the 2 * PARAM_DELTA syndromes
	syndrome_set* synd_set = syndrome_init(); 
	syndrome_gen(synd_set, tables, em); 

	// Using the simplified Berlekamp's algorithm we compute the error location polynomial elp
  sigma_poly* elp = sigma_poly_init(2 * PARAM_DELTA);
  get_error_location_poly(elp, tables, synd_set);

  #ifdef VERBOSE
    printf("\n\nsyndromes: "); for(uint16_t i = 0 ; i < synd_set->size ; ++i) printf("%d ,", synd_set->tab[i]);
    printf("\n\nerror location polynomial sigma(x) = : "); 
    for(uint16_t i = 0 ; i < elp->deg ; ++i) printf("%d x^%d + ", elp->value[i], i);
    printf("%d x^%d", elp->value[elp->deg], elp->deg);
  #endif

  // Compute the error location numbers using the Chien Search algorithm
  uint16_t error_pos [PARAM_DELTA];
 	memset(error_pos, 0, PARAM_DELTA * 2);
 	uint16_t size = 0;
 	chien_search(error_pos, &size, tables, elp); 
 	#ifdef VERBOSE
    printf("\n\nthe error location numbers: "); for(uint16_t i = 0 ; i < size ; ++i) printf("%d ,", error_pos[i]);
  #endif

 	// Compute the error polynomial 
 	vector_u32* error_poly = vector_u32_init(UTILS_BCH_CODEWORD_ARRAY_SIZE);
 	error_poly->by_position_flag = 0;
 	error_poly_gen(error_poly, error_pos, size);

 	#ifdef VERBOSE
    printf("\n\nThe error polynomial in binary representation : "); vector_u32_print(error_poly, UTILS_BCH_CODEWORD_ARRAY_SIZE);
  #endif

 	// Find the message from the decoded codeword
 	vector_u32* tmp = vector_u32_init(UTILS_BCH_CODEWORD_ARRAY_SIZE);
 	vector_u32_add(tmp, error_poly, em);
	get_message_from_codeword(m, tmp);
	
	gf_tables_clear(tables);  
	syndrome_clear(synd_set);
  sigma_poly_clear(elp);
  vector_u32_clear(error_poly);
  vector_u32_clear(tmp);
}

void get_message_from_codeword(vector_u32* o, vector_u32* v) {
	int val = PARAM_N1 - PARAM_K;

	for (uint8_t i = 0 ; i < UTILS_VEC_K_ARRAY_SIZE ; ++i)	{
		int index = (val / 32) + i ;
		uint32_t  m1 = (v->value[index] & UTILS_MASK_M1) << (val % 32);
		uint32_t  m2 = (v->value[index + 1] & UTILS_MASK_M2) >> (32 - (val % 32));
		o->value[i] = m1 | m2;
	}
}

sigma_poly* sigma_poly_init(int16_t dim){
	sigma_poly* poly = (sigma_poly*) malloc(sizeof(sigma_poly));
	poly->dim = dim;
	poly->value = calloc(dim,sizeof(int16_t));
	
	return poly;
}

int sigma_poly_clear(sigma_poly* poly){
	free(poly->value);
	free(poly);
	return 0;
}

void sigma_poly_copy(sigma_poly* p1, sigma_poly* p2) {
	for (int i = 0; i <= p2->deg ; ++i)	{
		p1->value[i] = p2->value[i];
	}
	p1->deg = p2->deg;
}

gf_tables* gf_tables_init() {
	gf_tables* tables = (gf_tables*) malloc(sizeof(gf_tables));

	tables->size = PARAM_GF_MUL_ORDER + 1;
	tables->log_tab = (int16_t*) malloc((tables->size) * sizeof(int16_t));
	tables->antilog_tab = (int16_t*) malloc((tables->size) * sizeof(int16_t));
	
	return tables;
}

void gf_tables_clear(gf_tables* gf_tables) {
	free(gf_tables->log_tab);
	free(gf_tables->antilog_tab);
	free(gf_tables);
}

void gf_generation(gf_tables* gf_tables) {
	const uint16_t k 	= 1 << PARAM_M; // k = 2^m = 2^10
	const uint16_t poly = PARAM_POLY; // get the primitive polynomial
	uint16_t val = 1;
	uint16_t alpha = 2; // alpha the root of the primitive polynomial is the primitive element of GF(2^10)

	for(int i = 0 ; i < PARAM_GF_MUL_ORDER ; ++i){
		gf_tables->antilog_tab[i] = val;
		gf_tables->log_tab[val] = i;
		val = val * alpha; // by multiplying by alpha and reducing later if needed we generate all the elements of GF(2^10)
		if(val >= k){ // if val is greater than 2^10
			val ^= poly; // replace alpha^10 by alpha^3 + 1
		}
	}

	gf_tables->antilog_tab[PARAM_GF_MUL_ORDER] = 1; 
	gf_tables->log_tab[0] = -1; // by convention 
}	

syndrome_set* syndrome_init() {
	syndrome_set*	synd_set = (syndrome_set*) malloc(sizeof(syndrome_set));
	synd_set->size = 2 * PARAM_DELTA;
	synd_set->tab =	calloc((synd_set->size), sizeof(int16_t));
	
	return synd_set;
}

void syndrome_clear(syndrome_set* synd_set) {
	free(synd_set->tab);
	free(synd_set);
}

void syndrome_gen(syndrome_set* synd_set, gf_tables* tables, vector_u32* v) {
	uint8_t tmp_array[PARAM_N1];
	// For clarity of computation we separate the coordinates of the vector v by putting each coordinate in an unsigned char.
	for (uint8_t i = 0; i < (v->dim - 1) ; ++i) {
		for (uint8_t j = 0; j < 32; ++j) {
			tmp_array[j + i * 32] = v->value[i] >> (31 - j)	& 1;	
		}
	}

	for (uint8_t i = 0; i < PARAM_N1 % 32 ; ++i)	{
		tmp_array [i + (v->dim - 1) * 32] = v->value[v->dim -1] >> (31 - i)	& 1;
	}

	// Evaluation of the polynomial corresponding to the vector v in alpha^i for i in {1, ..., 2 * PARAM_DELTA}
	for(uint16_t i = 0; i < PARAM_N1 ; ++i) {
		int tmp_value = 0;
		if(tmp_array[i]) {
			for(uint16_t j = 1 ; j < synd_set->size + 1 ; ++j) {			
				tmp_value = gf_mod(tmp_value + i);
				synd_set->tab[j - 1] ^= gf_get_antilog(tables, tmp_value);
			}
		}
	}

}

void get_error_location_poly(sigma_poly* elp, gf_tables* tables, syndrome_set* synd_set) {

	// Find the error location polynomial via Berlekamp's simplified algorithm as described by
	// Laurie L. Joiner and John J. Komo, the comments are following their terminology 
	uint32_t t = PARAM_DELTA;
	uint32_t n = PARAM_GF_MUL_ORDER;
	uint32_t i, j, tmp, l, dp = 1, d = synd_set->tab[0];

	sigma_poly* pelp = sigma_poly_init(2*t);
	sigma_poly* elp_copy = sigma_poly_init(2*t);
	int k, pp = -1;

	pelp->deg = 0;
	pelp->value[0] = 1;
	elp->deg = 0;
	elp->value[0] = 1;

	for (i = 0; (i < t) && (elp->deg <= t); i++) {

		if (d) {
			// Finding another row
			k = 2*i-pp;
			sigma_poly_copy(elp_copy, elp);
			
			// Compute d_mu * d__rho^(-1) 			
			tmp = gf_get_log(tables, d) + n - gf_get_log(tables, dp);
			// Compute sigma(mu+1)[x] 
			for (j = 0; j <= pelp->deg; j++) {

				if (pelp->value[j]) {
					l = gf_get_log(tables, pelp->value[j]);
					elp->value[j+k] ^= gf_get_antilog(tables, (tmp + l) % n);
				}

			}

			// Compute l_mu + 1 the degree of sigma(mu+1)[x]
			tmp = pelp->deg+k;
			if (tmp > elp->deg) {
				elp->deg = tmp;
				sigma_poly_copy(pelp, elp_copy);
				dp = d;
				pp = 2*i;
			}
		}

		// compute discrepancy d_mu+1 
		if (i < t-1) {
			d = synd_set->tab[2*i+2];
			for (j = 1; j <= elp->deg; j++){
				int tmp_val = gf_get_log(tables, synd_set->tab[2 * i + 2 - j]);
				if((elp->value[j])  && (tmp_val != -1))
					d ^= gf_get_antilog(tables, gf_mod(gf_get_log(tables, elp->value[j]) + tmp_val));
			}	
		}
	}

	sigma_poly_clear(pelp);
	sigma_poly_clear(elp_copy);
}

void chien_search(uint16_t* error_pos, uint16_t* size, gf_tables* tables, sigma_poly* elp) {
	int i = elp->deg + 1;
	// Put the coordinates of the error location polynomial in the log format. Its better for multiplication.
	while(i--) {
		elp->value[i] = gf_get_log(tables, elp->value[i]);
	}
	
	int l = PARAM_GF_MUL_ORDER - PARAM_N1;

	int tmp = 0;
	
	// Compute elp(alpha^l)
	for(uint16_t j = 1 ; j < elp->deg + 1 ; ++j){
		tmp = gf_mod(tmp + l);
		if (elp->value[j] != -1) {
			elp->value[j] = gf_mod(elp->value[j] + tmp);
		}
	}
	// Evaluate elp in a field element and check if it is a root of elp
	*size = 0;
	for(int i = l + 1 ; i <= PARAM_GF_MUL_ORDER ; ++i) {
		int sum = 0;
		int j = elp->deg + 1;
		while(--j) {
			if (elp->value[j] != -1) {
				elp->value[j] = gf_mod(elp->value[j] + j);
				sum ^= gf_get_antilog(tables, elp->value[j]);
			}
		}
		// Compute the inverse and update the list of error location numbers
		if (sum == 1) {
			error_pos[*size] = PARAM_GF_MUL_ORDER - i;
			++(*size);
		}
	}
}

void error_poly_gen(vector_u32* error_poly, uint16_t* error_pos, uint16_t size) {
	for (int i = 0; i < size; ++i) {
		int index = error_pos[i] / 32;
		error_poly->value[index] ^= 1 << (31 - (error_pos[i] % 32));
	}
}