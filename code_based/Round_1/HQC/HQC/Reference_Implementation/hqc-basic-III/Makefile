
CC:=gcc
CFLAGS:=-O3 -std=c99 -pedantic -Werror -Wall -Wextra

HASH_SRC:=lib/hash/hash.c
HASH_INCLUDE:=-I lib/hash -lcrypto

RNG_SRC:=lib/rng/rng.c
RNG_INCLUDE:=-I lib/rng

LIB:=$(HASH_INCLUDE) $(RNG_INCLUDE)
LIB_OBJS:= hash.o rng.o

SRC:=src
INCLUDE:=-I src
OBJS:=kem hqc bch parsing repetition tensor vector

PERF_MAIN:=src/main_hqc.c
KAT_MAIN:=src//main_kat.c

BIN:=bin
BUILD:=bin/build
KAT:=bin/

folders:
	@echo -e "\n### Creating folders\n"
	mkdir -p $(BUILD)
	mkdir -p $(KAT)

hash.o: folders
	@echo -e "\n### Compiling Hash function\n"	
	$(CC) $(CFLAGS) -c $(HASH_SRC) $(HASH_INCLUDE) -o $(BUILD)/$@

rng.o: folders
	@echo -e "\n### Compiling Random Number Generator\n"	
	$(CC) -O3 -c $(RNG_SRC) $(RNG_INCLUDE) -o $(BUILD)/$@


%-basic-III.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@ 


%-basic-III_v.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@ 


hqc-basic-III: kem-basic-III.o hqc-basic-III.o bch-basic-III.o parsing-basic-III.o repetition-basic-III.o tensor-basic-III.o vector-basic-III.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@ 


hqc-basic-III-verbose: kem-basic-III_v.o hqc-basic-III_v.o bch-basic-III_v.o parsing-basic-III_v.o repetition-basic-III_v.o tensor-basic-III_v.o vector-basic-III_v.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@ 


hqc-basic-III-kat: kem-basic-III.o hqc-basic-III.o bch-basic-III.o parsing-basic-III.o repetition-basic-III.o tensor-basic-III.o vector-basic-III.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) -Wno-unused-result $(CFLAGS) $(KAT_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(KAT)/$@ 


clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin