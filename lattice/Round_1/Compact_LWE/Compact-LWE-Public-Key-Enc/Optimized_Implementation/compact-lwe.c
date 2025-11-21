/**
 * \file
 *         Implmentation of Compact-LWE puiblic key encryption scheme developed in CSIRO
 *         09-11-2017
 *         Dongxi Liu <dongxi.liu@csiro.au>
 */

#include "compact-lwe.h"
#include "rng.h"
#include <stdio.h> /* For printf() */
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>


int sk_gen(struct SK* sk){


	int i, j, l;
	sk->n = N;
	sk->m = M;
	sk->t_bytes = T_BYTES;
	sk->q_bytes = Q_BYTES;

	if(sizeof(unsigned long)!=sk->q_bytes){
		printf("Optimisation of Compact-LWE not supported for non-%u bits platform \n", Q_BYTES*8);
		return -1;
	}

	mpz_init (sk->wPos);
	mpz_init (sk->wNeg);		
	mpz_init (sk->p);	
	mpz_init (sk->q);	
    mpz_init (sk->r);	
    mpz_init (sk->t);	
	mpz_init (sk->bv);

	for(j=0; j< F; j++){
		mpz_init (sk->kInv[j]);
     }

	mpz_init (sk->ckInv);

    mpz_set_ui(sk->wPos,W_POS);
	mpz_set_ui(sk->wNeg,W_NEG); 

	mpz_set_str(sk->bv, B, 10); 

    mpz_set_ui(sk->q,1); 
	mpz_mul_2exp(sk->q, sk->q, sk->q_bytes*8); 	


	mpz_set_ui(sk->t,1); 
	mpz_mul_2exp(sk->t, sk->t, sk->t_bytes*8); 	


    mpz_t a, b, c, sckInv;
    mpz_init (a);
    mpz_init (b); 
	mpz_init (c);	
    mpz_init (sckInv);


	unsigned long skSIZE, peMax, qDivW;
	
	
	randomMPZ(sk->q_bytes, a);
	mpz_set_str (c, pSIZE, 10);	
	mpz_mod(a, a, c);

        
	mpz_add(c, sk->wPos, sk->wNeg);
    mpz_mul(b, sk->bv, c);
        
	mpz_add(sk->p, b, a);


	if(mpz_get_ui(sk->p)%2==0){ 
		mpz_add_ui(sk->p, sk->p, 1);
		if(mpz_cmp(sk->p,sk->q)>=0){
			mpz_sub_ui(sk->p, sk->p, 2);
		}
	}

	unsigned long qM1 = (unsigned long) -1;

	qDivW = qM1/(mpz_get_ui(sk->wPos)+mpz_get_ui(sk->wNeg));	 
	qDivW = qDivW - mpz_get_ui(sk->p);

	mpz_set_str(sk->r, eMax, 10);
	peMax = mpz_get_ui(sk->p)*mpz_get_ui(sk->r);


	if(qDivW <= peMax){
		printf("Too big error: %s\n", eMax);
		return -1;
	}

	unsigned char *rndbuf = malloc(sizeof(unsigned long)*F*(sk->n-1)+F);
	randombytes(rndbuf, sizeof(unsigned long)*F*(sk->n-1)+F);
	for(j=0; j<F; j++){
		for(i=1; i< sk->n; i++){
			unsigned long *rnd = (unsigned long*) (rndbuf+j*(sk->n-1)*sizeof(unsigned long)+(i-1)*sizeof(unsigned long));	                
			mpz_init(sk->s[j][i]);
			mpz_set_ui(sk->s[j][i], *rnd);
		}
	}


	skSIZE = (qDivW-peMax)/mpz_get_ui(sk->bv);	

	for(j=0; j<F; j++){
		unsigned long *rnd = (unsigned long*) (rndbuf+F*(sk->n-1)*sizeof(unsigned long)+j*sizeof(unsigned long));
		mpz_init(sk->k[j]);
		mpz_set_ui(sk->k[j], *rnd);

		if(mpz_get_ui(sk->k[j])%2==0){ 
			mpz_add_ui(sk->k[j], sk->k[j], 1);
		}

		mpz_invert(sk->kInv[j], sk->k[j],sk->q);
	}

	unsigned long p = mpz_get_ui(sk->p);
	for(j=0; j<F; j++){
		randomMPZ(sk->q_bytes, sk->ck[j]);
		mpz_mod(sk->ck[j], sk->ck[j], sk->p);

		if(j==F-1){
			
			mpz_invert(sk->ckInv, sk->ck[j], sk->p);
			mpz_mul(a, sk->ckInv, sk->ck[j]);
			mpz_mod_ui(a, a, p);

			if(mpz_get_ui(a)==1){
			}
			else{
				j--;
			}

		}
        }


	do{
		for(j=0; j<F; j++){
			randomMPZ(sk->q_bytes, sk->s[j][0]);  
			mpz_mod_ui(sk->s[j][0], sk->s[j][0], skSIZE);
		}

		mpz_set_ui(a, 0);		
		for(j=0; j<F; j++){
			mpz_mul(b, sk->s[j][0], sk->ck[j]);
			mpz_mod_ui(b, b, p);

			mpz_add(a, a, b);
			mpz_mod_ui(a, a, p);
		}

		mpz_invert(sckInv, a, sk->p);

		mpz_mul(b, sckInv, a);
		mpz_mod_ui(b, b, p);
		if(mpz_get_ui(b)==1)
			break;

	}while(1);

	for(j=0; j<F; j++){
		mpz_mul(sk->ck[j], sk->ck[j], sckInv);
		mpz_mod(sk->ck[j], sk->ck[j], sk->p);
	}

	mpz_invert(sk->ckInv, sk->ck[F-1], sk->p);


    mpz_clear (a);
    mpz_clear (b); 
	mpz_clear (c);	
	
        free(rndbuf);
	return 0;
}



