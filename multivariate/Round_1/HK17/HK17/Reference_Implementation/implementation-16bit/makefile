SRC=octonions.c lib.c rng.c HK17.c HK17_api.c 
CC=gcc
FLAGS= -ansi -std=c99 -pedantic  
DEP= -lcrypto
all: help

help:
			@echo "compile a KAT generator, a small benchmark program, or a library:"
			@echo "\tkat\t\t builds an executable to build kat files"
			@echo "\ttest\t\t builds an executable for benchmarking purposes"
			@echo "\tapi\t\t builds a library respecting api.h to be included"

kat:		        $(SRC) PQCgenKAT_kem.c
			$(CC) $(FLAGS)  $^ -o katGenerator $(DEP)
			./katGenerator
test:		        $(SRC) program.c IntermediateKAT.c octonionTest.c
			$(CC) $(FLAGS)  $^ -o testBench $(DEP)
			./testBench
api:				$(SRC)
			$(CC) -c $(FLAGS)  $^  $(DEP)
			ar  rcs api.a      HK17_api.o
  