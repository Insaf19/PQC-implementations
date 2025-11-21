
#include "IntermediateKAT.h"

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[MAX_MARKER_LEN];
	int		i, len;
	int curr_line;

	len = (int)strlen(marker);
	if (len > MAX_MARKER_LEN - 1)
		len = MAX_MARKER_LEN - 1;

	for (i = 0; i < len; i++)
	{
		curr_line = fgetc(infile);
		line[i] = curr_line;
		if (curr_line == EOF)
			return 0;
	}
	line[len] = '\0';

	while (1) {
		if (!strncmp(line, marker, len))
			return 1;

		for (i = 0; i < len - 1; i++)
			line[i] = line[i + 1];
		curr_line = fgetc(infile);
		line[len - 1] = curr_line;
		if (curr_line == EOF)
			return 0;
		line[len] = '\0';
	}

	// shouldn't get here
	return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if (Length == 0) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if (FindMarker(infile, str))
		while ((ch = fgetc(infile)) != EOF) {
			if (!isxdigit(ch)) {
				if (!started) {
					if (ch == '\n')
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ((ch >= '0') && (ch <= '9'))
				ich = ch - '0';
			else if ((ch >= 'A') && (ch <= 'F'))
				ich = ch - 'A' + 10;
			else if ((ch >= 'a') && (ch <= 'f'))
				ich = ch - 'a' + 10;
			else // shouldn't ever get here
				ich = 0;

			for (i = 0; i < Length - 1; i++)
				A[i] = (A[i] << 4) | (A[i + 1] >> 4);
			A[Length - 1] = (A[Length - 1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

	fprintf(fp, "%s", S);

	for (i = 0; i < L; i++)
		fprintf(fp, "%02X", A[i]);

	if (L == 0)
		fprintf(fp, "00");

	fprintf(fp, "\n");
}


int intermediateKAT(int degree, long long module)
{
	char                fn_req[50], fn_rsp[50];
	FILE                *fp_req, *fp_rsp;
	unsigned char       seed[48];
	unsigned char       entropy_input[48];
	unsigned char       ct[CRYPTO_CIPHERTEXTBYTES], ss[CRYPTO_BYTES], ss1[CRYPTO_BYTES];
	int                 count;
	int                 done;
	unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
	int                 ret_val;
	memset(&fn_req[0], 0, sizeof(fn_req));
	memset(&fn_rsp[0], 0, sizeof(fn_rsp));
	// Create the REQUEST file
	sprintf(fn_req, "PQCkemKATWithIntermediateValues_%d.req", CRYPTO_SECRETKEYBYTES);
	if ((fp_req = fopen(fn_req, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_req);
		return KAT_FILE_OPEN_ERROR;
	}
	sprintf(fn_rsp, "PQCkemKATWithIntermediateValues_%d.rsp", CRYPTO_SECRETKEYBYTES);
	if ((fp_rsp = fopen(fn_rsp, "w")) == NULL) {
		printf("Couldn't open <%s> for write\n", fn_rsp);
		return KAT_FILE_OPEN_ERROR;
	}

	for (int i = 0; i<48; i++)
		entropy_input[i] = i;

	randombytes_init(entropy_input, NULL, 256);
	for (int i = 0; i<100; i++) {
		fprintf(fp_req, "count = %d\n", i);
		randombytes(seed, 48);
		fprintBstr(fp_req, "seed = ", seed, 48);
		fprintf(fp_req, "pk =\n");
		fprintf(fp_req, "sk =\n");
		fprintf(fp_req, "ct =\n");
		fprintf(fp_req, "ss =\n\n");
	}
	fclose(fp_req);

	//Create the RESPONSE file based on what's in the REQUEST file
	if ((fp_req = fopen(fn_req, "r")) == NULL) {
		printf("Couldn't open <%s> for read\n", fn_req);
		return KAT_FILE_OPEN_ERROR;
	}

	fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
	done = 0;
	do {
		if (FindMarker(fp_req, "count = "))
			fscanf(fp_req, "%d", &count);
		else {
			done = 1;
			break;
		}
		fprintf(fp_rsp, "count = %d\n", count);

		if (!ReadHex(fp_req, seed, 48, "seed = ")) {
			printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
			return KAT_DATA_ERROR;
		}
		fprintBstr(fp_rsp, "seed = ", seed, 48);

		randombytes_init(seed, NULL, 256);
		 
		fprintf(fp_rsp, "mod = %llu\n", module);
		fprintf(fp_rsp, "degree = %d\n", degree); 


		octonion publicOA = buildRandomOctonion(module);
		fprintBstr(fp_rsp, "OA = ",(unsigned char*) &publicOA, sizeof(octonion));
		octonion publicOB = buildRandomOctonion(module);
		fprintBstr(fp_rsp, "OB = ", (unsigned char*)&publicOB, sizeof(octonion));

		HK17PrivateKey* aliceKey = buildPrivateKey(degree, module);
		fprintf(fp_rsp, "m = %llu\n", aliceKey->m );
		fprintf(fp_rsp, "n = %llu\n", aliceKey->n );
		fprintBstr(fp_rsp, "f = ", (unsigned char*)aliceKey->polynomial, (degree * sizeof(polynomialTerm)));

		HK17PrivateKey* bobKey = buildPrivateKey(degree, module);
		fprintf(fp_rsp, "r = %llu\n", bobKey->m);
		fprintf(fp_rsp, "s = %llu\n", bobKey->n);
		fprintBstr(fp_rsp, "h = ", (unsigned char*)bobKey->polynomial, (degree * sizeof(polynomialTerm)));


		octonion aliceToken = calculateToken(publicOA, publicOB, aliceKey);

		fprintBstr(fp_rsp, "RA = ", (unsigned char*)&aliceToken, sizeof(octonion));
		octonion bobToken = calculateToken(publicOA, publicOB, bobKey);
		fprintBstr(fp_rsp, "RB = ", (unsigned char*)&bobToken, sizeof(octonion));
		//session shared knowledge

		octonion aliceSK = calculateToken(publicOA, bobToken, aliceKey);
		fprintBstr(fp_rsp, "K1 = ", (unsigned char*)&aliceToken, sizeof(octonion));
		octonion bobSK = calculateToken(publicOA, aliceToken, bobKey);
		fprintBstr(fp_rsp, "K2 = ", (unsigned char*)&aliceToken, sizeof(octonion));


		if (!octonionEquality(bobSK, aliceSK)) {
			printf("crypto_kem_dec returned bad 'ss' value\n");
			return KAT_CRYPTO_FAILURE;
		}

	} while (!done);

	fclose(fp_req);
	fclose(fp_rsp);

	return KAT_SUCCESS;

}