int pk_gen(struct SK* sk, unsigned char *pk_str){

	if(sizeof(unsigned long)!=sk->q_bytes){
		printf("Optimisation of Compact-LWE not supported for non-%u bits platform \n", Q_BYTES*8);
		return -1;
	}

	struct PK  pk1; 
	struct PK* pk = &pk1;   

	unsigned int i,j, l;

	//mpz_init (pk->q);	
	mpz_init (pk->t);
	mpz_init (pk->wPos);
	mpz_init (pk->wNeg);
	mpz_init (pk->bv);
	for(j=0; j <F; j++){
		for(i=0; i < sk->m; i++)
			mpz_init (pk->element[j][i]);
	}

	

	mpz_add_ui (pk->wPos, sk->wPos, 0);
	mpz_add_ui (pk->wNeg, sk->wNeg, 0);
	mpz_add_ui (pk->bv, sk->bv, 0);

	pk->q_bytes = sk->q_bytes;
	pk->t_bytes = sk->t_bytes;
	
        //mpz_set_ui(pk->q,0); 
	//mpz_mul_2exp(pk->q, pk->q, pk->q_bytes*8); 

	
        mpz_set_ui(pk->t,1); 
	mpz_mul_2exp(pk->t, pk->t, pk->t_bytes*8); 

	pk->m = sk->m;
	pk->n = sk->n;



        mpz_t a, b;
        mpz_init (a);
	mpz_init (b);

	unsigned long e, eMin, c, d, leftSum, kInv[F], p, pSum, pTemp;

	for(l=0; l<F; l++){
		kInv[l] = mpz_get_ui(sk->kInv[l]);
	}
	p = mpz_get_ui(sk->p);

	//eMin*(W_POS) >= (W_NEG-1)*sk->r + W_NEG -1
	mpz_mul(a, sk->r, pk->wNeg);
	mpz_add(a, a, pk->wNeg);
	eMin = mpz_get_ui(a)/mpz_get_ui(pk->wPos);

	unsigned long rMod = mpz_get_ui(sk->r);
	unsigned long bvMod = mpz_get_ui(pk->bv);	
	//printf("eMin: %s \n", mpz_get_str(NULL, 10, eMin));

	if(rMod <= eMin){
		printf("Incorrect: eMin %lu is bigger than max error %lu\n", eMin, rMod);
		return -1;
	}	
	
 	rMod = rMod -eMin;

	int numRan = sizeof(unsigned long)*F*pk->m*2;
	unsigned char* rndbuf = malloc(numRan);
	randombytes(rndbuf, numRan);		
	for(i=0; i < pk->m; i++){
			pSum = 0;	
	        for(l=0; l<F; l++){
				if(l<F-1){
					unsigned long* rnd = (unsigned long*) (rndbuf+i*F*sizeof(unsigned long)*2+2*l*sizeof(unsigned long));
					pTemp = (*rnd)%p;
					mpz_mul_ui(a, sk->ck[l], pTemp);
					mpz_mod_ui(a, a, p);
					pSum = mpz_get_ui(a) + pSum;	
					pSum = pSum%p;
				}
				else{
					unsigned long* rnd = (unsigned long*) (rndbuf+i*F*sizeof(unsigned long)*2+2*l*sizeof(unsigned long));
					pTemp = (*rnd)%p;
					mpz_mul_ui(b, sk->p, pTemp);
					mpz_sub_ui(b, b, pSum);
					mpz_mul(a, sk->ckInv, b);
					mpz_mod_ui(a, a, p);
					pTemp =  mpz_get_ui(a)%p;

					#ifdef debug
						mpz_mul_ui(a, sk->ck[l], pTemp);
						mpz_add_ui(a, a, pSum);
						mpz_mod_ui(a, a, p);
						if(mpz_get_ui(a)!=0)			
							printf("Incorect: not zero \n");
					#endif
				}


	            leftSum = 0;
               

				for(j=1; j<pk->n;j++){
					c = mpz_get_ui(sk->s[l][j])*(I[(i+j)%256]&0x0F);
					leftSum = leftSum + c;
				}
			
	
				//val[i]
				if(i==0)
					d = I[0];
				else
					d = mpz_get_ui(pk->element[0][i-1])^mpz_get_ui(pk->element[1][i-1]);


				d = d%bvMod;

				c = mpz_get_ui(sk->s[l][0])*d;
				d = pTemp + c;

				//randombytes((unsigned char*)&e, sizeof(unsigned long));
				unsigned long* rnd = (unsigned long*) (rndbuf+i*F*sizeof(unsigned long)+(2*(l+1)-1)*sizeof(unsigned long));
				e = (*rnd)%rMod;
				e= e+ eMin;						

				//c = kInv[l]*p;
			    c = p*e+d;
				c = kInv[l]*c;
 
                        //printf("error[%d][%d]=%s \n", l, i, mpz_get_str(NULL, 10, e));
				leftSum = leftSum + c;
				mpz_set_ui(pk->element[l][i], leftSum);

		        //pk->element[l][i] = leftSum + Ri*sk->kInv[l]*sk->p;  			        
		} 

	}


        mpz_clear (a);
	mpz_clear (b);


	int len  = pk_out_str(pk, pk_str, CRYPTO_PUBLICKEYBYTES); 

	//mpz_init (pk->q);	
	mpz_clear (pk->t);
	mpz_clear (pk->wPos);
	mpz_clear (pk->wNeg);
	mpz_clear (pk->bv);
	for(j=0; j <F; j++){
		for(i=0; i < sk->m; i++)
			mpz_clear (pk->element[j][i]);
	}

	free(rndbuf);

	return len;


}



