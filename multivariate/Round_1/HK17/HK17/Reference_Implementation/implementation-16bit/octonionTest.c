//
//  octonionTest.c
//	This file is part of a HK17 Algorithm Implementation
//  Implemented by Matias Teragni - 2017. 
//
//  This file contains some code made with the express purpose of testing out the algorithm.
//	in particular it contains functions to output a file of serialized octonion operations 

#include "octonionTest.h"
void printOctonion(FILE *fp, octonion o) {
	fprintf(fp, " ( %llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu) ", o.real, o.e1, o.e2, o.e3, o.e4, o.e5, o.e6, o.e7);
}
void generateOctonionTestFile(long long module, int degree, int count) {
	char                fn_req[50];
	FILE                *fp_req; 
	int                 done;

	 
	unsigned char       entropy_input[48];

	for (int i = 0; i<48; i++)
		entropy_input[i] = i;

	randombytes_init(entropy_input, NULL, 256);

 	// Create the REQUEST file
	printf("starting\n");
	sprintf(fn_req, "octonionAdd_%d.req",degree/2);
	if ((fp_req = fopen(fn_req, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_req);
		return ;
	}
	printf("Adding \n");
	for (int i = 0; i < count; i++)
	{

		octonion publicOA = buildRandomOctonion(module);
		octonion publicOB = buildRandomOctonion(module);
		octonion result = summ(publicOA, publicOB, module);
		fprintf(fp_req, "%d\n", i);
		fprintf(fp_req, "A= ");

		printOctonion(fp_req, publicOA);
		fprintf(fp_req, "\nB= ");
		printOctonion(fp_req, publicOB);
		fprintf(fp_req, "\nR= ");
		printOctonion(fp_req, result);
		fprintf(fp_req, "\n\n");
	}
	fclose(fp_req);


	memset(fn_req, 0, sizeof(fn_req));
	sprintf(fn_req, "octonionMul_%d.req", degree / 2);
	if ((fp_req = fopen(fn_req, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_req);
		return;
	}


	printf("multiplying \n");
	for (int i = 0; i < count; i++)
	{

		octonion publicOA = buildRandomOctonion(module);
		octonion publicOB = buildRandomOctonion(module);
		octonion result = multiply(publicOA, publicOB, module);
		fprintf(fp_req, "%d\n", i);
		fprintf(fp_req, "A= ");

		printOctonion(fp_req, publicOA);
		fprintf(fp_req, "\nB= ");
		printOctonion(fp_req, publicOB);
		fprintf(fp_req, "\nR= ");
		printOctonion(fp_req, result);
		fprintf(fp_req, "\n\n");
	}
	fclose(fp_req);




	memset(fn_req, 0, sizeof(fn_req));
	sprintf(fn_req, "octonionScale_%d.req", degree / 2);
	if ((fp_req = fopen(fn_req, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_req);
		return;
	}


	printf("scaling \n");
	for (int i = 0; i < count; i++)
	{

		octonion publicOA = buildRandomOctonion(module);
		unsigned long scale = random(module);
		octonion result = scalar(publicOA, scale, module);
		fprintf(fp_req, "%d\n", i);
		fprintf(fp_req, "A= ");
		printOctonion(fp_req, publicOA);
		fprintf(fp_req, "\nB= %lu", scale);
		fprintf(fp_req, "\nR= ");
		printOctonion(fp_req, result);
		fprintf(fp_req, "\n\n");
	}
	fclose(fp_req);


	memset(fn_req, 0, sizeof(fn_req));
	sprintf(fn_req, "octonionPow_%d.req", degree / 2);
	if ((fp_req = fopen(fn_req, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_req);
		return;
	}

	printf("powering \n");

	for (int i = 0; i < count; i++)
	{

		octonion publicOA = buildRandomOctonion(module);
		unsigned long scale = random(125);
		octonion result = power(publicOA, scale, module);
		fprintf(fp_req, "%d\n", i);
		fprintf(fp_req, "A= ");
		printOctonion(fp_req, publicOA);
		fprintf(fp_req, "\nB= %lu", scale);
		fprintf(fp_req, "\nR= ");
		printOctonion(fp_req, result);
		fprintf(fp_req, "\n\n");
	}
	fclose(fp_req);



	printf("done \n");

}