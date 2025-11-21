
/**
 * \file
 *         Implmentation of Compact-LWE puiblic key encryption scheme developed in CSIRO
 *         09-11-2017
 *         Dongxi Liu <dongxi.liu@csiro.au>
 */


#include "rng.h"
#include "api.h"	
#include <stdio.h> /* For printf() */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


/*---------------------------------------------------------------------------*/
void main(int argc, char **argv){
	printf("\n ++++++ Reference Implementation (Note that performance given in specification is not based on reference implementation) ++++++\n");

	unsigned char entropy[48]={
 		0x84, 0x17, 0xe3, 0x6e, 0x5c, 0xc3, 0x8a, 0xda, 0xcb, 0x8c, 0x98, 0x25, 0xdf, 0x77, 0x8d, 0xda,
 		0x2a, 0x91, 0x99, 0x92, 0x77, 0x1b, 0x5a, 0x73, 0xf7, 0xcf, 0x2a, 0xa9, 0xe3, 0xd7, 0x2d, 0xc7, 
 		0x7f, 0x5b, 0x3e, 0x25, 0x42, 0x4a, 0xfe, 0x5a, 0x2b, 0x74, 0xdc, 0x65, 0x3c, 0xa3, 0x85, 0xc2,};

	randombytes_init(entropy, NULL, 256);


	int count=0;
  
  	unsigned char* sk = malloc(CRYPTO_SECRETKEYBYTES); 
  	unsigned char* pk = malloc(CRYPTO_PUBLICKEYBYTES);

	struct timeval stop, start;

 	gettimeofday(&start, NULL);
	for(count=0; count<10000; count++){
  		crypto_encrypt_keypair(pk, sk);
	}
        
	gettimeofday(&stop, NULL);

	printf("\n 10000 key pairs: %lu uSec\n", (stop.tv_sec - start.tv_sec)*1000000L+ stop.tv_usec - start.tv_usec);
	
	gettimeofday(&start, NULL);

	
	unsigned char m[1024];
	randombytes(m, 1024);	


 	unsigned long long clen=9288;
  	unsigned char* c = malloc(clen*10000);

  	unsigned long long len=1024; 

	
	unsigned char* m1=malloc(len);
	unsigned long long mlen;

	
	for(len=32; len < 1025; len=2*len){

		printf("\n ------ message %llu bytes-----\n", len);

		gettimeofday(&start, NULL);
		for(count=0; count<10000; count++){
			crypto_encrypt(c+count*9288, &clen, m, len, pk);
		}
		gettimeofday(&stop, NULL);
		printf("\n 10000 encryptions: %lu uSec, cipher %llu bytes \n", (stop.tv_sec - start.tv_sec)*1000000L+ stop.tv_usec - start.tv_usec, clen);


		gettimeofday(&start, NULL);
		for(count=0; count<10000; count++){
			mlen=len;
			crypto_encrypt_open(m1, &mlen, c+count*9288, clen, sk);  

 			if(memcmp(m, m1, len)!=0||len!=mlen){//
				printf("error-%d\n", count);
				return;
	 		}	

		}
		gettimeofday(&stop, NULL);
		printf(" 10000 decryptions with correcteness check: %lu uSec\n", (stop.tv_sec - start.tv_sec)*1000000L+ stop.tv_usec - start.tv_usec);


	}
	

	free(sk);
	free(pk);
  	free(m1);
	free(c);
  	printf("\n");

}

