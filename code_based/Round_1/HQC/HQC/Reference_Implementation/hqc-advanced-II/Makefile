
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


%-advanced-II.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@ 


%-advanced-II_v.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@ 


hqc-advanced-II: kem-advanced-II.o hqc-advanced-II.o bch-advanced-II.o parsing-advanced-II.o repetition-advanced-II.o tensor-advanced-II.o vector-advanced-II.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@ 


hqc-advanced-II-verbose: kem-advanced-II_v.o hqc-advanced-II_v.o bch-advanced-II_v.o parsing-advanced-II_v.o repetition-advanced-II_v.o tensor-advanced-II_v.o vector-advanced-II_v.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@ 


hqc-advanced-II-kat: kem-advanced-II.o hqc-advanced-II.o bch-advanced-II.o parsing-advanced-II.o repetition-advanced-II.o tensor-advanced-II.o vector-advanced-II.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) -Wno-unused-result $(CFLAGS) $(KAT_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(KAT)/$@ 


clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin