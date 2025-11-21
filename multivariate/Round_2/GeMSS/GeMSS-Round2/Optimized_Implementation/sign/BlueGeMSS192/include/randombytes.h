#ifndef _RANDOMBYTES_H
#define _RANDOMBYTES_H

#include "debug.h"

#if DEBUG
    /* Set to zero */
    #define ENABLED_OPENSSL_NORMAL 0
#else
    /* Set to 1 to use the standard RNG of OpenSSL */
    #define ENABLED_OPENSSL_NORMAL 1
#endif


#if DEBUG
    #include "rng.h"
    #include "prefix_name.h"
    #define randombytes PREFIX_NAME(randombytes)
#elif ENABLED_OPENSSL_NORMAL
    #include <openssl/rand.h>
    #define randombytes(x,xlen) RAND_bytes(x,(int)xlen)
#else
    #include "rng.h"
    #include "prefix_name.h"
    #define randombytes PREFIX_NAME(randombytes)
#endif

#define randombytes_init PREFIX_NAME(randombytes_init)



#endif
