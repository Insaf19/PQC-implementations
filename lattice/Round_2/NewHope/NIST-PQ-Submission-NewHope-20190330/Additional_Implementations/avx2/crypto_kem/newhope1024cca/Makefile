CC = /usr/bin/gcc
CFLAGS = -no-pie -g -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native
LDFLAGS = -lcrypto

SOURCES = kem.c poly.c reduce.c fips202.c  verify.c cpapke.c ntt_double.s ntt.c precomp.c fips202x4.c rng.c PQCgenKAT_kem.c
HEADERS = api.h cpapke.h fips202.h ntt.h params.h poly.h reduce.h rng.h verify.h rng.h
KECCAK  = keccak4x/KeccakP-1600-times4-SIMD256.o

PQCgenKAT_kem: $(SOURCES) $(KECCAK) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(KECCAK) -o $@ $(LDFLAGS)

keccak4x/KeccakP-1600-times4-SIMD256.o: keccak4x/KeccakP-1600-times4-SIMD256.c \
																				keccak4x/align.h \
																				keccak4x/brg_endian.h \
																				keccak4x/KeccakP-1600-times4-SIMD256.c \
																				keccak4x/KeccakP-1600-times4-SnP.h \
																				keccak4x/KeccakP-1600-unrolling.macros \
																				keccak4x/SIMD256-config.h
	$(CC) $(CFLAGS) -c keccak4x/KeccakP-1600-times4-SIMD256.c -o $@



.PHONY: clean

clean:
	-rm PQCgenKAT_kem
	-rm keccak4x/KeccakP-1600-times4-SIMD256.o
