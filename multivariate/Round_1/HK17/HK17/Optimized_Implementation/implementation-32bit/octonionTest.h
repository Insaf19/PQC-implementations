//
//  octonionTest.c
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains some code made with the express purpose of testing out the algorithm.
//	in particular it contains functions to output a file of serialized octonion operations 


#pragma once
#include "HK17.h"
#include "octonions.h"
#include "lib.h"
#include <stdio.h>
#include "rng.h"
void generateOctonionTestFile(long long module, int degree, int count);
void printOctonion(FILE *fp, octonion o);