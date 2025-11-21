
CC=gcc
NO_MPFQ_WARNING:=-Wno-expansion-to-defined
CFLAGS:=-O3 -std=c99 -pedantic # $(NO_MPFQ_WARNING)

HASH_SRC:=lib/hash/hash.c
HASH_INCLUDE:=-I lib/hash -lcrypto

RNG_SRC:=lib/rng/rng.c
RNG_INCLUDE:=-I lib/rng

MPFQ_SRC:=lib/mpfq/src
MPFQ_INCLUDE:=-I lib/mpfq/include
MPFQ_FIELD:=2_89

FFI_SRC:=src/ffi
FFI_INCLUDE:=-I src/ffi -lgmp

SRC:=src
INCLUDE:=-I src $(FFI_INCLUDE)
LIB:=$(MPFQ_INCLUDE) $(HASH_INCLUDE) $(RNG_INCLUDE)

MAIN_RQC:=src/main_rqc.c
MAIN_KAT:=src/main_kat.c

RQC_OBJS:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o q_polynomial.o gabidulin.o rqc.o kem.o
RQC_OBJS_VERBOSE:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o q_polynomial.o gabidulin-verbose.o rqc-verbose.o kem-verbose.o
LIB_OBJS:=libmpfq_$(MPFQ_FIELD).a hash.o rng.o

BUILD:=bin/build
BIN:=bin



folders:
	@echo -e "\n### Creating build folders\n"
	mkdir -p $(BUILD)

hash.o: folders
	@echo -e "\n### Compiling $@ (wrapper around openssl SHA512 implementation)\n"
	$(CC) $(CFLAGS) -c $(HASH_SRC) $(HASH_INCLUDE) -o $(BUILD)/$@

rng.o: folders
	@echo -e "\n### Compiling NIST rng.o\n"
	$(CC) $(CFLAGS) -c $(RNG_SRC) $(RNG_INCLUDE) -o $(BUILD)/$@

libmpfq_$(MPFQ_FIELD).a: folders
	@echo -e "\n### Copying MPFQ library files\n"
	cp $(MPFQ_SRC)/$@ $(BUILD)/$@



ffi_%.o: $(FFI_SRC)/ffi_%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(FFI_INCLUDE) $(LIB) -o $(BUILD)/$@

%.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@

%-verbose.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@ (verbose mode)\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@



rqc128: $(RQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-128\n"
	$(CC) $(CFLAGS) $(MAIN_RQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rqc128-kat: $(RQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-128 KAT\n"
	$(CC) $(CFLAGS) $(MAIN_KAT) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rqc128-verbose: $(RQC_OBJS_VERBOSE) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-128 (verbose mode)\n"
	$(CC) $(CFLAGS) $(MAIN_RQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@



clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin

