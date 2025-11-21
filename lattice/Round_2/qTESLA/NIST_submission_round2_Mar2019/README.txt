Submission to NIST’s post-quantum project (2nd round):
lattice-based digital signature scheme qTESLA
--------------------------------------------------------------------------------

Name of the cryptosystem: qTESLA
Principal and auxiliary submitters:
Sedat Akleylek, Erdem Alkim, Paulo Barreto, Nina Bindel, Johannes Buchmann, 
Edward Eaton, Gus Gutoski, Juliane Krämer, Patrick Longa, Harun Polat, 
Jefferson Ricardini, and Gustavo Zanon
--------------------------------------------------------------------------------

The submission of the lattice-based digital signature scheme qTESLA includes four 
folders:

- "Additional_implementations": Contains AVX2 optimized implementations of the
                              heuristic parameter sets for x64 platforms
- "KAT":                      Contains the Known Answer Tests
- "Reference_implementation": Contains the reference implementation
- "Optimized_implementation": Contains the optimized implementation
- "Supporting_Documentation": Contains electronic version of all written 
                              materials, our sage script to choose parameters, 
                              and the submitters statements  

We list all files in the subfolders and give a brief description of each.
--------------------------------------------------------------------------------

Subfolder "Additional_implementations\avx2":
This folder contains the following subfolders which contain the AVX2-optimized 
x64 implementations for the proposed heuristic parameter sets:

- "qTesla-I"     : Additional AVX2 implementation of qTesla-I with parameters for
                 NIST’s security category 1
- "qTesla-I-s"   : Additional AVX2 implementation of qTesla-I-s with parameters for
                 NIST’s security category 1
- "qTesla-III"   : Additional AVX2 implementation of qTesla-III with parameters for
                 NIST’s security category 3
- "qTesla-III-s" : Additional AVX2 implementation of qTesla-III-s with parameters for
                 NIST’s security category 3
- "qTesla-V"     : Additional AVX2 implementation of qTesla-V with parameters for
                 NIST’s security category 5
- "qTesla-V-s"   : Additional AVX2 implementation of qTesla-V-s with parameters for
                 NIST’s security category 5

--------------------------------------------------------------------------------
Subfolder "KAT":
This folder contains knowns answer tests results for the proposed parameter sets.

- "\ref\KAT32\PQCsignKAT_qTesla-I.rsp"   : Known answer test results for qTesla-I, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-II.rsp"  : Known answer test results for qTesla-III, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-III.rsp" : Known answer test results for qTesla-III, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-V.rsp"   : Known answer test results for qTesla-V, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-V-size.rsp" : Known answer test results for qTesla-V-size, 
                                              32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-p-I.rsp" : Known answer test results for qTesla-p-I, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-p-III.rsp" : Known answer test results for qTesla-p-III, 
                                             32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-I-s.rsp"   : Known answer test results for qTesla-I-s, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-II-s.rsp"  : Known answer test results for qTesla-III-s, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-III-s.rsp" : Known answer test results for qTesla-III-s, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-V-s.rsp"   : Known answer test results for qTesla-V-s, 
                                           32-bit platforms
- "\ref\KAT32\PQCsignKAT_qTesla-V-size-s.rsp" : Known answer test results for qTesla-V-size-s, 
                                              32-bit platforms

- "\ref\KAT64\PQCsignKAT_qTesla-I.rsp"   : Known answer test results for qTesla-I, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-II.rsp"  : Known answer test results for qTesla-II, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-III.rsp" : Known answer test results for qTesla-III, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-V.rsp"   : Known answer test results for qTesla-V, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-V-size.rsp" : Known answer test results for qTesla-V-size, 
                                              64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-p-I.rsp" : Known answer test results for qTesla-p-I, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-p-III.rsp" : Known answer test results for qTesla-p-III, 
                                             64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-I-s.rsp"   : Known answer test results for qTesla-I-s, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-II-s.rsp"  : Known answer test results for qTesla-II-s, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-III-s.rsp" : Known answer test results for qTesla-III-s, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-V-s.rsp"   : Known answer test results for qTesla-V-s, 
                                           64-bit platforms
- "\ref\KAT64\PQCsignKAT_qTesla-V-size-s.rsp" : Known answer test results for qTesla-V-size-s, 
                                              64-bit platforms

- "\avx2\KAT64\PQCsignKAT_qTesla-I.rsp"   : Known answer test results for qTesla-I,
                                             additional AVX2 implementation
- "\avx2\KAT64\PQCsignKAT_qTesla-III.rsp" : Known answer test results for qTesla-III,
                                             additional AVX2 implementation
- "\avx2\KAT64\PQCsignKAT_qTesla-V.rsp"   : Known answer test results for qTesla-V,
                                             additional AVX2 implementation				
- "\avx2\KAT64\PQCsignKAT_qTesla-I-s.rsp"   : Known answer test results for qTesla-I-s,
                                             additional AVX2 implementation
- "\avx2\KAT64\PQCsignKAT_qTesla-III-s.rsp" : Known answer test results for qTesla-III-s,
                                             additional AVX2 implementation
