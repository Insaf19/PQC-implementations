//
//  lib.h
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains the declaration of the functions used by the algorithm to access random number in a comfortable way.
//functions
// randomRange
//    returns a random number contained in (min ... max]
// random
//    returns a random number contained in (0 ... max]

#ifndef lib_h
#define lib_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "octonions.h"
#include <time.h>
unsigned long randomRange(unsigned long min, unsigned long max);
unsigned long random(unsigned long max);

#endif // !lib_h
