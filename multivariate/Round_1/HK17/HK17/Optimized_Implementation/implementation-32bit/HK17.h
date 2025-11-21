//
//  HK17.h
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the declaration of the structures and functions used by the algorithm built on top of octonions
//	to provide its cryptographical characteristics 
//structures
//	HK17PrivateKey
//		this structure represents the secret data needed by the algorithm. It includes some extra fields like the module just because
//		it was comfortable for me to have it there.
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

#pragma once
#include "octonions.h"
#include "lib.h"
 
typedef struct {
	long long module;
	long long m;
	long long n;
	//todo: the following int will probably be deleted eventually
	int polynomialDegree;
	polynomialTerm* polynomial;
} HK17PrivateKey;

bool testKeyGeneration();
octonion buildRandomOctonion(long long module);

HK17PrivateKey* buildPrivateKey(int degree, long long module);

polynomialTerm* obtainPolynomial(int degree, long long module);

octonion calculateToken(octonion oA, octonion oB, HK17PrivateKey* privateKey);