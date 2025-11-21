//
//  HK17.c
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the definition of the functions used by the algorithm built on top of octonions
//	to provide its cryptographical characteristics 
//functions
// testKeyGeneration
//    performs the key creation, exchange, and validation for testing purposes
// buildRandomOctonion
//    builds a random octonion of mod m using the rng functions present in lib.h
// buildPrivateKey
//    builds a random private key of mod m with a polynomial function of the provided degree with the rng functions present in lib.h
// obtainPolynomial
//    builds a random polynomial function of mod m using the provided degree with the rng functions present in lib.h
// calculateToken
//    calculates token required by the algorithm using the provided octonions and private key.
#include "HK17.h"



octonion buildRandomOctonion(long long module)
{ 
	return newOctonion(
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module),
		randomRange(1,module));

}
polynomialTerm* obtainPolynomial(int degree, long long  module) {
	//TODO: remove this malloc from the obtain polynomial.
	polynomialTerm* polynomial = (polynomialTerm*) malloc(sizeof(polynomialTerm)*degree);
	int index = 0;
	for (int i = degree - 1; i > -1; i--)
	{
		polynomialTerm  term;
		term.value = randomRange(1, module);
		term.grade = i;
		polynomial[index++] = term;
	}
	return polynomial;
}

HK17PrivateKey* buildPrivateKey(int degree, long long module) {

	HK17PrivateKey* result = (HK17PrivateKey*) malloc(sizeof(HK17PrivateKey));
	result->m = randomRange(2, 257);
	result->n = randomRange(2, 257);
	result->module = module;
	result->polynomial = obtainPolynomial(degree, module);
	result->polynomialDegree = degree;
	return result;
}


octonion calculateToken(octonion oA, octonion oB, HK17PrivateKey* privateKey) {
	octonion result;
	octonion oFa = calculateF(oA, privateKey->polynomial, privateKey->polynomialDegree, privateKey->module);
	//TODO: compress this.
	result = power(oFa, privateKey->m, privateKey->module);
	result = multiply(result, oB, privateKey->module);
	result = multiply(result, power(oFa, privateKey->n, privateKey->module), privateKey->module);
	return result;
}