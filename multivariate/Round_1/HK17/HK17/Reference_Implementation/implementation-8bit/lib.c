//
//  lib.h
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the definition of the functions used by the algorithm to access random number in a comfortable way.
//  in particular this implementaiton uses the rng provided by the NIST.
//functions
// randomRange
//    returns a random number contained in (min ... max]
// random
//    returns a random number contained in (0 ... max]
#include "lib.h"
#include "rng.h"

unsigned long randomRange(unsigned long min, unsigned long max)
{
	unsigned long diff = max - min;
	return random(diff) + min; 
}
unsigned long random(unsigned long max)
{
	unsigned long random = 0;
	unsigned long rand;

	randombytes((unsigned char*)&rand, sizeof(unsigned long));

	rand %= max;
	return rand;
}