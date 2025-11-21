//
//  program.c
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains some code made with the express purpose of testing out the algorithm.
//	even considering than its main objective was to give me the oportunity to meassure the code,
//	it can be viewed as an example of some sorts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include"HK17.h"
#include "rng.h"
#include "intermediateKAT.h"
#include "octonionTest.h"
//#define octTest
//#define memtest
#define processorTest
//#define KAT

bool testKeyGeneration() {
	int degree = 8;
	int module = 251;
	//private stuff
	HK17PrivateKey* aliceKey = buildPrivateKey(degree, module);
	HK17PrivateKey* bobKey = buildPrivateKey(degree, module);

	//public shared stuff
	octonion publicOA = buildRandomOctonion(module);
	octonion publicOB = buildRandomOctonion(module);
	octonion aliceToken = calculateToken(publicOA, publicOB, aliceKey);
	octonion bobToken = calculateToken(publicOA, publicOB, bobKey);
	//session shared knowledge

	octonion aliceSK = calculateToken(publicOA, bobToken, aliceKey);
	octonion bobSK = calculateToken(publicOA, aliceToken, bobKey);


	//horrible free stuff.
	free(aliceKey->polynomial);
	free(bobKey->polynomial);
	free(aliceKey);
	free(bobKey);


	//if SK is equal to 0,0,0,0,0,0,0,0 the whole process should restart because n or m were not correct
	return octonionEquality(aliceSK, bobSK);

}


bool testKeyGeneration32(long long module, int degree) {
#ifdef memtest
	printf("waiting to execute");
	getchar();
#endif 
	//private stuff
	HK17PrivateKey* aliceKey = buildPrivateKey(degree, module);
	HK17PrivateKey* bobKey = buildPrivateKey(degree, module);

	//public shared stuff
	octonion publicOA = buildRandomOctonion(module);
	octonion publicOB = buildRandomOctonion(module);
	octonion aliceToken = calculateToken(publicOA, publicOB, aliceKey);
	octonion bobToken = calculateToken(publicOA, publicOB, bobKey);
	//session shared knowledge

	octonion aliceSK = calculateToken(publicOA, bobToken, aliceKey);
	octonion bobSK = calculateToken(publicOA, aliceToken, bobKey);
#ifdef memtest
	printf("Executed, \n waiting to release");
	getchar();
#endif

	//horrible free stuff.
	free(aliceKey->polynomial);
	free(bobKey->polynomial);
	free(aliceKey);
	free(bobKey);
#ifdef memtest
	printf("Released, \n waiting to continue");

	getchar();
#endif

	//if SK is equal to 0,0,0,0,0,0,0,0 the whole process should restart because n or m were not correct
	return octonionEquality(aliceSK, bobSK);
}

void testRandomParameterGeneration(long long module) {
	octonion publicOA = buildRandomOctonion(module);
	
}

void testPrivateKeyGeneration(int degree, long long module) {
	HK17PrivateKey* aliceKey = buildPrivateKey(degree, module);
#ifdef memtest
	free(aliceKey->polynomial);
	free(aliceKey);

#endif // memtest
}

void testTokenGeneration(octonion publicOA, octonion publicOB, HK17PrivateKey* privateKey)
{
	octonion aliceToken = calculateToken(publicOA, publicOB, privateKey);
}

void testSessionPasswordGeneration(octonion publicOA, octonion bobToken, HK17PrivateKey* aliceKey)
{
	octonion aliceSK = calculateToken(publicOA, bobToken, aliceKey);
}
 

  

int main()
{
	long long module = 4294967279;
	int degree = 64;
	//long long module = 65521;
	//int degree = 32;
	//long long module = 251;
	//int degree = 16;
#ifdef octTest
	generateOctonionTestFile(module, degree, 20);
#else

#ifdef KAT
	intermediateKAT(degree, module);
#else


	printf("started at : %s %s \n", __DATE__, __TIME__);
	int executions = 200;
	clock_t begin = clock();

	//KeyPair8its* keys = algorithm();
	for (int i = 0; i < executions; i++)
	{
		testKeyGeneration32(module,degree);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;

	printf("\nComplete Execution took: %f  ms. An avg of %f\n", time_spent,time_spent/ executions);
	//free(keys);
#ifdef processorTest


	
	begin = clock();	
	for (int i = 0; i < executions; i++)
	{
		testRandomParameterGeneration(module);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("\nRandom octonion generation took: %f  ms. An avg of %f\n", time_spent, time_spent / executions);
	 

	begin = clock();
	for (int i = 0; i < executions; i++)
	{
		testPrivateKeyGeneration(degree,module);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("\nRandom private key generation took: %f  ms. An avg of %f\n", time_spent, time_spent / executions);



	octonion publicOA = buildRandomOctonion(module);
	octonion publicOB = buildRandomOctonion(module);
	HK17PrivateKey* aliceKey = buildPrivateKey(degree, module);
	HK17PrivateKey* bobKey = buildPrivateKey(degree, module);
	octonion bobToken = calculateToken(publicOA, publicOB, bobKey);

	begin = clock();
	for (int i = 0; i < executions; i++)
	{
		testTokenGeneration(publicOA, publicOB, aliceKey);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("\nPublic token generation took: %f  ms. An avg of %f\n", time_spent, time_spent / executions);

	begin = clock();
	for (int i = 0; i < executions; i++)
	{
		testSessionPasswordGeneration(publicOA,bobToken , aliceKey);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("\nShared session password generation took: %f  ms. An avg of %f\n", time_spent, time_spent / executions);

#endif // processorTest

#endif // KAT

#endif // octTest
	getchar();

}