void clearCipher(struct Cipher* D){
	unsigned int i, j;
	for(j=0; j < F; j++)
		mpz_clear(D->tail[j]);
        for(i=0; i<N-1; i++){
		mpz_init(D->head[i]);
	}
}


int enc(struct PK* pk, const unsigned char* v, struct Cipher* D){
        //mpz_mod(v, v, pk->t);

	if(sizeof(unsigned long)!=pk->q_bytes){
		printf("Optimisation of Compact-LWE not supported for non-%u bits platform \n", pk->q_bytes*8);
		return -1;
	}
	
	unsigned int i,j;

	for(i=0; i<pk->n-1; i++){	
		mpz_init(D->head[i]);
	}	
	for(j=0; j < F; j++){
		mpz_init(D->tail[j]);
	}

	unsigned int sel, nsel;

	unsigned char buf[W_POS+2*W_NEG+2];
	randombytes(buf, mpz_get_ui(pk->wPos)+mpz_get_ui(pk->wNeg)*2+2);

	if(mpz_get_ui(pk->wNeg)>0){
		sel = mpz_get_ui(pk->wPos)+(buf[0]%mpz_get_ui(pk->wNeg));	
		nsel = buf[1]%mpz_get_ui(pk->wNeg);
	}
	else{
		sel = mpz_get_ui(pk->wPos);	
		nsel = 0;
	}

	char* l=malloc(pk->m);
	unsigned long* tail=malloc(F*sizeof(unsigned long));	
	short* element=malloc((pk->n-1)*sizeof(short));	

	for(j=0; j < F; j++){
		tail[j] =  0;	
	}
	for(i=0; i<pk->n-1; i++){	
		element[i] = 0;
	}

	unsigned long a, b, t;
	long randV=0;

	memset(l, 0x00, M);
	//for(i=0; i<M; i++){
	//	l[i]=0x00;
  	//}


	int posc = 0, negc=0;
	int count = nsel==0?sel:(sel/nsel+1);  
	for(i=0; i<sel+nsel; i++){
		unsigned short slot = buf[i+2]%M;
		if(count>0&&posc<sel){
			while(l[slot]<0)	
				slot = (slot+1)%M;		
			l[slot] = l[slot] + 1;			
			count--;
			posc++;
		}
		else{
			while(l[slot]>0)	
				slot = (slot+1)%M;		
			l[slot] = l[slot] - 1;			
			count = nsel==0?sel:(sel/nsel+1);
			negc++;
		}

  	}

	#ifdef debug
		printf("\n selection (%d, %d, %d): ", sel, posc, negc);
        	for(i=0; i<pk->m; i++){
			printf("l%u=%d, ", i, l[i]);
  		}
		printf("\n ");
	#endif

	unsigned long bvMod = mpz_get_ui(pk->bv);

	for(i=0; i<M; i++){		
		if(i==0)
			b = I[0];
		else
			b = mpz_get_ui(pk->element[0][i-1])^mpz_get_ui(pk->element[1][i-1]);

		b = b % bvMod;


		if(l[i]>=0){
			randV = randV + b * l[i];
		}
		else{
			short lPos = l[i]*(-1);
			randV = randV - b*lPos;
		}
	}

	while(randV<=0){
		for(i=0; i<M; i++){		
			if(l[i]<0){
				if(i==0)
					b = I[0];
				else
					b = mpz_get_ui(pk->element[0][i-1])^mpz_get_ui(pk->element[1][i-1]);

				b = b%bvMod;
				randV = randV + b;
				l[i] = l[i] +1;
				
				if(randV>0)
					break;

			}		
		}		
	}


	for(i=0; i<M; i++){			
		for(j=0; j < F; j++){			
			if(l[i]>=0){
				a = mpz_get_ui(pk->element[j][i]) * l[i];
				tail[j] = tail[j] + a;
			}
			else{
				short lPos = l[i]*(-1);
				a = mpz_get_ui(pk->element[j][i]) * lPos;
				tail[j] = tail[j] - a;
			}		
		}

		short elementV;

		for(j=1; j<pk->n; j++){
			if(l[i]>=0){
				elementV=(I[(i+j)%256]&0x0f)*l[i];
	        		element[j-1] = element[j-1] + elementV;
			}	
			else{
				char lPos = l[i]*(-1);
				elementV=(I[(i+j)%256]&0x0f)*lPos;
				element[j-1] = element[j-1] - elementV;
			}		
      	
		} 
		
	}

	

	for(j=0; j < F; j++)
		mpz_set_ui(D->tail[j], tail[j]);
	       
	for(j=0; j < pk->n-1; j++)
		mpz_set_si(D->head[j], element[j]);


	//printf("randv = %s", mpz_get_str(NULL, 16, randV));
	//printf("\n");
	
	t = mpz_get_ui(pk->t);

	a = randV%t;	
	b = randV/t;	
	if(b%2==0){//ensure b coprime with sk->t
		b=b+1;
	}

	unsigned long len;

	mpz_t randVMPZ;
	mpz_init(randVMPZ);
	mpz_set_ui(randVMPZ, a);

	for(i=0; i < pk->t_bytes; i++){
		buf[i] = 0x00;				
	}

	mpz_export (buf, &len, -1, 1, 1, 0, randVMPZ); 



	for(i=0; i < pk->t_bytes; i++){
		D->cval[i] = buf[(i+pk->t_bytes/2)%pk->t_bytes]^v[i]; 
	}

	mpz_import (randVMPZ, pk->t_bytes, -1, 1, 1, 0,  D->cval);
	len = mpz_get_ui(randVMPZ)*b;
	a = len%t;
	
	mpz_set_ui(randVMPZ, a);
	
	for(i=0; i < pk->t_bytes; i++){
		D->cval[i] = 0x00;			
	}

	mpz_export (D->cval, &len, -1, 1, 1, 0, randVMPZ);	

	free(l);
	free(tail);
	free(element);
	mpz_clear(randVMPZ);
	return 1;
}


