//
//  octonions.h
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the declaration of the functions and structures required to operate with octonions.
//Structures
// octonion
//    This structure represents a single octonion, composed by a real component an 7 complex components.
// polynomialTerm
//    This structure represent a single term on a polynomial function, it is composed by the value (b) and te degree (n) of 
//    a term of the following form: b X^n

#ifndef oct_h
#define oct_h

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
 

typedef struct {
	 long long real;
	 long long e1;
	 long long e2;
	 long long e3;
	 long long e4;
	 long long e5;
	 long long e6;
	 long long e7;

} octonion;


typedef struct {
	long long value;
	int grade;
} polynomialTerm;

octonion summ(octonion o1, octonion o2, long long module);
octonion multiply(octonion o1, octonion o2, long long module);
octonion scalar(octonion o, long long esc, long long module);
octonion power(octonion oc, int potency, long long module);
//TODO: the dynamically allocated polynomial term is not necessary since the degree of each polynome depends on the bits used by the algorithm and it is
//already defined on a document that JK has.
octonion calculateF(octonion oa, polynomialTerm* f, int termCount, long long module);


bool octonionEquality(octonion o1, octonion o2);

octonion newOctonion(long long real, long long e1, long long e2, long long e3, long long e4, long long e5, long long e6, long long e7);

long long bigModMult(long long  a, long long  b, long long c);
#endif // !oct_h
