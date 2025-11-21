+=============================================================================+
|                                                                             |
|               ***********************************************               |
|               *     POST-QUANTUM CRYPTO STANDARDIZATION     *               |
|               ***********************************************               |
|                                                                             |
|=============================================================================|
|                                                                             |
|        Proposal: HQC                                                        |
|        Principal Submitters (by alphabetical order):                        |
|                  - Carlos AGUILAR MELCHOR                                   |
|                  - Slim BETTAIEB                                            |
|                  - Loïc BIDOUX                                              |
|                  - Olivier BLAZY                                            |
| [backup contact] - Jean-Christophe DENEUVILLE                               |
| [main contact]   - Philippe GABORIT                                         |
|                  - Adrien HAUTEVILLE                                        |
|                  - Edoardo PERSICHETTI                                      |
|                  - Gilles ZÉMOR                                             |
|                                                                             |
|        Inventors: Same as submitters                                        |
|                                                                             |
|        Developers: Same as submitters, and Jurjeb Bos                       |
|                                                                             |
|        Owners: Same as submitters                                           |
|                                                                             |
+=============================================================================+

This archive is a proposal in response to NIST's call for proposal for standar-
dization of quantum-resistant public-key cryptographic algorithms.

This version is submitted for the second round of the standardization process.

HQC provides POST-QUANTUM CODE-BASED PUBLIC KEY ENCRYPTION and targets NIST's 
security levels 1, 3, and 5.

This archive is organized as follows:

===============================================================================

.
├── KATs
│   ├── Optimized_Implementation
│   │   ├── hqc-128-1
│   │   │   ├── hqc_128-1_intermediates_values
│   │   │   ├── hqc_128-1_kat.req
│   │   │   └── hqc_128-1_kat.rsp
│   │   ├── hqc-192-1
│   │   │   ├── hqc_192-1_intermediates_values
│   │   │   ├── hqc_192-1_kat.req
│   │   │   └── hqc_192-1_kat.rsp
│   │   ├── hqc-192-2
│   │   │   ├── hqc_192-2_intermediates_values
│   │   │   ├── hqc_192-2_kat.req
│   │   │   └── hqc_192-2_kat.rsp
│   │   ├── hqc-256-1
│   │   │   ├── hqc_256-1_intermediates_values
│   │   │   ├── hqc_256-1_kat.req
│   │   │   └── hqc_256-1_kat.rsp
│   │   ├── hqc-256-2
│   │   │   ├── hqc_256-2_intermediates_values
│   │   │   ├── hqc_256-2_kat.req
│   │   │   └── hqc_256-2_kat.rsp
│   │   └── hqc-256-3
│   │       ├── hqc_256-3_intermediates_values
│   │       ├── hqc_256-3_kat.req
│   │       └── hqc_256-3_kat.rsp
│   └── Reference_Implementation
│       ├── hqc-128-1
│       │   ├── hqc_128-1_intermediates_values
│       │   ├── hqc_128-1_kat.req
│       │   └── hqc_128-1_kat.rsp
│       ├── hqc-192-1
│       │   ├── hqc_192-1_intermediates_values
│       │   ├── hqc_192-1_kat.req
│       │   └── hqc_192-1_kat.rsp
│       ├── hqc-192-2
│       │   ├── hqc_192-2_intermediates_values
│       │   ├── hqc_192-2_kat.req
│       │   └── hqc_192-2_kat.rsp
│       ├── hqc-256-1
│       │   ├── hqc_256-1_intermediates_values
│       │   ├── hqc_256-1_kat.req
│       │   └── hqc_256-1_kat.rsp
│       ├── hqc-256-2
│       │   ├── hqc_256-2_intermediates_values
│       │   ├── hqc_256-2_kat.req
│       │   └── hqc_256-2_kat.rsp
│       └── hqc-256-3
│           ├── hqc_256-3_intermediates_values
│           ├── hqc_256-3_kat.req
│           └── hqc_256-3_kat.rsp
├── Optimized_Implementation
│   ├── hqc-128-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   ├── hqc-192-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   ├── hqc-192-2
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   ├── hqc-256-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   ├── hqc-256-2
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   ├── hqc-256-3
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.c
│   │       ├── bch.h
│   │       ├── gf2x_avx2.c
│   │       ├── gf2x_avx2.h
│   │       ├── hqc.c
│   │       ├── hqc.h
│   │       ├── kem.c
│   │       ├── main_hqc.c
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.c
│   │       ├── parsing.h
│   │       ├── repetition.c
│   │       ├── repetition.h
│   │       ├── tensor.c
│   │       ├── tensor.h
│   │       ├── vector.c
│   │       └── vector.h
│   └── README
├── README.md
├── Reference_Implementation
│   ├── hqc-128-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   ├── hqc-192-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   ├── hqc-192-2
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   ├── hqc-256-1
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   ├── hqc-256-2
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   ├── hqc-256-3
│   │   ├── doc
│   │   │   ├── biblio.bib
│   │   │   └── main_page.txt
│   │   ├── doxygen.conf
│   │   ├── lib
│   │   │   ├── hash
│   │   │   │   ├── hash.c
│   │   │   │   └── hash.h
│   │   │   └── rng
│   │   │       ├── rng.c
│   │   │       └── rng.h
│   │   ├── Makefile
│   │   └── src
│   │       ├── api.h
│   │       ├── bch.cpp
│   │       ├── bch.h
│   │       ├── gf2x.cpp
│   │       ├── gf2x.h
│   │       ├── hqc.cpp
│   │       ├── hqc.h
│   │       ├── kem.cpp
│   │       ├── main_hqc.cpp
│   │       ├── main_kat.c
│   │       ├── parameters.h
│   │       ├── parsing.cpp
│   │       ├── parsing.h
│   │       ├── repetition.cpp
│   │       ├── repetition.h
│   │       ├── tensor.cpp
│   │       ├── tensor.h
│   │       ├── vector.cpp
│   │       └── vector.h
│   └── README
└── Supporting_Documentation
    ├── HQC_Submission.pdf
    └── tweaks.pdf

===============================================================================