struct SK* sk_in_str(const unsigned char* buf, int buf_len){
	int i, pos=0, j, l;

	struct SK* sk = malloc(sizeof(struct SK)); 

        sk->m = buf[pos];
	pos++;
        sk->n = buf[pos];
	pos++;
	sk->t_bytes = buf[pos];
	pos++;
	sk->q_bytes = buf[pos];
	pos++;

	mpz_init (sk->wPos);
	mpz_init (sk->wNeg);		
	mpz_init (sk->p);	
	mpz_init (sk->q);	
        mpz_init (sk->r);	
        mpz_init (sk->t);
	mpz_init (sk->bv);	
	
	for(j=0; j< F; j++){
		mpz_init (sk->kInv[j]);
		mpz_init (sk->k[j]);
		mpz_init (sk->ck[j]);

		for(i=0; i< sk->n ; i++){
			mpz_init (sk->s[j][i]);
		}	
        }

	mpz_init (sk->ckInv);



        int len = sk->q_bytes+sk->q_bytes+ F*sk->q_bytes+sk->q_bytes+F*sk->n*sk->q_bytes+2*F*sk->q_bytes+ 2+2+1+1+1+1+sk->q_bytes; //224
	if(buf_len < len){
		printf("The buf for sk is too small: expected %d, actual %d\n", len, buf_len);	
		return NULL;
	}

