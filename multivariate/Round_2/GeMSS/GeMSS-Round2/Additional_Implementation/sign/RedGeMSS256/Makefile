LOCAL=/usr/local

HEAD=$(wildcard include/*.h)
SRC=$(wildcard src/*.c)
OBJS=$(SRC:.c=.o)

CC=gcc
LDFLAGS=-lgf2x -lkeccak -lcrypto -ldl -lpthread
# CFLAGS=-Wall -O4 -mavx2 -mpclmul -mpopcnt -funroll-loops -I include/ -I $(LOCAL)/include -L $(LOCAL)/lib
CFLAGS=-Wall -O4 -march=native -mtune=native -funroll-loops -I include/ -I $(LOCAL)/include -L $(LOCAL)/lib

all: PQCgenKAT_sign


PQCgenKAT_sign: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<


cleanKAT:
	rm -f PQCsignKAT_*.int PQCsignKAT_*.req PQCsignKAT_*.rsp

clean:
	rm -f PQCgenKAT_sign src/*.o
