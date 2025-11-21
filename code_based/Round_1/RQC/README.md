+=============================================================================+
|                                                                             |
|               ***********************************************               |
|               *     POST-QUANTUM CRYPTO STANDARDIZATION     *               |
|               ***********************************************               |
|                                                                             |
|=============================================================================|
|                                                                             |
|        Proposal: RQC                                                        |
|        Principal Submitters (by alphabetical order):                        |
|                  - Carlos AGUILAR MELCHOR                                   |
|                  - Nicolas ARAGON                                           |
|                  - Slim BETTAIEB                                            |
|                  - Loïc BIDOUX                                              |
|                  - Olivier BLAZY                                            |
| [backup contact] - Jean-Christophe DENEUVILLE                               |
| [main contact]   - Philippe GABORIT                                         |
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

RQC provides POST-QUANTUM CODE-BASED PUBLIC KEY ENCRYPTION and targets NIST's 
security levels 1, 3, and 5.

This archive is organized as follows:

===============================================================================

.
├── KATs: Known Answer Test values
│   ├── Optimized_Implementation: This folder is a copy of KATs/Reference_Implementation
│   │   ├── rqc128
│   │   │   ├── rqc128_intermediate_values
│   │   │   ├── rqc128_kat.req
│   │   │   └── rqc128_kat.rsp
│   │   ├── rqc192
│   │   │   ├── rqc192_intermediate_values
│   │   │   ├── rqc192_kat.req
│   │   │   └── rqc192_kat.rsp
│   │   └── rqc256
│   │       ├── rqc256_intermediate_values
│   │       ├── rqc256_kat.req
│   │       └── rqc256_kat.rsp
│   └── Reference_Implementation: KATs for reference implementation
│       ├── rqc128: KATs for RQC-128 (security level 1)
│       │   ├── rqc128_intermediate_values: Intermediate values for RQC-128
│       │   ├── rqc128_kat.req: Req file for RQC-128
│       │   └── rqc128_kat.rsp: Rsp file for RQC-128
│       ├── rqc192: KATs for RQC-192 (security level 3)
│       │   ├── rqc192_intermediate_values: Intermediate values for RQC-192
│       │   ├── rqc192_kat.req: Req file for RQC-192
│       │   └── rqc192_kat.rsp: Rsp file for RQC-192
│       └── rqc256: KATs for RQC-256 (security level 5)
│           ├── rqc256_intermediate_values: Intermediate values for RQC-256
│           ├── rqc256_kat.req: Req file for RQC-256
│           └── rqc256_kat.rsp: Rsp file for RQC-256
├── Optimized_Implementation: This folder is a copy of Reference_Implementation
│   ├── README: Readme file with compilation instructions
│   ├── rqc128: Implementation of RQC-128 (security level 1)
│   │   ├── configure: Configuration file for compilation
│   │   ├── doc: Technical documentation folder
│   │   │   ├── main_page.txt: Main page of the technical documentation
│   │   │   └── refs.bib: References for the technical documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation 
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│   │   │   ├── mpfq: MPFQ library source code
│   │   │   │   └── mpfq-1.1
│   │   │   │       ├── Copying
│   │   │   │       ├── doc
│   │   │   │       │   ├── api.xml
│   │   │   │       │   ├── design.xml
│   │   │   │       │   ├── doc.xml
│   │   │   │       │   ├── fieldimpl.xml
│   │   │   │       │   ├── install.xml
│   │   │   │       │   ├── intro.xml
│   │   │   │       │   ├── Makefile
│   │   │   │       │   ├── mpfqdoc.dtd
│   │   │   │       │   ├── parsemath.pl
│   │   │   │       │   ├── perl-lib
│   │   │   │       │   │   └── XML
│   │   │   │       │   │       └── Reprocess.pm
│   │   │   │       │   ├── README
│   │   │   │       │   ├── tuning.xml
│   │   │   │       │   └── xsl
│   │   │   │       │       ├── custom-fo.xsl
│   │   │   │       │       ├── custom-xhtml.xsl
│   │   │   │       │       ├── custom.xsl
│   │   │   │       │       ├── fo.xsl
│   │   │   │       │       ├── xhtml-nochunks.xsl
│   │   │   │       │       └── xhtml.xsl
│   │   │   │       └── src
│   │   │   │           ├── api.pl
│   │   │   │           ├── apps
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── curve2_251.c
│   │   │   │           │   ├── curve25519.c
│   │   │   │           │   ├── surf127eps.c
│   │   │   │           │   └── surf2_113.c
│   │   │   │           ├── benches
│   │   │   │           │   ├── bench.pl
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fieldop.c
│   │   │   │           │   └── mpfqbench.pl
│   │   │   │           ├── CMakeLists.txt
│   │   │   │           ├── CMakeMacros.txt
│   │   │   │           ├── fixmp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fixmp.h.in
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── gen_mp_longlong.pl
│   │   │   │           │   │   ├── gen_mp_test.pl
│   │   │   │           │   │   ├── gen_mp_x86_32.pl
│   │   │   │           │   │   └── gen_mp_x86_64.pl
│   │   │   │           │   └── README
│   │   │   │           ├── gf2n
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fields.data
│   │   │   │           │   ├── gen_gf2n.pl
│   │   │   │           │   ├── helper
│   │   │   │           │   │   ├── bitlinalg.c
│   │   │   │           │   │   ├── bitlinalg.h
│   │   │   │           │   │   ├── CMakeLists.txt
│   │   │   │           │   │   ├── helper.c
│   │   │   │           │   │   ├── wmat.c
│   │   │   │           │   │   └── wmat.h
│   │   │   │           │   ├── mpfq_gf2n_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   └── gf64.pm
│   │   │   │           │   └── tracer
│   │   │   │           │       ├── tracer.h.meta
│   │   │   │           │       └── tracer.pl
│   │   │   │           ├── gf2x
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── dump_poly.h
│   │   │   │           │   ├── tuning-summary.sh
│   │   │   │           │   ├── wizard.pl
│   │   │   │           │   └── wiztest.c
│   │   │   │           ├── gf7
│   │   │   │           │   ├── gen_gf7.pl
│   │   │   │           │   ├── gf7.pm
│   │   │   │           │   └── README
│   │   │   │           ├── gfp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfp.pl
│   │   │   │           │   ├── mpfq_gfp_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── p127_1.pm
│   │   │   │           │   │   ├── p127_735.pm
│   │   │   │           │   │   └── p25519.pm
│   │   │   │           │   └── TODO_for_speed
│   │   │   │           ├── gfpe
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfpe.pl
│   │   │   │           │   ├── mpfq_gfpe_common.h
│   │   │   │           │   └── perl
│   │   │   │           │       ├── elt.pm
│   │   │   │           │       ├── elt_ur.pm
│   │   │   │           │       ├── field.pm
│   │   │   │           │       ├── gfpe.pm
│   │   │   │           │       └── io.pm
│   │   │   │           ├── include
│   │   │   │           │   ├── mpfq
│   │   │   │           │   │   └── mpfq.h
│   │   │   │           │   └── timing.h
│   │   │   │           ├── perl-lib
│   │   │   │           │   └── Mpfq
│   │   │   │           │       ├── defaults
│   │   │   │           │       │   ├── flatdata.pm
│   │   │   │           │       │   ├── mpi_flat.pm
│   │   │   │           │       │   ├── polygcd.pm
│   │   │   │           │       │   ├── poly.pm
│   │   │   │           │       │   ├── pow.pm
│   │   │   │           │       │   ├── vec
│   │   │   │           │       │   │   ├── addsub.pm
│   │   │   │           │       │   │   ├── alloc.pm
│   │   │   │           │       │   │   ├── conv.pm
│   │   │   │           │       │   │   ├── flatdata.pm
│   │   │   │           │       │   │   ├── getset.pm
│   │   │   │           │       │   │   ├── io.pm
│   │   │   │           │       │   │   └── mul.pm
│   │   │   │           │       │   └── vec.pm
│   │   │   │           │       ├── defaults.pm
│   │   │   │           │       ├── engine
│   │   │   │           │       │   ├── conf.pm
│   │   │   │           │       │   ├── handler.pm
│   │   │   │           │       │   ├── maketext.pm
│   │   │   │           │       │   ├── oo.pm
│   │   │   │           │       │   ├── postprocess.pm
│   │   │   │           │       │   └── utils.pm
│   │   │   │           │       ├── gf2n
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── inversion.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   ├── linearops.pm
│   │   │   │           │       │   ├── mul.pm
│   │   │   │           │       │   ├── reduction.pm
│   │   │   │           │       │   ├── squaring.pm
│   │   │   │           │       │   ├── trivialities.pm
│   │   │   │           │       │   └── utils
│   │   │   │           │       │       └── poly.pm
│   │   │   │           │       ├── gf2n.pm
│   │   │   │           │       ├── gf2x
│   │   │   │           │       │   ├── details
│   │   │   │           │       │   │   ├── basecase.pm
│   │   │   │           │       │   │   ├── extra.pm
│   │   │   │           │       │   │   ├── kara.pm
│   │   │   │           │       │   │   ├── schoolbook.pm
│   │   │   │           │       │   │   └── sse2.pm
│   │   │   │           │       │   ├── utils
│   │   │   │           │       │   │   ├── align.pm
│   │   │   │           │       │   │   └── bitops.pm
│   │   │   │           │       │   └── wizard
│   │   │   │           │       │       ├── coldstore.pm
│   │   │   │           │       │       └── discard.pm
│   │   │   │           │       ├── gf2x.pm
│   │   │   │           │       ├── gfp
│   │   │   │           │       │   ├── elt.pm
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   └── mgy
│   │   │   │           │       │       ├── codec.pm
│   │   │   │           │       │       ├── elt.pm
│   │   │   │           │       │       ├── field.pm
│   │   │   │           │       │       └── io.pm
│   │   │   │           │       ├── gfpmgy.pm
│   │   │   │           │       └── gfp.pm
│   │   │   │           ├── scripts
│   │   │   │           │   ├── machine.sh
│   │   │   │           │   └── wordsize.sh
│   │   │   │           ├── simd
│   │   │   │           │   ├── abase.pl
│   │   │   │           │   ├── binary-dotprods-backends.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── io.pm
│   │   │   │           │   │   ├── p16.pm
│   │   │   │           │   │   ├── simd_char2.pm
│   │   │   │           │   │   ├── simd_dotprod.pm
│   │   │   │           │   │   ├── simd_flat.pm
│   │   │   │           │   │   ├── simd_gfp.pm
│   │   │   │           │   │   ├── simd_multiplex.pm
│   │   │   │           │   │   ├── simd_noflat.pm
│   │   │   │           │   │   ├── simd_p16.pm
│   │   │   │           │   │   ├── simd_u64k.pm
│   │   │   │           │   │   ├── simd_u64n.pm
│   │   │   │           │   │   └── trivialities.pm
│   │   │   │           │   ├── README
│   │   │   │           │   └── README.oo
│   │   │   │           └── test
│   │   │   │               ├── CMakeLists.txt
│   │   │   │               ├── mk_name_k.pl
│   │   │   │               ├── mpfq_test.c.meta
│   │   │   │               └── README
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST fonctions for randomness generation
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: RQC source folder
│   │       ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│   │       ├── ffi: Finite field interface folder
│   │       │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│   │       │   ├── ffi_elt.h: Interface for finite field elements
│   │       │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│   │       │   ├── ffi_field.h: Interface for finite fields
│   │       │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│   │       │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│   │       │   └── ffi_vec.h: Interface for vectors over finite fields 
│   │       ├── gabidulin.c: Implementation of gabidulin.h
│   │       ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── main_rqc.c: RQC KEM IND-CCA2 working example
│   │       ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── q_polynomial.c: Implementation of q_polynomial.h
│   │       ├── q_polynomial.h: Functions to manipulate q_polynomials
│   │       ├── rqc.c: Implementation of rqc.h
│   │       └── rqc.h: Functions of the RQC PKE IND-CPA scheme
│   ├── rqc192: Implementation of RQC-192 (security level 3)
│   │   ├── configure: Configuration file for compilation
│   │   ├── doc: Technical documentation folder
│   │   │   ├── main_page.txt: Main page of the technical documentation
│   │   │   └── refs.bib: References for the technical documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation 
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│   │   │   ├── mpfq: MPFQ library source code
│   │   │   │   └── mpfq-1.1
│   │   │   │       ├── Copying
│   │   │   │       ├── doc
│   │   │   │       │   ├── api.xml
│   │   │   │       │   ├── design.xml
│   │   │   │       │   ├── doc.xml
│   │   │   │       │   ├── fieldimpl.xml
│   │   │   │       │   ├── install.xml
│   │   │   │       │   ├── intro.xml
│   │   │   │       │   ├── Makefile
│   │   │   │       │   ├── mpfqdoc.dtd
│   │   │   │       │   ├── parsemath.pl
│   │   │   │       │   ├── perl-lib
│   │   │   │       │   │   └── XML
│   │   │   │       │   │       └── Reprocess.pm
│   │   │   │       │   ├── README
│   │   │   │       │   ├── tuning.xml
│   │   │   │       │   └── xsl
│   │   │   │       │       ├── custom-fo.xsl
│   │   │   │       │       ├── custom-xhtml.xsl
│   │   │   │       │       ├── custom.xsl
│   │   │   │       │       ├── fo.xsl
│   │   │   │       │       ├── xhtml-nochunks.xsl
│   │   │   │       │       └── xhtml.xsl
│   │   │   │       └── src
│   │   │   │           ├── api.pl
│   │   │   │           ├── apps
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── curve2_251.c
│   │   │   │           │   ├── curve25519.c
│   │   │   │           │   ├── surf127eps.c
│   │   │   │           │   └── surf2_113.c
│   │   │   │           ├── benches
│   │   │   │           │   ├── bench.pl
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fieldop.c
│   │   │   │           │   └── mpfqbench.pl
│   │   │   │           ├── CMakeLists.txt
│   │   │   │           ├── CMakeMacros.txt
│   │   │   │           ├── fixmp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fixmp.h.in
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── gen_mp_longlong.pl
│   │   │   │           │   │   ├── gen_mp_test.pl
│   │   │   │           │   │   ├── gen_mp_x86_32.pl
│   │   │   │           │   │   └── gen_mp_x86_64.pl
│   │   │   │           │   └── README
│   │   │   │           ├── gf2n
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fields.data
│   │   │   │           │   ├── gen_gf2n.pl
│   │   │   │           │   ├── helper
│   │   │   │           │   │   ├── bitlinalg.c
│   │   │   │           │   │   ├── bitlinalg.h
│   │   │   │           │   │   ├── CMakeLists.txt
│   │   │   │           │   │   ├── helper.c
│   │   │   │           │   │   ├── wmat.c
│   │   │   │           │   │   └── wmat.h
│   │   │   │           │   ├── mpfq_gf2n_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   └── gf64.pm
│   │   │   │           │   └── tracer
│   │   │   │           │       ├── tracer.h.meta
│   │   │   │           │       └── tracer.pl
│   │   │   │           ├── gf2x
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── dump_poly.h
│   │   │   │           │   ├── tuning-summary.sh
│   │   │   │           │   ├── wizard.pl
│   │   │   │           │   └── wiztest.c
│   │   │   │           ├── gf7
│   │   │   │           │   ├── gen_gf7.pl
│   │   │   │           │   ├── gf7.pm
│   │   │   │           │   └── README
│   │   │   │           ├── gfp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfp.pl
│   │   │   │           │   ├── mpfq_gfp_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── p127_1.pm
│   │   │   │           │   │   ├── p127_735.pm
│   │   │   │           │   │   └── p25519.pm
│   │   │   │           │   └── TODO_for_speed
│   │   │   │           ├── gfpe
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfpe.pl
│   │   │   │           │   ├── mpfq_gfpe_common.h
│   │   │   │           │   └── perl
│   │   │   │           │       ├── elt.pm
│   │   │   │           │       ├── elt_ur.pm
│   │   │   │           │       ├── field.pm
│   │   │   │           │       ├── gfpe.pm
│   │   │   │           │       └── io.pm
│   │   │   │           ├── include
│   │   │   │           │   ├── mpfq
│   │   │   │           │   │   └── mpfq.h
│   │   │   │           │   └── timing.h
│   │   │   │           ├── perl-lib
│   │   │   │           │   └── Mpfq
│   │   │   │           │       ├── defaults
│   │   │   │           │       │   ├── flatdata.pm
│   │   │   │           │       │   ├── mpi_flat.pm
│   │   │   │           │       │   ├── polygcd.pm
│   │   │   │           │       │   ├── poly.pm
│   │   │   │           │       │   ├── pow.pm
│   │   │   │           │       │   ├── vec
│   │   │   │           │       │   │   ├── addsub.pm
│   │   │   │           │       │   │   ├── alloc.pm
│   │   │   │           │       │   │   ├── conv.pm
│   │   │   │           │       │   │   ├── flatdata.pm
│   │   │   │           │       │   │   ├── getset.pm
│   │   │   │           │       │   │   ├── io.pm
│   │   │   │           │       │   │   └── mul.pm
│   │   │   │           │       │   └── vec.pm
│   │   │   │           │       ├── defaults.pm
│   │   │   │           │       ├── engine
│   │   │   │           │       │   ├── conf.pm
│   │   │   │           │       │   ├── handler.pm
│   │   │   │           │       │   ├── maketext.pm
│   │   │   │           │       │   ├── oo.pm
│   │   │   │           │       │   ├── postprocess.pm
│   │   │   │           │       │   └── utils.pm
│   │   │   │           │       ├── gf2n
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── inversion.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   ├── linearops.pm
│   │   │   │           │       │   ├── mul.pm
│   │   │   │           │       │   ├── reduction.pm
│   │   │   │           │       │   ├── squaring.pm
│   │   │   │           │       │   ├── trivialities.pm
│   │   │   │           │       │   └── utils
│   │   │   │           │       │       └── poly.pm
│   │   │   │           │       ├── gf2n.pm
│   │   │   │           │       ├── gf2x
│   │   │   │           │       │   ├── details
│   │   │   │           │       │   │   ├── basecase.pm
│   │   │   │           │       │   │   ├── extra.pm
│   │   │   │           │       │   │   ├── kara.pm
│   │   │   │           │       │   │   ├── schoolbook.pm
│   │   │   │           │       │   │   └── sse2.pm
│   │   │   │           │       │   ├── utils
│   │   │   │           │       │   │   ├── align.pm
│   │   │   │           │       │   │   └── bitops.pm
│   │   │   │           │       │   └── wizard
│   │   │   │           │       │       ├── coldstore.pm
│   │   │   │           │       │       └── discard.pm
│   │   │   │           │       ├── gf2x.pm
│   │   │   │           │       ├── gfp
│   │   │   │           │       │   ├── elt.pm
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   └── mgy
│   │   │   │           │       │       ├── codec.pm
│   │   │   │           │       │       ├── elt.pm
│   │   │   │           │       │       ├── field.pm
│   │   │   │           │       │       └── io.pm
│   │   │   │           │       ├── gfpmgy.pm
│   │   │   │           │       └── gfp.pm
│   │   │   │           ├── scripts
│   │   │   │           │   ├── machine.sh
│   │   │   │           │   └── wordsize.sh
│   │   │   │           ├── simd
│   │   │   │           │   ├── abase.pl
│   │   │   │           │   ├── binary-dotprods-backends.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── io.pm
│   │   │   │           │   │   ├── p16.pm
│   │   │   │           │   │   ├── simd_char2.pm
│   │   │   │           │   │   ├── simd_dotprod.pm
│   │   │   │           │   │   ├── simd_flat.pm
│   │   │   │           │   │   ├── simd_gfp.pm
│   │   │   │           │   │   ├── simd_multiplex.pm
│   │   │   │           │   │   ├── simd_noflat.pm
│   │   │   │           │   │   ├── simd_p16.pm
│   │   │   │           │   │   ├── simd_u64k.pm
│   │   │   │           │   │   ├── simd_u64n.pm
│   │   │   │           │   │   └── trivialities.pm
│   │   │   │           │   ├── README
│   │   │   │           │   └── README.oo
│   │   │   │           └── test
│   │   │   │               ├── CMakeLists.txt
│   │   │   │               ├── mk_name_k.pl
│   │   │   │               ├── mpfq_test.c.meta
│   │   │   │               └── README
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST fonctions for randomness generation
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: RQC source folder
│   │       ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│   │       ├── ffi: Finite field interface folder
│   │       │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│   │       │   ├── ffi_elt.h: Interface for finite field elements
│   │       │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│   │       │   ├── ffi_field.h: Interface for finite fields
│   │       │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│   │       │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│   │       │   └── ffi_vec.h: Interface for vectors over finite fields 
│   │       ├── gabidulin.c: Implementation of gabidulin.h
│   │       ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── main_rqc.c: RQC KEM IND-CCA2 working example
│   │       ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── q_polynomial.c: Implementation of q_polynomial.h
│   │       ├── q_polynomial.h: Functions to manipulate q_polynomials
│   │       ├── rqc.c: Implementation of rqc.h
│   │       └── rqc.h: Functions of the RQC PKE IND-CPA scheme
│   └── rqc256: Implementation of RQC-256 (security level 5)
│       ├── configure: Configuration file for compilation
│       ├── doc: Technical documentation folder
│       │   ├── main_page.txt: Main page of the technical documentation
│       │   └── refs.bib: References for the technical documentation
│       ├── doxygen.conf: Doxygen configuration file for documentation
│       ├── lib: Third party libraries folder
│       │   ├── hash: Wrapper around SHA512 implementation 
│       │   │   ├── hash.c: Implementation of hash.h
│       │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│       │   ├── mpfq: MPFQ library source code
│       │   │   └── mpfq-1.1
│       │   │       ├── Copying
│       │   │       ├── doc
│       │   │       │   ├── api.xml
│       │   │       │   ├── design.xml
│       │   │       │   ├── doc.xml
│       │   │       │   ├── fieldimpl.xml
│       │   │       │   ├── install.xml
│       │   │       │   ├── intro.xml
│       │   │       │   ├── Makefile
│       │   │       │   ├── mpfqdoc.dtd
│       │   │       │   ├── parsemath.pl
│       │   │       │   ├── perl-lib
│       │   │       │   │   └── XML
│       │   │       │   │       └── Reprocess.pm
│       │   │       │   ├── README
│       │   │       │   ├── tuning.xml
│       │   │       │   └── xsl
│       │   │       │       ├── custom-fo.xsl
│       │   │       │       ├── custom-xhtml.xsl
│       │   │       │       ├── custom.xsl
│       │   │       │       ├── fo.xsl
│       │   │       │       ├── xhtml-nochunks.xsl
│       │   │       │       └── xhtml.xsl
│       │   │       └── src
│       │   │           ├── api.pl
│       │   │           ├── apps
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── curve2_251.c
│       │   │           │   ├── curve25519.c
│       │   │           │   ├── surf127eps.c
│       │   │           │   └── surf2_113.c
│       │   │           ├── benches
│       │   │           │   ├── bench.pl
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fieldop.c
│       │   │           │   └── mpfqbench.pl
│       │   │           ├── CMakeLists.txt
│       │   │           ├── CMakeMacros.txt
│       │   │           ├── fixmp
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fixmp.h.in
│       │   │           │   ├── perl
│       │   │           │   │   ├── gen_mp_longlong.pl
│       │   │           │   │   ├── gen_mp_test.pl
│       │   │           │   │   ├── gen_mp_x86_32.pl
│       │   │           │   │   └── gen_mp_x86_64.pl
│       │   │           │   └── README
│       │   │           ├── gf2n
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fields.data
│       │   │           │   ├── gen_gf2n.pl
│       │   │           │   ├── helper
│       │   │           │   │   ├── bitlinalg.c
│       │   │           │   │   ├── bitlinalg.h
│       │   │           │   │   ├── CMakeLists.txt
│       │   │           │   │   ├── helper.c
│       │   │           │   │   ├── wmat.c
│       │   │           │   │   └── wmat.h
│       │   │           │   ├── mpfq_gf2n_common.h
│       │   │           │   ├── perl
│       │   │           │   │   └── gf64.pm
│       │   │           │   └── tracer
│       │   │           │       ├── tracer.h.meta
│       │   │           │       └── tracer.pl
│       │   │           ├── gf2x
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── dump_poly.h
│       │   │           │   ├── tuning-summary.sh
│       │   │           │   ├── wizard.pl
│       │   │           │   └── wiztest.c
│       │   │           ├── gf7
│       │   │           │   ├── gen_gf7.pl
│       │   │           │   ├── gf7.pm
│       │   │           │   └── README
│       │   │           ├── gfp
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── gen_gfp.pl
│       │   │           │   ├── mpfq_gfp_common.h
│       │   │           │   ├── perl
│       │   │           │   │   ├── p127_1.pm
│       │   │           │   │   ├── p127_735.pm
│       │   │           │   │   └── p25519.pm
│       │   │           │   └── TODO_for_speed
│       │   │           ├── gfpe
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── gen_gfpe.pl
│       │   │           │   ├── mpfq_gfpe_common.h
│       │   │           │   └── perl
│       │   │           │       ├── elt.pm
│       │   │           │       ├── elt_ur.pm
│       │   │           │       ├── field.pm
│       │   │           │       ├── gfpe.pm
│       │   │           │       └── io.pm
│       │   │           ├── include
│       │   │           │   ├── mpfq
│       │   │           │   │   └── mpfq.h
│       │   │           │   └── timing.h
│       │   │           ├── perl-lib
│       │   │           │   └── Mpfq
│       │   │           │       ├── defaults
│       │   │           │       │   ├── flatdata.pm
│       │   │           │       │   ├── mpi_flat.pm
│       │   │           │       │   ├── polygcd.pm
│       │   │           │       │   ├── poly.pm
│       │   │           │       │   ├── pow.pm
│       │   │           │       │   ├── vec
│       │   │           │       │   │   ├── addsub.pm
│       │   │           │       │   │   ├── alloc.pm
│       │   │           │       │   │   ├── conv.pm
│       │   │           │       │   │   ├── flatdata.pm
│       │   │           │       │   │   ├── getset.pm
│       │   │           │       │   │   ├── io.pm
│       │   │           │       │   │   └── mul.pm
│       │   │           │       │   └── vec.pm
│       │   │           │       ├── defaults.pm
│       │   │           │       ├── engine
│       │   │           │       │   ├── conf.pm
│       │   │           │       │   ├── handler.pm
│       │   │           │       │   ├── maketext.pm
│       │   │           │       │   ├── oo.pm
│       │   │           │       │   ├── postprocess.pm
│       │   │           │       │   └── utils.pm
│       │   │           │       ├── gf2n
│       │   │           │       │   ├── field.pm
│       │   │           │       │   ├── inversion.pm
│       │   │           │       │   ├── io.pm
│       │   │           │       │   ├── linearops.pm
│       │   │           │       │   ├── mul.pm
│       │   │           │       │   ├── reduction.pm
│       │   │           │       │   ├── squaring.pm
│       │   │           │       │   ├── trivialities.pm
│       │   │           │       │   └── utils
│       │   │           │       │       └── poly.pm
│       │   │           │       ├── gf2n.pm
│       │   │           │       ├── gf2x
│       │   │           │       │   ├── details
│       │   │           │       │   │   ├── basecase.pm
│       │   │           │       │   │   ├── extra.pm
│       │   │           │       │   │   ├── kara.pm
│       │   │           │       │   │   ├── schoolbook.pm
│       │   │           │       │   │   └── sse2.pm
│       │   │           │       │   ├── utils
│       │   │           │       │   │   ├── align.pm
│       │   │           │       │   │   └── bitops.pm
│       │   │           │       │   └── wizard
│       │   │           │       │       ├── coldstore.pm
│       │   │           │       │       └── discard.pm
│       │   │           │       ├── gf2x.pm
│       │   │           │       ├── gfp
│       │   │           │       │   ├── elt.pm
│       │   │           │       │   ├── field.pm
│       │   │           │       │   ├── io.pm
│       │   │           │       │   └── mgy
│       │   │           │       │       ├── codec.pm
│       │   │           │       │       ├── elt.pm
│       │   │           │       │       ├── field.pm
│       │   │           │       │       └── io.pm
│       │   │           │       ├── gfpmgy.pm
│       │   │           │       └── gfp.pm
│       │   │           ├── scripts
│       │   │           │   ├── machine.sh
│       │   │           │   └── wordsize.sh
│       │   │           ├── simd
│       │   │           │   ├── abase.pl
│       │   │           │   ├── binary-dotprods-backends.h
│       │   │           │   ├── perl
│       │   │           │   │   ├── io.pm
│       │   │           │   │   ├── p16.pm
│       │   │           │   │   ├── simd_char2.pm
│       │   │           │   │   ├── simd_dotprod.pm
│       │   │           │   │   ├── simd_flat.pm
│       │   │           │   │   ├── simd_gfp.pm
│       │   │           │   │   ├── simd_multiplex.pm
│       │   │           │   │   ├── simd_noflat.pm
│       │   │           │   │   ├── simd_p16.pm
│       │   │           │   │   ├── simd_u64k.pm
│       │   │           │   │   ├── simd_u64n.pm
│       │   │           │   │   └── trivialities.pm
│       │   │           │   ├── README
│       │   │           │   └── README.oo
│       │   │           └── test
│       │   │               ├── CMakeLists.txt
│       │   │               ├── mk_name_k.pl
│       │   │               ├── mpfq_test.c.meta
│       │   │               └── README
│       │   └── rng: NIST rng files
│       │       ├── rng.c: Implementation of rng.h
│       │       └── rng.h: NIST fonctions for randomness generation
│       ├── Makefile: Makefile to compile the provided code
│       └── src: RQC source folder
│           ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│           ├── ffi: Finite field interface folder
│           │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│           │   ├── ffi_elt.h: Interface for finite field elements
│           │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│           │   ├── ffi_field.h: Interface for finite fields
│           │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│           │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│           │   └── ffi_vec.h: Interface for vectors over finite fields 
│           ├── gabidulin.c: Implementation of gabidulin.h
│           ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│           ├── kem.c: Implementation of api.h
│           ├── main_kat.c: NIST KAT generator
│           ├── main_rqc.c: RQC KEM IND-CCA2 working example
│           ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│           ├── parsing.c: Implementation of parsing.h
│           ├── parsing.h: Functions to parse public key, secret key and ciphertext
│           ├── q_polynomial.c: Implementation of q_polynomial.h
│           ├── q_polynomial.h: Functions to manipulate q_polynomials
│           ├── rqc.c: Implementation of rqc.h
│           └── rqc.h: Functions of the RQC PKE IND-CPA scheme
├── README.md: This file
├── Reference_Implementation: RQC reference implementation
│   ├── README: Readme file with compilation instructions
│   ├── rqc128: Implementation of RQC-128 (security level 1)
│   │   ├── configure: Configuration file for compilation
│   │   ├── doc: Technical documentation folder
│   │   │   ├── main_page.txt: Main page of the technical documentation
│   │   │   └── refs.bib: References for the technical documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation 
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│   │   │   ├── mpfq: MPFQ library source code
│   │   │   │   └── mpfq-1.1
│   │   │   │       ├── Copying
│   │   │   │       ├── doc
│   │   │   │       │   ├── api.xml
│   │   │   │       │   ├── design.xml
│   │   │   │       │   ├── doc.xml
│   │   │   │       │   ├── fieldimpl.xml
│   │   │   │       │   ├── install.xml
│   │   │   │       │   ├── intro.xml
│   │   │   │       │   ├── Makefile
│   │   │   │       │   ├── mpfqdoc.dtd
│   │   │   │       │   ├── parsemath.pl
│   │   │   │       │   ├── perl-lib
│   │   │   │       │   │   └── XML
│   │   │   │       │   │       └── Reprocess.pm
│   │   │   │       │   ├── README
│   │   │   │       │   ├── tuning.xml
│   │   │   │       │   └── xsl
│   │   │   │       │       ├── custom-fo.xsl
│   │   │   │       │       ├── custom-xhtml.xsl
│   │   │   │       │       ├── custom.xsl
│   │   │   │       │       ├── fo.xsl
│   │   │   │       │       ├── xhtml-nochunks.xsl
│   │   │   │       │       └── xhtml.xsl
│   │   │   │       └── src
│   │   │   │           ├── api.pl
│   │   │   │           ├── apps
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── curve2_251.c
│   │   │   │           │   ├── curve25519.c
│   │   │   │           │   ├── surf127eps.c
│   │   │   │           │   └── surf2_113.c
│   │   │   │           ├── benches
│   │   │   │           │   ├── bench.pl
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fieldop.c
│   │   │   │           │   └── mpfqbench.pl
│   │   │   │           ├── CMakeLists.txt
│   │   │   │           ├── CMakeMacros.txt
│   │   │   │           ├── fixmp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fixmp.h.in
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── gen_mp_longlong.pl
│   │   │   │           │   │   ├── gen_mp_test.pl
│   │   │   │           │   │   ├── gen_mp_x86_32.pl
│   │   │   │           │   │   └── gen_mp_x86_64.pl
│   │   │   │           │   └── README
│   │   │   │           ├── gf2n
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fields.data
│   │   │   │           │   ├── gen_gf2n.pl
│   │   │   │           │   ├── helper
│   │   │   │           │   │   ├── bitlinalg.c
│   │   │   │           │   │   ├── bitlinalg.h
│   │   │   │           │   │   ├── CMakeLists.txt
│   │   │   │           │   │   ├── helper.c
│   │   │   │           │   │   ├── wmat.c
│   │   │   │           │   │   └── wmat.h
│   │   │   │           │   ├── mpfq_gf2n_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   └── gf64.pm
│   │   │   │           │   └── tracer
│   │   │   │           │       ├── tracer.h.meta
│   │   │   │           │       └── tracer.pl
│   │   │   │           ├── gf2x
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── dump_poly.h
│   │   │   │           │   ├── tuning-summary.sh
│   │   │   │           │   ├── wizard.pl
│   │   │   │           │   └── wiztest.c
│   │   │   │           ├── gf7
│   │   │   │           │   ├── gen_gf7.pl
│   │   │   │           │   ├── gf7.pm
│   │   │   │           │   └── README
│   │   │   │           ├── gfp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfp.pl
│   │   │   │           │   ├── mpfq_gfp_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── p127_1.pm
│   │   │   │           │   │   ├── p127_735.pm
│   │   │   │           │   │   └── p25519.pm
│   │   │   │           │   └── TODO_for_speed
│   │   │   │           ├── gfpe
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfpe.pl
│   │   │   │           │   ├── mpfq_gfpe_common.h
│   │   │   │           │   └── perl
│   │   │   │           │       ├── elt.pm
│   │   │   │           │       ├── elt_ur.pm
│   │   │   │           │       ├── field.pm
│   │   │   │           │       ├── gfpe.pm
│   │   │   │           │       └── io.pm
│   │   │   │           ├── include
│   │   │   │           │   ├── mpfq
│   │   │   │           │   │   └── mpfq.h
│   │   │   │           │   └── timing.h
│   │   │   │           ├── perl-lib
│   │   │   │           │   └── Mpfq
│   │   │   │           │       ├── defaults
│   │   │   │           │       │   ├── flatdata.pm
│   │   │   │           │       │   ├── mpi_flat.pm
│   │   │   │           │       │   ├── polygcd.pm
│   │   │   │           │       │   ├── poly.pm
│   │   │   │           │       │   ├── pow.pm
│   │   │   │           │       │   ├── vec
│   │   │   │           │       │   │   ├── addsub.pm
│   │   │   │           │       │   │   ├── alloc.pm
│   │   │   │           │       │   │   ├── conv.pm
│   │   │   │           │       │   │   ├── flatdata.pm
│   │   │   │           │       │   │   ├── getset.pm
│   │   │   │           │       │   │   ├── io.pm
│   │   │   │           │       │   │   └── mul.pm
│   │   │   │           │       │   └── vec.pm
│   │   │   │           │       ├── defaults.pm
│   │   │   │           │       ├── engine
│   │   │   │           │       │   ├── conf.pm
│   │   │   │           │       │   ├── handler.pm
│   │   │   │           │       │   ├── maketext.pm
│   │   │   │           │       │   ├── oo.pm
│   │   │   │           │       │   ├── postprocess.pm
│   │   │   │           │       │   └── utils.pm
│   │   │   │           │       ├── gf2n
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── inversion.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   ├── linearops.pm
│   │   │   │           │       │   ├── mul.pm
│   │   │   │           │       │   ├── reduction.pm
│   │   │   │           │       │   ├── squaring.pm
│   │   │   │           │       │   ├── trivialities.pm
│   │   │   │           │       │   └── utils
│   │   │   │           │       │       └── poly.pm
│   │   │   │           │       ├── gf2n.pm
│   │   │   │           │       ├── gf2x
│   │   │   │           │       │   ├── details
│   │   │   │           │       │   │   ├── basecase.pm
│   │   │   │           │       │   │   ├── extra.pm
│   │   │   │           │       │   │   ├── kara.pm
│   │   │   │           │       │   │   ├── schoolbook.pm
│   │   │   │           │       │   │   └── sse2.pm
│   │   │   │           │       │   ├── utils
│   │   │   │           │       │   │   ├── align.pm
│   │   │   │           │       │   │   └── bitops.pm
│   │   │   │           │       │   └── wizard
│   │   │   │           │       │       ├── coldstore.pm
│   │   │   │           │       │       └── discard.pm
│   │   │   │           │       ├── gf2x.pm
│   │   │   │           │       ├── gfp
│   │   │   │           │       │   ├── elt.pm
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   └── mgy
│   │   │   │           │       │       ├── codec.pm
│   │   │   │           │       │       ├── elt.pm
│   │   │   │           │       │       ├── field.pm
│   │   │   │           │       │       └── io.pm
│   │   │   │           │       ├── gfpmgy.pm
│   │   │   │           │       └── gfp.pm
│   │   │   │           ├── scripts
│   │   │   │           │   ├── machine.sh
│   │   │   │           │   └── wordsize.sh
│   │   │   │           ├── simd
│   │   │   │           │   ├── abase.pl
│   │   │   │           │   ├── binary-dotprods-backends.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── io.pm
│   │   │   │           │   │   ├── p16.pm
│   │   │   │           │   │   ├── simd_char2.pm
│   │   │   │           │   │   ├── simd_dotprod.pm
│   │   │   │           │   │   ├── simd_flat.pm
│   │   │   │           │   │   ├── simd_gfp.pm
│   │   │   │           │   │   ├── simd_multiplex.pm
│   │   │   │           │   │   ├── simd_noflat.pm
│   │   │   │           │   │   ├── simd_p16.pm
│   │   │   │           │   │   ├── simd_u64k.pm
│   │   │   │           │   │   ├── simd_u64n.pm
│   │   │   │           │   │   └── trivialities.pm
│   │   │   │           │   ├── README
│   │   │   │           │   └── README.oo
│   │   │   │           └── test
│   │   │   │               ├── CMakeLists.txt
│   │   │   │               ├── mk_name_k.pl
│   │   │   │               ├── mpfq_test.c.meta
│   │   │   │               └── README
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST fonctions for randomness generation
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: RQC source folder
│   │       ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│   │       ├── ffi: Finite field interface folder
│   │       │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│   │       │   ├── ffi_elt.h: Interface for finite field elements
│   │       │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│   │       │   ├── ffi_field.h: Interface for finite fields
│   │       │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│   │       │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│   │       │   └── ffi_vec.h: Interface for vectors over finite fields 
│   │       ├── gabidulin.c: Implementation of gabidulin.h
│   │       ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── main_rqc.c: RQC KEM IND-CCA2 working example
│   │       ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── q_polynomial.c: Implementation of q_polynomial.h
│   │       ├── q_polynomial.h: Functions to manipulate q_polynomials
│   │       ├── rqc.c: Implementation of rqc.h
│   │       └── rqc.h: Functions of the RQC PKE IND-CPA scheme
│   ├── rqc192: Implementation of RQC-192 (security level 3)
│   │   ├── configure: Configuration file for compilation
│   │   ├── doc: Technical documentation folder
│   │   │   ├── main_page.txt: Main page of the technical documentation
│   │   │   └── refs.bib: References for the technical documentation
│   │   ├── doxygen.conf: Doxygen configuration file for documentation
│   │   ├── lib: Third party libraries folder
│   │   │   ├── hash: Wrapper around SHA512 implementation 
│   │   │   │   ├── hash.c: Implementation of hash.h
│   │   │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│   │   │   ├── mpfq: MPFQ library source code
│   │   │   │   └── mpfq-1.1
│   │   │   │       ├── Copying
│   │   │   │       ├── doc
│   │   │   │       │   ├── api.xml
│   │   │   │       │   ├── design.xml
│   │   │   │       │   ├── doc.xml
│   │   │   │       │   ├── fieldimpl.xml
│   │   │   │       │   ├── install.xml
│   │   │   │       │   ├── intro.xml
│   │   │   │       │   ├── Makefile
│   │   │   │       │   ├── mpfqdoc.dtd
│   │   │   │       │   ├── parsemath.pl
│   │   │   │       │   ├── perl-lib
│   │   │   │       │   │   └── XML
│   │   │   │       │   │       └── Reprocess.pm
│   │   │   │       │   ├── README
│   │   │   │       │   ├── tuning.xml
│   │   │   │       │   └── xsl
│   │   │   │       │       ├── custom-fo.xsl
│   │   │   │       │       ├── custom-xhtml.xsl
│   │   │   │       │       ├── custom.xsl
│   │   │   │       │       ├── fo.xsl
│   │   │   │       │       ├── xhtml-nochunks.xsl
│   │   │   │       │       └── xhtml.xsl
│   │   │   │       └── src
│   │   │   │           ├── api.pl
│   │   │   │           ├── apps
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── curve2_251.c
│   │   │   │           │   ├── curve25519.c
│   │   │   │           │   ├── surf127eps.c
│   │   │   │           │   └── surf2_113.c
│   │   │   │           ├── benches
│   │   │   │           │   ├── bench.pl
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fieldop.c
│   │   │   │           │   └── mpfqbench.pl
│   │   │   │           ├── CMakeLists.txt
│   │   │   │           ├── CMakeMacros.txt
│   │   │   │           ├── fixmp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fixmp.h.in
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── gen_mp_longlong.pl
│   │   │   │           │   │   ├── gen_mp_test.pl
│   │   │   │           │   │   ├── gen_mp_x86_32.pl
│   │   │   │           │   │   └── gen_mp_x86_64.pl
│   │   │   │           │   └── README
│   │   │   │           ├── gf2n
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── fields.data
│   │   │   │           │   ├── gen_gf2n.pl
│   │   │   │           │   ├── helper
│   │   │   │           │   │   ├── bitlinalg.c
│   │   │   │           │   │   ├── bitlinalg.h
│   │   │   │           │   │   ├── CMakeLists.txt
│   │   │   │           │   │   ├── helper.c
│   │   │   │           │   │   ├── wmat.c
│   │   │   │           │   │   └── wmat.h
│   │   │   │           │   ├── mpfq_gf2n_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   └── gf64.pm
│   │   │   │           │   └── tracer
│   │   │   │           │       ├── tracer.h.meta
│   │   │   │           │       └── tracer.pl
│   │   │   │           ├── gf2x
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── dump_poly.h
│   │   │   │           │   ├── tuning-summary.sh
│   │   │   │           │   ├── wizard.pl
│   │   │   │           │   └── wiztest.c
│   │   │   │           ├── gf7
│   │   │   │           │   ├── gen_gf7.pl
│   │   │   │           │   ├── gf7.pm
│   │   │   │           │   └── README
│   │   │   │           ├── gfp
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfp.pl
│   │   │   │           │   ├── mpfq_gfp_common.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── p127_1.pm
│   │   │   │           │   │   ├── p127_735.pm
│   │   │   │           │   │   └── p25519.pm
│   │   │   │           │   └── TODO_for_speed
│   │   │   │           ├── gfpe
│   │   │   │           │   ├── CMakeLists.txt
│   │   │   │           │   ├── gen_gfpe.pl
│   │   │   │           │   ├── mpfq_gfpe_common.h
│   │   │   │           │   └── perl
│   │   │   │           │       ├── elt.pm
│   │   │   │           │       ├── elt_ur.pm
│   │   │   │           │       ├── field.pm
│   │   │   │           │       ├── gfpe.pm
│   │   │   │           │       └── io.pm
│   │   │   │           ├── include
│   │   │   │           │   ├── mpfq
│   │   │   │           │   │   └── mpfq.h
│   │   │   │           │   └── timing.h
│   │   │   │           ├── perl-lib
│   │   │   │           │   └── Mpfq
│   │   │   │           │       ├── defaults
│   │   │   │           │       │   ├── flatdata.pm
│   │   │   │           │       │   ├── mpi_flat.pm
│   │   │   │           │       │   ├── polygcd.pm
│   │   │   │           │       │   ├── poly.pm
│   │   │   │           │       │   ├── pow.pm
│   │   │   │           │       │   ├── vec
│   │   │   │           │       │   │   ├── addsub.pm
│   │   │   │           │       │   │   ├── alloc.pm
│   │   │   │           │       │   │   ├── conv.pm
│   │   │   │           │       │   │   ├── flatdata.pm
│   │   │   │           │       │   │   ├── getset.pm
│   │   │   │           │       │   │   ├── io.pm
│   │   │   │           │       │   │   └── mul.pm
│   │   │   │           │       │   └── vec.pm
│   │   │   │           │       ├── defaults.pm
│   │   │   │           │       ├── engine
│   │   │   │           │       │   ├── conf.pm
│   │   │   │           │       │   ├── handler.pm
│   │   │   │           │       │   ├── maketext.pm
│   │   │   │           │       │   ├── oo.pm
│   │   │   │           │       │   ├── postprocess.pm
│   │   │   │           │       │   └── utils.pm
│   │   │   │           │       ├── gf2n
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── inversion.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   ├── linearops.pm
│   │   │   │           │       │   ├── mul.pm
│   │   │   │           │       │   ├── reduction.pm
│   │   │   │           │       │   ├── squaring.pm
│   │   │   │           │       │   ├── trivialities.pm
│   │   │   │           │       │   └── utils
│   │   │   │           │       │       └── poly.pm
│   │   │   │           │       ├── gf2n.pm
│   │   │   │           │       ├── gf2x
│   │   │   │           │       │   ├── details
│   │   │   │           │       │   │   ├── basecase.pm
│   │   │   │           │       │   │   ├── extra.pm
│   │   │   │           │       │   │   ├── kara.pm
│   │   │   │           │       │   │   ├── schoolbook.pm
│   │   │   │           │       │   │   └── sse2.pm
│   │   │   │           │       │   ├── utils
│   │   │   │           │       │   │   ├── align.pm
│   │   │   │           │       │   │   └── bitops.pm
│   │   │   │           │       │   └── wizard
│   │   │   │           │       │       ├── coldstore.pm
│   │   │   │           │       │       └── discard.pm
│   │   │   │           │       ├── gf2x.pm
│   │   │   │           │       ├── gfp
│   │   │   │           │       │   ├── elt.pm
│   │   │   │           │       │   ├── field.pm
│   │   │   │           │       │   ├── io.pm
│   │   │   │           │       │   └── mgy
│   │   │   │           │       │       ├── codec.pm
│   │   │   │           │       │       ├── elt.pm
│   │   │   │           │       │       ├── field.pm
│   │   │   │           │       │       └── io.pm
│   │   │   │           │       ├── gfpmgy.pm
│   │   │   │           │       └── gfp.pm
│   │   │   │           ├── scripts
│   │   │   │           │   ├── machine.sh
│   │   │   │           │   └── wordsize.sh
│   │   │   │           ├── simd
│   │   │   │           │   ├── abase.pl
│   │   │   │           │   ├── binary-dotprods-backends.h
│   │   │   │           │   ├── perl
│   │   │   │           │   │   ├── io.pm
│   │   │   │           │   │   ├── p16.pm
│   │   │   │           │   │   ├── simd_char2.pm
│   │   │   │           │   │   ├── simd_dotprod.pm
│   │   │   │           │   │   ├── simd_flat.pm
│   │   │   │           │   │   ├── simd_gfp.pm
│   │   │   │           │   │   ├── simd_multiplex.pm
│   │   │   │           │   │   ├── simd_noflat.pm
│   │   │   │           │   │   ├── simd_p16.pm
│   │   │   │           │   │   ├── simd_u64k.pm
│   │   │   │           │   │   ├── simd_u64n.pm
│   │   │   │           │   │   └── trivialities.pm
│   │   │   │           │   ├── README
│   │   │   │           │   └── README.oo
│   │   │   │           └── test
│   │   │   │               ├── CMakeLists.txt
│   │   │   │               ├── mk_name_k.pl
│   │   │   │               ├── mpfq_test.c.meta
│   │   │   │               └── README
│   │   │   └── rng: NIST rng files
│   │   │       ├── rng.c: Implementation of rng.h
│   │   │       └── rng.h: NIST fonctions for randomness generation
│   │   ├── Makefile: Makefile to compile the provided code
│   │   └── src: RQC source folder
│   │       ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│   │       ├── ffi: Finite field interface folder
│   │       │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│   │       │   ├── ffi_elt.h: Interface for finite field elements
│   │       │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│   │       │   ├── ffi_field.h: Interface for finite fields
│   │       │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│   │       │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│   │       │   └── ffi_vec.h: Interface for vectors over finite fields 
│   │       ├── gabidulin.c: Implementation of gabidulin.h
│   │       ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│   │       ├── kem.c: Implementation of api.h
│   │       ├── main_kat.c: NIST KAT generator
│   │       ├── main_rqc.c: RQC KEM IND-CCA2 working example
│   │       ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│   │       ├── parsing.c: Implementation of parsing.h
│   │       ├── parsing.h: Functions to parse public key, secret key and ciphertext
│   │       ├── q_polynomial.c: Implementation of q_polynomial.h
│   │       ├── q_polynomial.h: Functions to manipulate q_polynomials
│   │       ├── rqc.c: Implementation of rqc.h
│   │       └── rqc.h: Functions of the RQC PKE IND-CPA scheme
│   └── rqc256: Implementation of RQC-256 (security level 5)
│       ├── configure: Configuration file for compilation
│       ├── doc: Technical documentation folder
│       │   ├── main_page.txt: Main page of the technical documentation
│       │   └── refs.bib: References for the technical documentation
│       ├── doxygen.conf: Doxygen configuration file for documentation
│       ├── lib: Third party libraries folder
│       │   ├── hash: Wrapper around SHA512 implementation 
│       │   │   ├── hash.c: Implementation of hash.h
│       │   │   └── hash.h: Wrapper around OpenSSL SHA512 implementation
│       │   ├── mpfq: MPFQ library source code
│       │   │   └── mpfq-1.1
│       │   │       ├── Copying
│       │   │       ├── doc
│       │   │       │   ├── api.xml
│       │   │       │   ├── design.xml
│       │   │       │   ├── doc.xml
│       │   │       │   ├── fieldimpl.xml
│       │   │       │   ├── install.xml
│       │   │       │   ├── intro.xml
│       │   │       │   ├── Makefile
│       │   │       │   ├── mpfqdoc.dtd
│       │   │       │   ├── parsemath.pl
│       │   │       │   ├── perl-lib
│       │   │       │   │   └── XML
│       │   │       │   │       └── Reprocess.pm
│       │   │       │   ├── README
│       │   │       │   ├── tuning.xml
│       │   │       │   └── xsl
│       │   │       │       ├── custom-fo.xsl
│       │   │       │       ├── custom-xhtml.xsl
│       │   │       │       ├── custom.xsl
│       │   │       │       ├── fo.xsl
│       │   │       │       ├── xhtml-nochunks.xsl
│       │   │       │       └── xhtml.xsl
│       │   │       └── src
│       │   │           ├── api.pl
│       │   │           ├── apps
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── curve2_251.c
│       │   │           │   ├── curve25519.c
│       │   │           │   ├── surf127eps.c
│       │   │           │   └── surf2_113.c
│       │   │           ├── benches
│       │   │           │   ├── bench.pl
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fieldop.c
│       │   │           │   └── mpfqbench.pl
│       │   │           ├── CMakeLists.txt
│       │   │           ├── CMakeMacros.txt
│       │   │           ├── fixmp
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fixmp.h.in
│       │   │           │   ├── perl
│       │   │           │   │   ├── gen_mp_longlong.pl
│       │   │           │   │   ├── gen_mp_test.pl
│       │   │           │   │   ├── gen_mp_x86_32.pl
│       │   │           │   │   └── gen_mp_x86_64.pl
│       │   │           │   └── README
│       │   │           ├── gf2n
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── fields.data
│       │   │           │   ├── gen_gf2n.pl
│       │   │           │   ├── helper
│       │   │           │   │   ├── bitlinalg.c
│       │   │           │   │   ├── bitlinalg.h
│       │   │           │   │   ├── CMakeLists.txt
│       │   │           │   │   ├── helper.c
│       │   │           │   │   ├── wmat.c
│       │   │           │   │   └── wmat.h
│       │   │           │   ├── mpfq_gf2n_common.h
│       │   │           │   ├── perl
│       │   │           │   │   └── gf64.pm
│       │   │           │   └── tracer
│       │   │           │       ├── tracer.h.meta
│       │   │           │       └── tracer.pl
│       │   │           ├── gf2x
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── dump_poly.h
│       │   │           │   ├── tuning-summary.sh
│       │   │           │   ├── wizard.pl
│       │   │           │   └── wiztest.c
│       │   │           ├── gf7
│       │   │           │   ├── gen_gf7.pl
│       │   │           │   ├── gf7.pm
│       │   │           │   └── README
│       │   │           ├── gfp
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── gen_gfp.pl
│       │   │           │   ├── mpfq_gfp_common.h
│       │   │           │   ├── perl
│       │   │           │   │   ├── p127_1.pm
│       │   │           │   │   ├── p127_735.pm
│       │   │           │   │   └── p25519.pm
│       │   │           │   └── TODO_for_speed
│       │   │           ├── gfpe
│       │   │           │   ├── CMakeLists.txt
│       │   │           │   ├── gen_gfpe.pl
│       │   │           │   ├── mpfq_gfpe_common.h
│       │   │           │   └── perl
│       │   │           │       ├── elt.pm
│       │   │           │       ├── elt_ur.pm
│       │   │           │       ├── field.pm
│       │   │           │       ├── gfpe.pm
│       │   │           │       └── io.pm
│       │   │           ├── include
│       │   │           │   ├── mpfq
│       │   │           │   │   └── mpfq.h
│       │   │           │   └── timing.h
│       │   │           ├── perl-lib
│       │   │           │   └── Mpfq
│       │   │           │       ├── defaults
│       │   │           │       │   ├── flatdata.pm
│       │   │           │       │   ├── mpi_flat.pm
│       │   │           │       │   ├── polygcd.pm
│       │   │           │       │   ├── poly.pm
│       │   │           │       │   ├── pow.pm
│       │   │           │       │   ├── vec
│       │   │           │       │   │   ├── addsub.pm
│       │   │           │       │   │   ├── alloc.pm
│       │   │           │       │   │   ├── conv.pm
│       │   │           │       │   │   ├── flatdata.pm
│       │   │           │       │   │   ├── getset.pm
│       │   │           │       │   │   ├── io.pm
│       │   │           │       │   │   └── mul.pm
│       │   │           │       │   └── vec.pm
│       │   │           │       ├── defaults.pm
│       │   │           │       ├── engine
│       │   │           │       │   ├── conf.pm
│       │   │           │       │   ├── handler.pm
│       │   │           │       │   ├── maketext.pm
│       │   │           │       │   ├── oo.pm
│       │   │           │       │   ├── postprocess.pm
│       │   │           │       │   └── utils.pm
│       │   │           │       ├── gf2n
│       │   │           │       │   ├── field.pm
│       │   │           │       │   ├── inversion.pm
│       │   │           │       │   ├── io.pm
│       │   │           │       │   ├── linearops.pm
│       │   │           │       │   ├── mul.pm
│       │   │           │       │   ├── reduction.pm
│       │   │           │       │   ├── squaring.pm
│       │   │           │       │   ├── trivialities.pm
│       │   │           │       │   └── utils
│       │   │           │       │       └── poly.pm
│       │   │           │       ├── gf2n.pm
│       │   │           │       ├── gf2x
│       │   │           │       │   ├── details
│       │   │           │       │   │   ├── basecase.pm
│       │   │           │       │   │   ├── extra.pm
│       │   │           │       │   │   ├── kara.pm
│       │   │           │       │   │   ├── schoolbook.pm
│       │   │           │       │   │   └── sse2.pm
│       │   │           │       │   ├── utils
│       │   │           │       │   │   ├── align.pm
│       │   │           │       │   │   └── bitops.pm
│       │   │           │       │   └── wizard
│       │   │           │       │       ├── coldstore.pm
│       │   │           │       │       └── discard.pm
│       │   │           │       ├── gf2x.pm
│       │   │           │       ├── gfp
│       │   │           │       │   ├── elt.pm
│       │   │           │       │   ├── field.pm
│       │   │           │       │   ├── io.pm
│       │   │           │       │   └── mgy
│       │   │           │       │       ├── codec.pm
│       │   │           │       │       ├── elt.pm
│       │   │           │       │       ├── field.pm
│       │   │           │       │       └── io.pm
│       │   │           │       ├── gfpmgy.pm
│       │   │           │       └── gfp.pm
│       │   │           ├── scripts
│       │   │           │   ├── machine.sh
│       │   │           │   └── wordsize.sh
│       │   │           ├── simd
│       │   │           │   ├── abase.pl
│       │   │           │   ├── binary-dotprods-backends.h
│       │   │           │   ├── perl
│       │   │           │   │   ├── io.pm
│       │   │           │   │   ├── p16.pm
│       │   │           │   │   ├── simd_char2.pm
│       │   │           │   │   ├── simd_dotprod.pm
│       │   │           │   │   ├── simd_flat.pm
│       │   │           │   │   ├── simd_gfp.pm
│       │   │           │   │   ├── simd_multiplex.pm
│       │   │           │   │   ├── simd_noflat.pm
│       │   │           │   │   ├── simd_p16.pm
│       │   │           │   │   ├── simd_u64k.pm
│       │   │           │   │   ├── simd_u64n.pm
│       │   │           │   │   └── trivialities.pm
│       │   │           │   ├── README
│       │   │           │   └── README.oo
│       │   │           └── test
│       │   │               ├── CMakeLists.txt
│       │   │               ├── mk_name_k.pl
│       │   │               ├── mpfq_test.c.meta
│       │   │               └── README
│       │   └── rng: NIST rng files
│       │       ├── rng.c: Implementation of rng.h
│       │       └── rng.h: NIST fonctions for randomness generation
│       ├── Makefile: Makefile to compile the provided code
│       └── src: RQC source folder
│           ├── api.h: API file for the RQC KEM IND-CCA2 scheme
│           ├── ffi: Finite field interface folder
│           │   ├── ffi_elt.c: Implementation of ffi_elt.h using the MPFQ library
│           │   ├── ffi_elt.h: Interface for finite field elements
│           │   ├── ffi_field.c: Implementation of ffi_field.h using the MPFQ library
│           │   ├── ffi_field.h: Interface for finite fields
│           │   ├── ffi.h: Some define and typedef easing the use of the MPFQ library
│           │   ├── ffi_vec.c: Implementation of ffi_vec.h using the MPFQ library
│           │   └── ffi_vec.h: Interface for vectors over finite fields 
│           ├── gabidulin.c: Implementation of gabidulin.h
│           ├── gabidulin.h: Functions to encode and decode messages using Gabidulin codes
│           ├── kem.c: Implementation of api.h
│           ├── main_kat.c: NIST KAT generator
│           ├── main_rqc.c: RQC KEM IND-CCA2 working example
│           ├── parameters.h: Parameters of the RQC KEM IND-CCA2 scheme
│           ├── parsing.c: Implementation of parsing.h
│           ├── parsing.h: Functions to parse public key, secret key and ciphertext
│           ├── q_polynomial.c: Implementation of q_polynomial.h
│           ├── q_polynomial.h: Functions to manipulate q_polynomials
│           ├── rqc.c: Implementation of rqc.h
│           └── rqc.h: Functions of the RQC PKE IND-CPA scheme
└── Supporting_Documentation: 
    └── RQC_Submission.pdf: Complete specification for our proposal

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