        mpz_set_ui(sk->q,1); 
	mpz_mul_2exp(sk->q, sk->q, sk->q_bytes*8); 	


	mpz_set_ui(sk->t,1); 
	mpz_mul_2exp(sk->t, sk->t, sk->t_bytes*8); 
	
	mpz_import (sk->wPos, 2, -1, 1, 1, 0, buf+pos); 
	pos = pos+2;

	mpz_import (sk->wNeg, 2, -1, 1, 1, 0, buf+pos); 
	pos = pos+2;

	mpz_import (sk->p, sk->q_bytes, -1, 1, 1, 0, buf+pos); 
	pos = pos+sk->q_bytes;

	mpz_import (sk->r, sk->q_bytes, -1, 1, 1, 0, buf+pos); 
	pos = pos+sk->q_bytes;

	for(j=0; j < F ; j++){
	      	mpz_import (sk->ck[j], sk->q_bytes, -1, 1, 1, 0, buf+pos); 
		pos = pos+sk->q_bytes;
	}

	mpz_import (sk->ckInv, sk->q_bytes, -1, 1, 1, 0, buf+pos); 
	pos = pos+sk->q_bytes;

	for(i=0; i< sk->n; i++){
		for(j=0; j < F ; j++){
	      		mpz_import (sk->s[j][i], sk->q_bytes, -1, 1, 1, 0,  buf+pos); 
			pos = pos+sk->q_bytes;
		}		
	}

	for(j=0; j < F ; j++){
	      	mpz_import (sk->k[j], sk->q_bytes, -1, 1, 1, 0,  buf+pos); 
		pos = pos+sk->q_bytes;
	}

	for(j=0; j < F ; j++){
	      	mpz_import (sk->kInv[j], sk->q_bytes, -1, 1, 1, 0, buf+pos); 
		pos = pos+sk->q_bytes;
	}
 

	mpz_import (sk->bv, sk->q_bytes, -1, 1, 1, 0, buf+pos); 
	pos = pos+sk->q_bytes;

	if(pos!=len){
		printf("Something wrong in sk input");
		return NULL;
	}

	return sk;

}


int sk_out_str(struct SK* sk, unsigned char* buf, int buf_len){
	int i, pos=0, j, l;

        int len = sk->q_bytes+sk->q_bytes+ F*sk->q_bytes+sk->q_bytes+F*N*sk->q_bytes+2*F*sk->q_bytes+ 2+2+1+1+1+1+sk->q_bytes; //224
	if(buf_len < len){
		printf("The buf forskis too small: expected %d, actual %d\n", len, buf_len);	
		return -1;
	}

        buf[pos]  = sk->m;
	pos++;
        buf[pos]  = sk->n;
	pos++;
	buf[pos]  = sk->t_bytes;
	pos++;
	buf[pos]  = sk->q_bytes;
	pos++;
	
	size_t tempbuflen;
	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->wPos); 
	for(l=tempbuflen; l<2; l++){
			buf[pos+l]=0x00;
	}
	pos = pos+2;

	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->wNeg); 
	for(l=tempbuflen; l<2; l++){
			buf[pos+l]=0x00;
	}
	pos = pos+2;

	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->p); 
	for(l=tempbuflen; l<sk->q_bytes; l++){
		buf[pos+l]=0x00;
	}
	pos = pos+sk->q_bytes;

	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->r); 
	for(l=tempbuflen; l<sk->q_bytes; l++){
		buf[pos+l]=0x00;
	}
	pos = pos+sk->q_bytes;


	for(j=0; j < F ; j++){
	      	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->ck[j]); 
		for(l=tempbuflen; l<sk->q_bytes; l++){
			buf[pos+l]=0x00;
		}
		pos = pos+sk->q_bytes;
	}
	
	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->ckInv); 
	for(l=tempbuflen; l<sk->q_bytes; l++){
		buf[pos+l]=0x00;
	}
	pos = pos+sk->q_bytes;

	for(i=0; i< sk->n; i++){
		for(j=0; j < F ; j++){
	      		mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->s[j][i]); 
			for(l=tempbuflen; l<sk->q_bytes; l++){
				buf[pos+l]=0x00;
			}
			pos = pos+sk->q_bytes;
		}		
	}


	for(j=0; j < F ; j++){
	      	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->k[j]); 
		for(l=tempbuflen; l<sk->q_bytes; l++){
			buf[pos+l]=0x00;
		}
		pos = pos+sk->q_bytes;
	}

	for(j=0; j < F ; j++){
	      	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->kInv[j]); 
		for(l=tempbuflen; l<sk->q_bytes; l++){
			buf[pos+l]=0x00;
		}
		pos = pos+sk->q_bytes;
	}
 

	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, sk->bv); 
	for(l=tempbuflen; l<sk->q_bytes; l++){
		buf[pos+l]=0x00;
	}
	pos = pos+sk->q_bytes;

	if(pos!=len)
		printf("Something wrong in sk output");
	
	return pos;


}

