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
|                  - Nicolas ARAGON                                           |
|                  - Slim BETTAIEB                                            |
|                  - Loïc BIDOUX                                              |
|                  - Olivier BLAZY                                            |
| [backup contact] - Jean-Christophe DENEUVILLE                               |
| [main contact]   - Philippe GABORIT                                         |
|                  - Edoardo PERSICHETTI                                      |
|                  - Gilles ZÉMOR                                             |
|                                                                             |
|        Inventors: Same as submitters                                        |
|                                                                             |
|        Developers: Same as submitters                                       |
|                                                                             |
|        Owners: Same as submitters                                           |
|                                                                             |
+=============================================================================+

This archive is a proposal in response to NIST's call for proposal for standar-
dization of quantum-resistant public-key cryptographic algorithms.

HQC provides POST-QUANTUM CODE-BASED PUBLIC KEY ENCRYPTION and targets NIST's 
security levels 1, 3, and 5.

This archive is organized as follows:

===============================================================================

.
├── KATs: Known Answer Test values
│   ├── Optimized_Implementation: This folder is copy of KATs/Reference_Implementation
│   │   ├── hqc-advanced-I 
│   │   │   ├── hqc-advanced-I_kat.int: Intermediate values for hqc-advanced-I
│   │   │   ├── hqc-advanced-I_kat.req: Req file for hqc-advanced-I
│   │   │   └── hqc-advanced-I_kat.rsp: Rsp file for hqc-advanced-I
│   │   ├── hqc-advanced-II: KATs for hqc-advanced-II (security level 3, failure probability 2^{-128})
│   │   │   ├── hqc-advanced-II_kat.int: Intermediate values for hqc-advanced-II
│   │   │   ├── hqc-advanced-II_kat.req: Req file for hqc-advanced-II
│   │   │   └── hqc-advanced-II_kat.rsp: Rsp file for hqc-advanced-II
│   │   ├── hqc-advanced-III: KATs for hqc-advanced-III (security level 3, failure probability 2^{-192})
│   │   │   ├── hqc-advanced-III_kat.int: Intermediate values for hqc-advanced-III
│   │   │   ├── hqc-advanced-III_kat.req: Req file for hqc-advanced-III
│   │   │   └── hqc-advanced-III_kat.rsp: Rsp file for hqc-advanced-III
│   │   ├── hqc-basic-I: KATs for hqc-basic-I (security level 1, failure probability 2^{-64})
│   │   │   ├── hqc-basic-I_kat.int: Intermediate values for hqc-basic-I
│   │   │   ├── hqc-basic-I_kat.req: Req file for hqc-basic-I
│   │   │   └── hqc-basic-I_kat.rsp: Rsp file for hqc-basic-I
│   │   ├── hqc-basic-II: KATs for hqc-basic-II (security level 1, failure probability 2^{-96})
│   │   │   ├── hqc-basic-II_kat.int: Intermediate values for hqc-basic-II
│   │   │   ├── hqc-basic-II_kat.req: Req file for hqc-basic-II
│   │   │   └── hqc-basic-II_kat.rsp: Rsp file for hqc-basic-II
│   │   ├── hqc-basic-III: KATs for hqc-basic-III (security level 1, failure probability 2^{-128})
│   │   │   ├── hqc-basic-III_kat.int: Intermediate values for hqc-basic-III
│   │   │   ├── hqc-basic-III_kat.req: Req file for hqc-basic-III
│   │   │   └── hqc-basic-III_kat.rsp: Rsp file for hqc-basic-III
│   │   ├── hqc-paranoiac-I: KATs for hqc-paranoiac-I (security level 5, failure probability 2^{-64})
│   │   │   ├── hqc-paranoiac-I_kat.int: Intermediate values for hqc-paranoiac-I
│   │   │   ├── hqc-paranoiac-I_kat.req: Req file for hqc-paranoiac-I
│   │   │   └── hqc-paranoiac-I_kat.rsp: Rsp file for hqc-paranoiac-I
│   │   ├── hqc-paranoiac-II: KATs for hqc-paranoiac-II (security level 5, failure probability 2^{-128})
│   │   │   ├── hqc-paranoiac-II_kat.int: Intermediate values for hqc-paranoiac-II
│   │   │   ├── hqc-paranoiac-II_kat.req: Req file for hqc-paranoiac-II
│   │   │   └── hqc-paranoiac-II_kat.rsp: Rsp file for hqc-paranoiac-II
│   │   ├── hqc-paranoiac-III: KATs for hqc-paranoiac-III (security level 5, failure probability 2^{-192})
│   │   │   ├── hqc-paranoiac-III_kat.int: Intermediate values for hqc-paranoiac-III
│   │   │   ├── hqc-paranoiac-III_kat.req: Req file for hqc-paranoiac-III
│   │   │   └── hqc-paranoiac-III_kat.rsp: Rsp file for hqc-paranoiac-III
│   │   └── hqc-paranoiac-IV: KATs for hqc-paranoiac-IV (security level 5, failure probability 2^{-256})
│   │       ├── hqc-paranoiac-IV_kat.int: Intermediate values for hqc-paranoiac-IV
│   │       ├── hqc-paranoiac-IV_kat.req: Req file for hqc-paranoiac-IV
│   │       └── hqc-paranoiac-IV_kat.rsp: Rsp file for hqc-paranoiac-IV
│   └── Reference_Implementation: KATs for reference implementation
│       ├── hqc-advanced-I: KATs for hqc-advanced-I (security level 3, failure probability 2^{-64})
│       │   ├── hqc-advanced-I_kat.int: Intermediate values for hqc-advanced-I
│       │   ├── hqc-advanced-I_kat.req: Req file for hqc-advanced-I
│       │   └── hqc-advanced-I_kat.rsp: Rsp file for hqc-advanced-I
│       ├── hqc-advanced-II: KATs for hqc-advanced-II (security level 3, failure probability 2^{-128})
│       │   ├── hqc-advanced-II_kat.int: Intermediate values for hqc-advanced-II
│       │   ├── hqc-advanced-II_kat.req: Req file for hqc-advanced-II
│       │   └── hqc-advanced-II_kat.rsp: Rsp file for hqc-advanced-II
│       ├── hqc-advanced-III: KATs for hqc-advanced-III (security level 3, failure probability 2^{-192})
│       │   ├── hqc-advanced-III_kat.int: Intermediate values for hqc-advanced-III
│       │   ├── hqc-advanced-III_kat.req: Req file for hqc-advanced-III
│       │   └── hqc-advanced-III_kat.rsp: Rsp file for hqc-advanced-III
│       ├── hqc-basic-I: KATs for hqc-basic-I (security level 1, failure probability 2^{-64})
│       │   ├── hqc-basic-I_kat.int: Intermediate values for hqc-basic-I
│       │   ├── hqc-basic-I_kat.req: Req file for hqc-basic-I
│       │   └── hqc-basic-I_kat.rsp: Rsp file for hqc-basic-I
│       ├── hqc-basic-II: KATs for hqc-basic-II (security level 1, failure probability 2^{-96})
│       │   ├── hqc-basic-II_kat.int: Intermediate values for hqc-basic-II
│       │   ├── hqc-basic-II_kat.req: Req file for hqc-basic-II
│       │   └── hqc-basic-II_kat.rsp: Rsp file for hqc-basic-II
│       ├── hqc-basic-III: KATs for hqc-basic-III (security level 1, failure probability 2^{-128})
│       │   ├── hqc-basic-III_kat.int: Intermediate values for hqc-basic-III
│       │   ├── hqc-basic-III_kat.req: Req file for hqc-basic-III
│       │   └── hqc-basic-III_kat.rsp: Rsp file for hqc-basic-III
│       ├── hqc-paranoiac-I: KATs for hqc-paranoiac-I (security level 5, failure probability 2^{-64})
│       │   ├── hqc-paranoiac-I_kat.int: Intermediate values for hqc-paranoiac-I
│       │   ├── hqc-paranoiac-I_kat.req: Req file for hqc-paranoiac-I
│       │   └── hqc-paranoiac-I_kat.rsp: Rsp file for hqc-paranoiac-I
│       ├── hqc-paranoiac-II: KATs for hqc-paranoiac-II (security level 5, failure probability 2^{-128})
│       │   ├── hqc-paranoiac-II_kat.int: Intermediate values for hqc-paranoiac-II
│       │   ├── hqc-paranoiac-II_kat.req: Req file for hqc-paranoiac-II
│       │   └── hqc-paranoiac-II_kat.rsp: Rsp file for hqc-paranoiac-II
│       ├── hqc-paranoiac-III: KATs for hqc-paranoiac-III (security level 5, failure probability 2^{-192})
│       │   ├── hqc-paranoiac-III_kat.int: Intermediate values for hqc-paranoiac-III
│       │   ├── hqc-paranoiac-III_kat.req: Req file for hqc-paranoiac-III
│       │   └── hqc-paranoiac-III_kat.rsp: Rsp file for hqc-paranoiac-III
│       └── hqc-paranoiac-IV: KATs for hqc-paranoiac-IV (security level 5, failure probability 2^{-256})
│           ├── hqc-paranoiac-IV_kat.int: Intermediate values for hqc-paranoiac-IV
│           ├── hqc-paranoiac-IV_kat.req: Req file for hqc-paranoiac-IV
│           └── hqc-paranoiac-IV_kat.rsp: Rsp file for hqc-paranoiac-IV
├── Optimized_Implementation: This folder is copy of the folder Reference_Implementation
│   ├── hqc-advanced-I: Implementation of hqc-advanced-I (security level 3, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-advanced-II: Implementation of hqc-advanced-II (security level 3, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-advanced-III: Implementation of hqc-advanced-III (security level 3, failure probability 2^{-192})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-I: Implementation of hqc-basic-I (security level 1, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-II: Implementation of hqc-basic-II (security level 1, failure probability 2^{-96})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-III: Implementation of hqc-basic-III (security level 1, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-I: Implementation of hqc-paranoiac-I (security level 5, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-II: Implementation of hqc-paranoiac-II (security level 5, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-III: Implementation of hqc-paranoiac-III (security level 5, failure probability 2^{-192})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-IV: Implementation of hqc-paranoiac-IV (security level 5, failure probability 2^{-256})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   └── README: Readme file with compilation instructions
├── README.md: This file
├── Reference_Implementation: HQC reference implementation
│   ├── hqc-advanced-I: Implementation of hqc-advanced-I (security level 3, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-advanced-II: Implementation of hqc-advanced-II (security level 3, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-advanced-III: Implementation of hqc-advanced-III (security level 3, failure probability 2^{-192})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-I: Implementation of hqc-basic-I (security level 1, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-II: Implementation of hqc-basic-II (security level 1, failure probability 2^{-96})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-basic-III: Implementation of hqc-basic-III (security level 1, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-I: Implementation of hqc-paranoiac-I (security level 5, failure probability 2^{-64})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-II: Implementation of hqc-paranoiac-II (security level 5, failure probability 2^{-128})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-III: Implementation of hqc-paranoiac-III (security level 5, failure probability 2^{-192})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   ├── hqc-paranoiac-IV: Implementation of hqc-paranoiac-IV (security level 5, failure probability 2^{-256})
│   │   ├── doc:Technical documentation folder
│   │   │   ├── biblio.bib: References used in the documentation
│   │   │   ├── doc_bch.pdf: A technical document that details BCH codes and the decoding algorithm used in this implementation
│   │   │   ├── doc_mul.pdf: A technical document that explains the multiplication algorithm used in the implementation
│   │   │   └── main_page.txt: Main page of the documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST rng
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: HQC source folder
│   │       ├── api.h: API file for the HQC KEM IND-CCA2 scheme
│   │       ├── bch.c: Implementation of bch.h
│   │       ├── bch.h: Functions to encode and decode messages using BCH codes
│   │       ├── hqc.c: Implementation of hqc.h
│   │       ├── hqc.h: Functions of the HQC PKE IND-CPA scheme
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_hqc.c: HQC KEM IND-CCA2 working example
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── parameters.h: Parameters of the HQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── repetition.c: Implementation of repetition.h
│   │       ├── repetition.h: Functions to encode and decode messages using repetition code
│   │       ├── tensor.c: Implementation of tensor.h
│   │       ├── tensor.h: Functions to encode and decode messages using tensor code
│   │       ├── vector.c: Implementation of vector.h
│   │       └── vector.h: Functions to manipulate vectors
│   └── README: Readme file with compilation instructions
└── Supporting_Documentation
    └── HQC_Submission.pdf: Complete specification for our proposal

===============================================================================

The authors did their best to make this archive complete and proper.
    
-------------------------------------------------------------------------------

Important note regarding Intellectual Property.

As requested by the NIST, the statements will be sent to Dustin MOODY at the 
address provided by the NIST (see below) *and/or* given to NIST at the first 
PQC Standardization Conference 

Dustin MOODY
Information Technology Laboratory
Attention: Post-Quantum Cryptographic Algorithm Submissions
100 Bureau Drive – Stop 8930
National Institute of Standards and Technology
Gaithersburg, MD 20899-8930

Please note that in the meantime, electronic copies of these statements have
been included in appendix to the supporting documentation.

