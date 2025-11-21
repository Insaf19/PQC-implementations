/**
 * \file
 *         Implmentation of Compact-LWE puiblic key encryption scheme developed in CSIRO
 *         09-11-2017
 *         Dongxi Liu <dongxi.liu@csiro.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"
#include "compact-lwe.h"

int crypto_encrypt_keypair(unsigned char *pk_str, unsigned char *sk_str){
	
	int len, j;

	struct SK sk;
 	len = sk_gen(&sk); 
	if(len==-1)
		return -1;

  	len = sk_out_str(&sk, sk_str, CRYPTO_SECRETKEYBYTES); 


	len = pk_gen(&sk, pk_str); 

	mpz_clear (sk.wPos);
	mpz_clear (sk.wNeg);		
	mpz_clear (sk.p);	
	mpz_clear (sk.q);	
    mpz_clear (sk.r);	
    mpz_clear (sk.t);	
	mpz_clear (sk.bv);

	for(j=0; j< F; j++){
		mpz_clear (sk.kInv[j]);
    }

	 mpz_clear (sk.ckInv);
 	
	if(len>0)
		len=0;	

	return len;
}

int crypto_encrypt(
 unsigned char *c, unsigned long long *clen,
 const unsigned char *m1, unsigned long long mlen1,
 const unsigned char *pk_str
 ){

	unsigned char *m;
	unsigned long extra=0, group_size;

	if((mlen1+L+3)%T_BYTES!=0)
		extra = T_BYTES - ((mlen1+L+3)%T_BYTES);

	group_size = (mlen1+L+3+extra)/T_BYTES;
	m = malloc(mlen1+L+3+extra);
	encode(m1, mlen1, m, mlen1+L+3+extra);
		

	//#ifdef debug
	//	int lll=0;
	//	for(lll=0; lll< mlen1+L+3+extra; lll++)
	//		printf(" 0x%02x ", m[lll]);	
	//	printf("\n");
	//#endif
	//const unsigned char *m = m1;
	
	int c_pos=0;
	int i, j;
	
	unsigned long single_clen = F*Q_BYTES+2*(N-1)+T_BYTES;
	unsigned long real_clen = group_size*single_clen;

	//if(*clen < real_clen){
	//	#ifdef debug
	//		printf("buffer c too short: %lu bytes expected \n", real_clen);			
	//	#endif
	//	return -1;
	//}

	struct PK* pk;
	pk = pk_in_str(pk_str, CRYPTO_PUBLICKEYBYTES);
	if(pk==NULL){
		#ifdef debug
			printf("failed to load public key \n");			
		#endif
		return -1;
	}

	struct Cipher D; 

	for(i=0; i < group_size; i++){
		enc(pk, m+i*T_BYTES, &D);

		//printCipherS(&c);
			
 		int cipher_len = cipher_out_str(&D, c+c_pos, (*clen)-c_pos);
		if(cipher_len!=single_clen){
			#ifdef debug
				printf("something wrong in cipher_out_str \n");			
			#endif		
			return -1;
		}

		c_pos = c_pos + cipher_len;
		clearCipher(&D);
	}

	*clen = c_pos;

	clearPK(pk);
	free(pk);
	free(m);

	return 0;

}

int crypto_encrypt_open(
 unsigned char *m1, unsigned long long *mlen,
 const unsigned char *c, unsigned long long clen,
 const unsigned char *sk_str
 ){

	unsigned long single_clen = F*Q_BYTES+2*(N-1)+T_BYTES;
	unsigned long group_size = clen/single_clen;
	if(clen%single_clen!=0){
		printf("Incorrect length ciphertext buffer\n");		
		return -1;
	}

	unsigned long real_mlen = group_size*(T_BYTES);


	unsigned char *m = malloc(real_mlen);

	struct SK* sk;
	sk = sk_in_str(sk_str, CRYPTO_SECRETKEYBYTES);
	if(sk==NULL){
		#ifdef debug
			printf("failed to load private key \n");			
		#endif
		return -1;
	}

	int pos, i;
	struct Cipher D;

	int m_pos =0;
	for(i=0; i < group_size; i++){
		cipher_in_str(c+i*single_clen, &pos, &D);
		//printCipherS(&c);
		if(pos!=single_clen){
			#ifdef debug
				printf("Error: something worng with cipher_in_str \n");		
			#endif
			*mlen = 0;
			return -1;
		}
		dec(sk, &D, m+i*T_BYTES);
		clearCipher(&D);
	}
	


	//#ifdef debug
	//	printf("encoded message after decryption\n");
	//	int lll=0;
	//	for(lll=0; lll< real_mlen; lll++)
	//		printf(" 0x%02x ", m[lll]);

	//	printf("\n");
	//#endif	

	//if(*mlen+L+3<real_mlen){
	//	printf("Error: too short buffer for m: %lu bytes expected\n", real_mlen);	
	//	return -1;
	//}

	i = decode(m1, mlen, m, real_mlen);
	
	free(sk);
	free(m);
	return i;
}
