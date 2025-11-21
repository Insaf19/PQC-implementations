//
//  octonions.c
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the definition of the functions required to operate with octonions.
//Functions
// summ
//    this operation performs (o1 + o2)%m
// scalar
//    this operation performs (o1 * n)%m
// multiply
//    this operation performs (o1 * o2)%m
// power
//    this operation performs (o1 ^ n)%m
// calculateF
//    this operation applies the provided polynomial terms (terms) of size termCount to the octonion o1 on mod m
// octonionEquality
//    this operation returns  o1== o2
// newOctonion
//    this operation builds an octonion composed by the given arguments
// mod
//    this functions returns the mathematically correct value of a%m
// bigModMult
//    this functions can execute (a*b )%m for any two given a and b without overflowing as long as m is a valid unsigned long
 
#include "octonions.h"

#ifndef octonions_c
#define octonions_c
long long mod(long long value, long long mod)
{
	return ((value%mod) + mod) % mod;
}
//Summ o1+o2
octonion summ(octonion o1, octonion o2, long long module)
{
	octonion result;
	result.real = mod(o1.real + o2.real, module);
	result.e1 = mod(o1.e1 + o2.e1, module);
	result.e2 = mod(o1.e2 + o2.e2, module);
	result.e3 = mod(o1.e3 + o2.e3, module);
	result.e4 = mod(o1.e4 + o2.e4, module);
	result.e5 = mod(o1.e5 + o2.e5, module);
	result.e6 = mod(o1.e6 + o2.e6, module);
	result.e7 = mod(o1.e7 + o2.e7, module);

	return result;
}
long long bigModMult(long long  a, long long  b, long long c) {
	long long x = a * b;
	if (a != 0 && x / a != b) {
		// overflow handling
		if (a == 0 || b == 0) {
			return 0;
		}
		if (a == 1) {
			return b %c;
		}
		if (b == 1) {
			return a%c;
		}

		// Returns: (a * b/2) mod c
		long long a2 = bigModMult(a, b / 2, c);

		return (((a % c)*(b & 1)) + (a2 + a2)) % c;
		// Even factor
		//if ((b & 1) == 0) {
		//	// [((a * b/2) mod c) + ((a * b/2) mod c)] mod c
		//	return (a2 + a2) % c;
		//}
		//else {
		//	// Odd exponent
		//	// [(a mod c) + ((a * b/2) mod c) + ((a * b/2) mod c)] mod c
		//	return ((a % c) + (a2 + a2)) % c;
		//}
	}
	else {
		return x%c;
	}

}
//Multiply an octonion by a value
octonion scalar(octonion o, long long esc, long long module)
{
	octonion result;
	result.real = bigModMult(esc, o.real, module);
	result.e1 = bigModMult(esc, o.e1, module);
	result.e2 = bigModMult(esc, o.e2, module);
	result.e3 = bigModMult(esc, o.e3, module);
	result.e4 = bigModMult(esc, o.e4, module);
	result.e5 = bigModMult(esc, o.e5, module);
	result.e6 = bigModMult(esc, o.e6, module);
	result.e7 = bigModMult(esc, o.e7, module);
	return result;
}