int pk_out_str(struct PK* pk, unsigned char* buf, int buf_len){
	int i, pos=0, j, l;

        int len = pk->m*F*pk->q_bytes + 2+2+1+1+1+1+pk->q_bytes; 
	if(buf_len < len){
		printf("The buf for pk is too small (out): expected %d, actual %d\n", len, buf_len);	
		return -1;
	}

        buf[pos]  = pk->m;
	pos++;
        buf[pos]  = pk->n;
	pos++;
	buf[pos]  = pk->t_bytes;
	pos++;
	buf[pos]  = pk->q_bytes;
	pos++;
	
	size_t tempbuflen;
	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, pk->wPos); 
	for(l=tempbuflen; l<2; l++){
			buf[pos+l]=0x00;
	}
	pos = pos+2;

	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, pk->wNeg); 
	for(l=tempbuflen; l<2; l++){
			buf[pos+l]=0x00;
	}
	pos = pos+2;

	
	for(i=0; i< pk->m; i++){
		for(j=0; j < F ; j++){
	      		mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, pk->element[j][i]); 
			for(l=tempbuflen; l<pk->q_bytes; l++){
				buf[pos+l]=0x00;
			}
			pos = pos+pk->q_bytes;
		}		
	}


	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, pk->bv); 
	for(l=tempbuflen; l<pk->q_bytes; l++){
		buf[pos+l]=0x00;
	}
	pos = pos+pk->q_bytes;
 

	if(pos!=len)
		printf("Something wrong in pk output");
	
	return pos;

}

void clearPK(struct PK* pk){
	mpz_clear (pk->q);	
	mpz_clear (pk->t);
	mpz_clear (pk->wPos);
	mpz_clear (pk->wNeg);
	mpz_clear (pk->bv);
	int i, pos=0, j, l;
	for(j=0; j <F; j++){
		for(i=0; i < M; i++)
			mpz_clear (pk->element[j][i]);
	}
}

struct PK* pk_in_str(const unsigned char *buf, int buf_len){

	struct PK* pk = malloc(sizeof(struct PK));   
	if(pk==NULL){
		printf("Memory allocation for pk failed\n");	
		return NULL;
	}

	mpz_init (pk->q);	
	mpz_init (pk->t);
	mpz_init (pk->wPos);
	mpz_init (pk->wNeg);
	mpz_init (pk->bv);
	int i, pos=0, j, l;
	for(j=0; j <F; j++){
		for(i=0; i < M; i++)
			mpz_init (pk->element[j][i]);
	}

        pk->m = buf[pos];
	pos++;
        pk->n = buf[pos];
	pos++;
	pk->t_bytes = buf[pos];
	pos++;
	pk->q_bytes = buf[pos];
	pos++;

	//printf("%u, %u, %u \n", buf[0], F, pk->q_bytes); // + 2+2+1+1+1+1+pk->q_bytes

	unsigned int len = pk->m*F*pk->q_bytes + 2+2+1+1+1+1+pk->q_bytes; 
	if(buf_len < len){
		printf("The buf for pk is too small (in): expected %d, actual %d\n", len, buf_len);	
		return NULL;
	}


        mpz_set_ui(pk->q,1); 
	mpz_mul_2exp(pk->q, pk->q, pk->q_bytes*8); 

	
        mpz_set_ui(pk->t,1); 
	mpz_mul_2exp(pk->t, pk->t, pk->t_bytes*8); 

	mpz_import (pk->wPos, 2, -1, 1, 1, 0, buf+pos);  
	pos=pos+2;

	mpz_import (pk->wNeg, 2, -1, 1, 1, 0, buf+pos);  
	pos=pos+2;

	size_t tempbuflen;
	for(i=0; i< M; i++){
		for(j=0; j < F ; j++){
			mpz_import (pk->element[j][i], pk->q_bytes, -1, 1, 1, 0, buf+pos);
			pos = pos+pk->q_bytes;
		}		
	}
	
	mpz_import (pk->bv, pk->q_bytes, -1, 1, 1, 0, buf+pos); 
	pos = pos+pk->q_bytes;

