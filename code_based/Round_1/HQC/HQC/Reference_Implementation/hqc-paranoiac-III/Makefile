
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


%-paranoiac-III.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@ 


%-paranoiac-III_v.o: $(SRC)/%.c | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@ 


hqc-paranoiac-III: kem-paranoiac-III.o hqc-paranoiac-III.o bch-paranoiac-III.o parsing-paranoiac-III.o repetition-paranoiac-III.o tensor-paranoiac-III.o vector-paranoiac-III.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@ 


hqc-paranoiac-III-verbose: kem-paranoiac-III_v.o hqc-paranoiac-III_v.o bch-paranoiac-III_v.o parsing-paranoiac-III_v.o repetition-paranoiac-III_v.o tensor-paranoiac-III_v.o vector-paranoiac-III_v.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) $(CFLAGS) $(PERF_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@ 


hqc-paranoiac-III-kat: kem-paranoiac-III.o hqc-paranoiac-III.o bch-paranoiac-III.o parsing-paranoiac-III.o repetition-paranoiac-III.o tensor-paranoiac-III.o vector-paranoiac-III.o hash.o rng.o
	@echo -e "\n### Compiling HQC Basic I\n"	
	$(CC) -Wno-unused-result $(CFLAGS) $(KAT_MAIN) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(KAT)/$@ 


clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin