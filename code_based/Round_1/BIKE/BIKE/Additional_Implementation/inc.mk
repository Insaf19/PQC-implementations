CC := gcc
CPP := g++

INC := -I${ROOT} -I${ROOT}/common -I${ROOT}/decode -I${ROOT}/prf -I${ROOT}/hash -I${ROOT}/gf2x

CFLAGS := -ggdb -m64 -O3 -maes $(INC)

ifdef RDTSC
    CFLAGS += -DRDTSC
endif

ifdef VERBOSE
    CFLAGS += -DVERBOSE=$(VERBOSE)
endif

ifdef BIKE2
    CFLAGS += -DBIKE2
endif

ifdef FIXED_SEED
    CFLAGS += -DFIXED_SEED=1
endif

ifdef NUM_OF_TESTS
    CFLAGS += -DNUM_OF_TESTS=$(NUM_OF_TESTS)
endif

ifdef CHECK_COMPILATION
    CFLAGS += -mno-red-zone -fvisibility=hidden -funsigned-char -Wall -Wextra -Werror -Wpedantic 
endif

ifdef AVX512
    CFLAGS += -mavx512f -DAVX512
    SUF = _avx512
else
    CFLAGS += -mavx2
    SUF = _avx2
endif

ifdef CONSTANT_TIME
    CFLAGS += -DCONSTANT_TIME
endif

ifdef VALIDATE_CONSTANT_TIME
    CFLAGS += -DVALIDATE_CONSTANT_TIME
endif

ifndef PH
    PH = SHA384
endif

ifdef LEVEL
    CFLAGS += -DLEVEL=$(LEVEL)
endif

CFLAGS += -DSHA384

ifdef USE_NIST_RAND
    ifdef FIXED_SEED
        $(error cant have both FIXED_SEED and USE_NIST_RAND)
    endif

    ifndef OPENSSL
        $(error OPENSSL path variable is missing)
    endif

    #Add OpenSSL
    CFLAGS += -I$(OPENSSL)/include -L$(OPENSSL)/lib -lcrypto -lssl -ldl -lpthread 

    #Turn on NIST_RAND
    CFLAGS += -DUSE_NIST_RAND=1
endif