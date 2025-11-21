LDFLAGS = -fPIC -lssl -lcrypto
CFLAGS = -O2 -std=c99

OBJS = rng.o \
	encrypt.o \
	compact-lwe.o \
	mini-gmp.o \
	PQCgenKAT_encrypt.o

PERFOBJS = rng.o \
	encrypt.o \
	compact-lwe.o \
	mini-gmp.o \
	Performance-test.o

PQCgenKAT_encrypt : $(OBJS)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.c
	gcc $(CFLAGS) -o $@ -c $<

rng.o : rng.h
encrypt.o : api.h
compact-lwe.o : compact-lwe.h
mini-gmp.o : mini-gmp.h
PQCgenKAT_encrypt.o : rng.h compact-lwe.h 

.PHONY: clean

.PHONY: perf


perf : $(PERFOBJS)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f PQCgenKAT_encrypt perf *.o 