	return pk;
	
}

int cipher_out_str(struct Cipher* D, unsigned char* buf, int buf_len){
	int i, pos=0, j;

	for(i=0; i< N-1; i++){
		

		//if(pos>buf_len){
		//	printf("buf not long enough: expected at least %d, actual %d\n", pos, buf_len);	
		//	return -1;
		//}

		size_t tempbuflen;
      		mpz_export (buf+pos, &tempbuflen, 1, 1, 1, 0, D->head[i]); 
		if(tempbuflen==1){
			buf[pos+1]=buf[pos+0];
			buf[pos+0]=0x00;
		}
		pos=pos+2;

        }

	size_t tempbuflen;
        //unsigned char tempbuf[Q_BYTES];  
	for(j=0; j < F ; j++){
		//if(pos+Q_BYTES>buf_len){
		//	printf("The buf is too small: expected at least %d, actual %d\n", pos+Q_BYTES, buf_len);	
		//	return -1;
		//}

	      	mpz_export (buf+pos, &tempbuflen, -1, 1, 1, 0, D->tail[j]); 
		for(i=tempbuflen; i<(Q_BYTES); i++){
			buf[pos+i]=0x00;
		}
		pos = pos+Q_BYTES;
	}

	//if(pos+T_BYTES>buf_len){
	//		printf("The buf is too small: expected %d, actual %d\n", pos+T_BYTES, buf_len);	
	//		return -1;
	//}

	memcpy(buf+pos, D->cval, T_BYTES);  
	
	pos = pos + T_BYTES;
	return pos;
}



void cipher_in_str(const unsigned char* buf, int* last, struct Cipher* D){  

	int i, pos=0, j;
	for(j=0; j < F; j++)
		mpz_init(D->tail[j]);
        for(i=0; i<N; i++){
		mpz_init(D->head[i]);
	}

	for(i=0; i< N-1; i++){
      		mpz_import (D->head[i], 2, 1, 1, 1, 0, buf+pos);  
		pos=pos+2;
        }

	for(j=0; j < F; j++){
		mpz_import (D->tail[j], Q_BYTES, -1, 1, 1, 0, buf+pos);  
		pos=pos+Q_BYTES;
	}
	memcpy(D->cval, buf+pos, T_BYTES); 
	pos=pos+T_BYTES;

	*last = pos;
		
	return;
}

unsigned long mul_inv( long a, long b)
{
	long b0 = b, t, q;
	long x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return (unsigned long) x1;
}

int dec(struct SK* sk, struct Cipher* D, unsigned char* v){
	//printf("decryption \n"); 

	if(sizeof(unsigned long)!=sk->q_bytes){
		printf("Optimisation of Compact-LWE not supported for non-%u bits platform \n", Q_BYTES*8);
		return -1;
	}
	
	int i, j, l; 

    mpz_t d;
	unsigned long leftsum[F], a, randV=0, b, t;
	for(i=0; i< F; i++){
		leftsum[i] = 0;
	}


    mpz_init(d);

	unsigned long pMod = mpz_get_ui(sk->p);

	for(l=0; l < F; l++){
		for(j=1;j < sk->n; j++){
			a = mpz_get_ui(sk->s[l][j])*mpz_get_ui(D->head[j-1]);
			leftsum[l] = leftsum[l] + a;
		}

		leftsum[l] = mpz_get_ui(D->tail[l]) - leftsum[l];
		leftsum[l] = leftsum[l]*mpz_get_ui(sk->k[l]);

		leftsum[l] = leftsum[l]%pMod;
		mpz_set_ui(d, leftsum[l]);
		mpz_mul(d, d,sk->ck[l]);
		mpz_mod_ui(d, d, pMod);
		
		leftsum[l] = mpz_get_ui(d);

		
		randV = randV + leftsum[l];
		randV = randV % pMod;
	
	}


	t = mpz_get_ui(sk->t);

	a = randV%t;	
	b = randV/t;	
	if(b%2==0){//ensure b coprime with sk->t
		b=b+1;
	}

	unsigned long bInv;
	bInv = mul_inv(b, t);


	unsigned long len;

	unsigned char buf[T_BYTES];

	mpz_t randVMPZ;
	mpz_init(randVMPZ);
	mpz_set_ui(randVMPZ, a);

	for(i=0; i < sk->t_bytes; i++){
		buf[i] = 0x00;//*((unsigned char*)&randV+i);				
	}

	mpz_export (buf, &len, -1, 1, 1, 0, randVMPZ); 

	mpz_import (randVMPZ, sk->t_bytes, -1, 1, 1, 0,  D->cval);

	//printf("randVMPZ= %lu, bInv = %lu \n", mpz_get_ui(randVMPZ), bInv);

	len = mpz_get_ui(randVMPZ)*bInv;
	a = (len)%t; 


	mpz_set_ui(randVMPZ, a);
	for(i=0; i < sk->t_bytes; i++){
		D->cval[i] = 0x00;			
	}
	mpz_export (D->cval, &len, -1, 1, 1, 0, randVMPZ);

	for(i=0; i < sk->t_bytes; i++){
		v[i] = D->cval[i] ^ buf[(i+sk->t_bytes/2)%sk->t_bytes];

	}
	

	mpz_clear(d);
	mpz_clear(randVMPZ);

	return 1;
}



