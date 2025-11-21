To compile:
  - Go into the desired directory (Optimized_Implementation or Reference_Implementation)
  - Type 
      make
    This *should* compile everything, but on some systems this does not descend
    into the Lib directory and auto-compile there. So you might need to first
    'cd' into Lib and then type 'make'. 

We provide four algorithms (at different security strengths)
  - EncCPA    A CPA secure public key encryption scheme for short messages
  - EncCCA    A CCA secure public key encryption scheme for short messages
  - EncapCPA  A CPA secure key encapsulation scheme.
  - EncapCCA  A CCA secure key encapsulation scheme.

To make the KAT files descend into the subdirectory NIST and type
    make
The KAT files are then put in the subdirectory KAT-Test which can
then be compared to the directory KAT in the top level directory.




LIST OF FILES AND DESCRIPTIONS
------------------------------
.:
README.txt                                - This file
KAT                                       - KAT Directory
Optimized_Implementation                  - Optimized Implementation directory
Reference_Implementation                  - Reference Implementation directory
Supporting_Documentation                  - Various additional files


./KAT:                                    - Note name changes from NIST spec, as names conflict 
                                            we follow what NIST asked us to do via email
lima_2p_1024_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_2p_1024_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_2p_1024_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_2p_1024_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_2p_2048_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_2p_2048_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_2p_2048_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_2p_2048_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1018_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1018_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1018_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1018_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1306_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1306_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1306_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1306_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1822_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1822_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_1822_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_1822_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_2062_EncapCCA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_2062_EncapCPA-KAT.txt             - KAT data for specified parameter set and algorithm
lima_sp_2062_EncCCA-KAT.txt               - KAT data for specified parameter set and algorithm
lima_sp_2062_EncCPA-KAT.txt               - KAT data for specified parameter set and algorithm
XOF-KAT.txt                               - KAT data to test the XOF output in various situations
FFT-KAT.txt                               - KAT data to test the FFT routines



./Supporting_Documentation:
statement-submitter-nigel.pdf                  - General submission statement from Nigel Smart
statement-submitter-kenny.pdf                  - General submission statement from Kenny Paterson
statement-submitter-martin.pdf                 - General submission statement from Martin Albrecht
statement-submitter-emmanuela.pdf              - General submission statement from Emmanuela Orsini
statement-submitter-yehuda.pdf                 - General submission statement from Yehuda Lindell
statement-submitter-guy.pdf                    - General submission statement from Guy Peer
statement-submitter-valery.pdf                 - General submission statement from Valery Oscheter
statement-reference-implementation-Guy.pdf     - Statement from Guy Peer re the Code
statement-reference-implementation-Nigel.pdf   - Statement from Nigel Smart re the Code
statement-reference-implementation-Valery.pdf  - Statement from Valery Oscheter re the Code
Submission.pdf                                 - The detailed technical submission



./Reference_Implementation:
Lib                                       - Directory specifying the LIMA code
NIST                                      - Directory containing various subdirectories required by NIST for testing
Makefile                                  - Makefiel
README.txt                                - README file
Test-SubRoutines.c                        - Test all subroutines

./Reference_Implementation/Lib:
fft.c                                     - FFT algorithms (naive method)
fft.h                                     - FFT API
lima.c                                    - Main core routines
lima.h                                    - Main internal API
LimaAPI.c                                 - Routines for external API
LimaAPI.h                                 - External API
Makefile                                  - Makefile
modp.c                                    - Modular arithmetic routines (naive method)
modp.h                                    - Modular arithmetic API
xof.c                                     - XOF implementation (calling Keccak code)
xof.h                                     - XOF API

./Reference_Implementation/NIST:
EncCCA                                    - Directory with NIST API for CCA Public Key Encryption
EncapCPA                                  - Directory with NIST API for CPA Key Encapsulation
EncapCCA                                  - Directory with NIST API for CCA Key Encapsulation
EncCPA                                    - Directory with NIST API for CPA Public Key Encryption
KAT-Test                                  - Empty directory to take results of KAT tests
Makefile                                  - Makefile to run tests to produce all KAT files

./Reference_Implementation/EncapCCA:
api.h                                     - Required NIST API
kem.c                                     - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_kem.c                           - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Reference_Implementation/EncapCPA:
api.h                                     - Required NIST API
kem.c                                     - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_kem.c                           - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Reference_Implementation/EncCCA:
api.h                                     - Required NIST API
encrypt.c                                 - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_encrypt.c                       - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Reference_Implementation/EncCPA:
api.h                                     - Required NIST API
encrypt.c                                 - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_encrypt.c                       - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file




./Optimized_Implementation/NIST:
EncCCA                                    - Directory with NIST API for CCA Public Key Encryption
EncapCPA                                  - Directory with NIST API for CPA Key Encapsulation
EncapCCA                                  - Directory with NIST API for CCA Key Encapsulation
EncCPA                                    - Directory with NIST API for CPA Public Key Encryption
KAT-Test                                  - Empty directory to take results of KAT tests
Makefile                                  - Makefile to run tests to produce all KAT files

./Optimized_Implementation/EncapCCA:
api.h                                     - Required NIST API
kem.c                                     - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_kem.c                           - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Optimized_Implementation/EncapCPA:
api.h                                     - Required NIST API
kem.c                                     - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_kem.c                           - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Optimized_Implementation/EncCCA:
api.h                                     - Required NIST API
encrypt.c                                 - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_encrypt.c                       - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG file

./Optimized_Implementation/EncCPA:
api.h                                     - Required NIST API
encrypt.c                                 - Instantiation of the API
Makefile                                  - Makefile to make the KAT files
PQCgenKAT_encrypt.c                       - NIST test harness
rng.c                                     - NIST DRBG file
rng.h                                     - NIST DRBG fil