- "\avx2\KAT64\PQCsignKAT_qTesla-V-s.rsp"   : Known answer test results for qTesla-V-s,
                                             additional AVX2 implementation

--------------------------------------------------------------------------------
Subfolder "Optimized_implementation":
This folder contains the following subfolders which contain the optimized implementations
for the proposed parameter sets:

- "qTesla-II"       : Optimized implementation of qTesla-II with parameters for
                    NIST’s security category 2
- "qTesla-II-s"     : Optimized implementation of qTesla-II-s with parameters for
                    NIST’s security category 2
- "qTesla-V-size"   : Optimized implementation of qTesla-V-size with parameters for
                    NIST’s security category 5
- "qTesla-V-size-s" : Optimized implementation of qTesla-V-size-s with parameters for
                    NIST’s security category 5

These implementations are written in C plus a reduction routine written in x64 assembly.
For all the other parameter sets, the reference implementation is the optimized 
implementation for this version of the software. 

--------------------------------------------------------------------------------
Subfolder "Reference_implementation":
This folder contains the following subfolders which contain the reference implementations
for the proposed parameter sets:

- "qTesla-I"   : Reference implementation of qTesla-I with parameters for
                 NIST’s security category 1
- "qTesla-I-s"   : Reference implementation of qTesla-I-s with parameters for
                 NIST’s security category 1
- "qTesla-II"  : Reference implementation of qTesla-II with parameters for
                 NIST’s security category 2
- "qTesla-II-s"  : Reference implementation of qTesla-II-s with parameters for
                 NIST’s security category 2
- "qTesla-III" : Reference implementation of qTesla-III with parameters for
                 NIST’s security category 3
- "qTesla-III-s" : Reference implementation of qTesla-III-s with parameters for
                 NIST’s security category 3
- "qTesla-V"   : Reference implementation of qTesla-V with parameters for
                 NIST’s security category 5
- "qTesla-V-s"   : Reference implementation of qTesla-V-s with parameters for
                 NIST’s security category 5
- "qTesla-V-size" : Reference implementation of qTesla-V-size with parameters for
                 NIST’s security category 5
- "qTesla-V-size-s" : Reference implementation of qTesla-V-size-s with parameters for
                 NIST’s security category 5
- "qTesla-p-I" : Reference implementation of qTesla-p-I with parameters for
                 NIST’s security category 1
- "qTesla-p-I-s" : Reference implementation of qTesla-p-I-s with parameters for
                 NIST’s security category 1
- "qTesla-p-III" : Reference implementation of qTesla-p-III with parameters for
                   NIST’s security category 3
- "qTesla-p-III-s" : Reference implementation of qTesla-p-III-s with parameters for
                   NIST’s security category 3

--------------------------------------------------------------------------------
Subfolder "Supporting_Documentation":
This folder contains the following subfolders. 

- "Implementation_owners_statements_qTESLA": This folder contains the statements
according to Section 2.D.3 in NIST's call for proposals. Each file is named
"qTESLA-implementation-owners-statement-NAME.pdf" where NAME is the family
name of one of the implementations owners, i.e., Akleylek, Alkim, Barreto, Longa,
Polat, Ricardini, or Zanon. 

- "Submitters_statements_qTESLA": This folder contains the statements
according to Section 2.D.1 in NIST's call for proposals. Each file is named
"qTESLA-NIST-submitters-statement-NAME.pdf" where NAME is the family name of one
of the submitters, i.e., Akleylek, Alkim, Barreto, Bindel, Buchmann, Eaton, 
Gutoski, Krämer, Longa, Polat, Ricardini, or Zanon. 

- "Script_to_choose_parameters": This folder contains all files needed to run
the sage script that we used to choose our proposed parameter sets. Those files are: 

   - "README_Script_Parameterchoice.rst": This is the README file of our sage
                     script to compute parameters.
   - "parameterchoice.sage": This file is the main file to compute all system
                     parameters and estimate the hardness of the corresponding 
                     R-LWE instance. To this end it calls a function defined in
                     "estimator.py"
   - "README_LWE_Estimator.rst": This is the README file of the LWE-Estimator 
                     written by Albrecht, Player, and Scott. We use the 
                     LWE-Estimator to estimate the hardness of our chosen LWE 
                     instances.
   - "estimator.py": This python script is the implementation of the 
                     LWE-Estimator by Albrecht, Play, and Scott that we call in
                     our sage script "parameterchoice.sage".
   - The rest of the contained files are subroutines of the LWE-Estimator. We 
                     do not describe them in detail here but refer to the 
                     README file of the LWE-Estimator. 

- "Script_for_conjecture": This folder contains a README file and the corresponding script 
Script_for_experiments_supporting_the_security_conjecture.py to run experiments that support 
the conjecture used in the security reduction.

- "Script_for_Gaussian_sampler": This folder contains the script qCDT.sage to generate
the precomputed CDT tables required by the Gaussian sampler.

- "qTESLA_round2_04.2019.pdf": This pdf file is the description of our scheme qTESLA. We give 
all supporting information about our submitted signature scheme in the pdf.

- "qTESLA_modifications_round2_04.2019.pdf": This pdf file contains a summary of the modifications 
of qTESLA for the submission in the second round. 