void randomMPZ(int len, mpz_t a){//number of bytes

	mpz_init(a);

	unsigned char buf[32];
	randombytes(buf, len);

	mpz_import (a, len, -1, 1, 1, 0, buf); 


	return;
}


int encode(const unsigned char* buf, unsigned long long buf_len, unsigned char* res, unsigned long long res_len){

	if(buf_len+3>res_len)
		return -1;
	
	unsigned char extra = 0;

	if((buf_len+L+3)%T_BYTES!=0)
		extra = T_BYTES - ((buf_len+L+3)%T_BYTES);


	if(extra==0xff)
		return -1;

	unsigned long i, l=res_len-2;

	unsigned char x, or, y;
	unsigned short r;

		randombytes((unsigned char*)&r, 2);
		res[res_len-2] = *((unsigned char*)&r+0); //r0
		res[res_len-1] = *((unsigned char*)&r+1); //r1

		#ifdef debug
			printf("r1= 0x%02x \n", res[res_len-1]);
			printf("r0= 0x%02x \n", res[res_len-2]);
		#endif

		or=res[res_len-2];
		x = I[or];
		for(i=0; i < l; i++){
			if(i<buf_len)
				res[i] = buf[i]^x;
			else if(i==buf_len)
				res[i] = 0xFF^x;
			else
				res[i] = (L+extra)^x; 
			x= x^I[(res[i]+or)%256];
			res[res_len-2] = res[res_len-2]^((res[i]*res[res_len-1])%256); 
		}
	

		or = res[res_len-1];
		x = I[or];
	        for(i=0; i < l; i++){
			res[l-i-1] = res[l-i-1]^x; 
			x = x^I[(res[l-i-1]+or)%256]; 
			res[res_len-1] = res[res_len-1]^((res[l-i-1]*res[res_len-2])%256);
		}

	return 0;
}

int decode(unsigned char* buf, unsigned long long *buf_len, const unsigned char* res, unsigned long long res_len){
	

	unsigned long i, k;

	unsigned char r0, r1;
	unsigned char x, y;

	 
	unsigned long l=res_len-2; 

	r1 = res[res_len-1];
	r0 = res[res_len-2];

	for(i=0; i<l; i++){
		k = l-1-i;
		r1 = r1^((res[k]*r0)%256);
	}
	
	#ifdef debug
		printf("r1= 0x%02x \n", r1);
	#endif		

	x = I[r1];	
	for(i=0; i<l; i++){
		k = l-1-i;
		y=res[k];
		buf[k] = res[k]^x; 
		x = x^I[(y+r1)%256];
	}

	for(i=0; i<l; i++){
		r0 = r0^((buf[i]*r1)%256);
	}	
	#ifdef debug
		printf("r0= 0x%02x \n", r0);
	#endif

	x = I[r0];
	for(i=0; i<l; i++){
		k =i;
		y = buf [k];
		buf[k] = buf [k]^x; 
		x = x^I[(y+r0)%256];	
	}

	int temp=0;
	unsigned char extra = buf[l-0-1];


	if(extra==0xFF){
		if(L!=0){
			#ifdef debug
				printf("Error: zero L from decoding not expected\n");
			#endif
			*buf_len = 0;
			return -1;
		}
		else{
			*buf_len = l-1;
			return 0;
		}
	}

	for(i=0; i<l; i++){
		if(buf[l-i-1]==extra){
			temp++;
			continue;
		}
		
		if(buf[l-i-1]==0xFF){
			temp++;
			break;
		}
		else{
			#ifdef debug
				printf("Error: no 0xFF found \n");
			#endif
			*buf_len = 0;		
			return -1;
		}				
	}

	if( i==l){
		#ifdef debug
			printf("Error: no 0xFF found \n");
		#endif
		*buf_len = 0;		
		return -1;
	}

	if(temp!=extra+1){
		#ifdef debug
			printf("Error: L from decoding not expected\n");
		#endif
		*buf_len = 0;
		return -1;
	}

	*buf_len = l - temp;

	return 0;
}