//multiply two octonions o1*o2
octonion multiply(octonion o1, octonion o2, long long module)
{
	octonion result;
	result.real =
		bigModMult(o1.real, o2.real, module)
		- bigModMult(o1.e1, o2.e1, module)
		- bigModMult(o1.e2, o2.e2, module)
		- bigModMult(o1.e3, o2.e3, module)
		- bigModMult(o1.e4, o2.e4, module)
		- bigModMult(o1.e5, o2.e5, module)
		- bigModMult(o1.e6, o2.e6, module)
		- bigModMult(o1.e7, o2.e7, module);    // Real
	result.e1 =
		bigModMult(o1.real, o2.e1, module)
		+ bigModMult(o1.e1, o2.real, module)
		+ bigModMult(o1.e2, o2.e4, module)
		+ bigModMult(o1.e3, o2.e7, module)
		- bigModMult(o1.e4, o2.e2, module)
		+ bigModMult(o1.e5, o2.e6, module)
		- bigModMult(o1.e6, o2.e5, module)
		- bigModMult(o1.e7, o2.e3, module);    // e1
	result.e2 =
		bigModMult(o1.real, o2.e2, module)
		- bigModMult(o1.e1, o2.e4, module)
		+ bigModMult(o1.e2, o2.real, module)
		+ bigModMult(o1.e3, o2.e5, module)
		+ bigModMult(o1.e4, o2.e1, module)
		- bigModMult(o1.e5, o2.e3, module)
		+ bigModMult(o1.e6, o2.e7, module)
		- bigModMult(o1.e7, o2.e6, module);    // e2
	result.e3 =
		bigModMult(o1.real, o2.e3, module)
		- bigModMult(o1.e1, o2.e7, module)
		- bigModMult(o1.e2, o2.e5, module)
		+ bigModMult(o1.e3, o2.real, module)
		+ bigModMult(o1.e4, o2.e6, module)
		+ bigModMult(o1.e5, o2.e2, module)
		- bigModMult(o1.e6, o2.e4, module)
		+ bigModMult(o1.e7, o2.e1, module);    // e3
	result.e4 =
		bigModMult(o1.real, o2.e4, module)
		+ bigModMult(o1.e1, o2.e2, module)
		- bigModMult(o1.e2, o2.e1, module)
		- bigModMult(o1.e3, o2.e6, module)
		+ bigModMult(o1.e4, o2.real, module)
		+ bigModMult(o1.e5, o2.e7, module)
		+ bigModMult(o1.e6, o2.e3, module)
		- bigModMult(o1.e7, o2.e5, module);    // e4
	result.e5 =
		bigModMult(o1.real, o2.e5, module)
		- bigModMult(o1.e1, o2.e6, module)
		+ bigModMult(o1.e2, o2.e3, module)
		- bigModMult(o1.e3, o2.e2, module)
		- bigModMult(o1.e4, o2.e7, module)
		+ bigModMult(o1.e5, o2.real, module)
		+ bigModMult(o1.e6, o2.e1, module)
		+ bigModMult(o1.e7, o2.e4, module);    // e5
	result.e6 =
		bigModMult(o1.real, o2.e6, module)
		+ bigModMult(o1.e1, o2.e5, module)
		- bigModMult(o1.e2, o2.e7, module)
		+ bigModMult(o1.e3, o2.e4, module)
		- bigModMult(o1.e4, o2.e3, module)
		- bigModMult(o1.e5, o2.e1, module)
		+ bigModMult(o1.e6, o2.real, module)
		+ bigModMult(o1.e7, o2.e2, module);    // e6
	result.e7 =
		bigModMult(o1.real, o2.e7, module)
		+ bigModMult(o1.e1, o2.e3, module)
		+ bigModMult(o1.e2, o2.e6, module)
		- bigModMult(o1.e3, o2.e1, module)
		+ bigModMult(o1.e4, o2.e5, module)
		- bigModMult(o1.e5, o2.e4, module)
		- bigModMult(o1.e6, o2.e2, module)
		+ bigModMult(o1.e7, o2.real, module);    // e7




	result.real = mod(result.real, module);
	result.e1 = mod(result.e1, module);
	result.e2 = mod(result.e2, module);
	result.e3 = mod(result.e3, module);
	result.e4 = mod(result.e4, module);
	result.e5 = mod(result.e5, module);
	result.e6 = mod(result.e6, module);
	result.e7 = mod(result.e7, module);


	return result;
}

//
octonion power(octonion oc, int potency, long long module)
{
	octonion result = { 0 };
	if (potency == 0)
	{
		result.real = 1;
		return result;
	}
	result = oc;
	for (int i = 1; i <= potency; i++)
	{
		if (i > 1)
		{
			result = multiply(result, oc, module);
		}
	}
	return result;
}

octonion calculateF(octonion oa, polynomialTerm* terms, int termCount, long long module)
{
	//check if this blanks the whole struct
	octonion Fa = { 0 };
	for (int i = 0; i < termCount; i++)
	{
		if (i == termCount - 1)
		{
			Fa = summ(Fa, newOctonion(terms[i].value, 0, 0, 0, 0, 0, 0, 0), module);
		}
		else
		{
			octonion on = power(oa, terms[i].grade, module);    // hace on = o a la n
			octonion ox = scalar(on, terms[i].value, module);      // hace c.on
			Fa = summ(Fa, ox, module);             // suma el termino c.on a fa
			// free(ox); <-- si habilito viola segmento
		}
	}

	return Fa;
}


bool octonionEquality(octonion o1, octonion o2)
{
	//todo: this might be incorrect  when the octonions are composed of something other than ints
	int* p_o1 = (int*)&o1;
	int* p_o2 = (int*)&o2;
	bool result = true;
	for (int i = 0; i < 8; i++)
	{
		result = result & (p_o1[i] == p_o2[i]);
		if (!result)
		{
			result = false;
		}
	}
	return result;
}


octonion newOctonion(long long real, long long e1, long long e2, long long e3, long long e4, long long e5, long long e6, long long e7) {
	octonion result;
	result.real = real;
	result.e1 = e1;
	result.e2 = e2;
	result.e3 = e3;
	result.e4 = e4;
	result.e5 = e5;
	result.e6 = e6;
	result.e7 = e7;
	return result;
}


#endif // !octonions_c
