Submission to NIST’s post-quantum project:
lattice-based digital signature scheme qTESLA
--------------------------------------------------------------------------------

Name of the cryptosystem: qTESLA
Principal and auxiliary submitters:
Sedat Akleylek, Erdem Alkim, Paulo Barreto, Nina Bindel, Johannes Buchmann, 
Edward Eaton, Gus Gutoski, Juliane Krämer, Patrick Longa, Harun Polat, 
Jefferson Ricardini, and Gustavo Zanon
--------------------------------------------------------------------------------

The submission of the lattice-based digital signature scheme qTESLA is organized
as follows. The submission folder "qTESLA_Bindel_Akleylek_Alkim_Barreto_Buchmann
_Eaton_Gutoski_Kraemer_Longa_Polat_Ricardini_Zanon" includes again four folders:

- "KAT":                      Contains the Known Answer Tests
- "Reference_Implementation": Contains the reference implementation
- "Optimized_Implementation": in this version, the optimized and reference
                              implementations are the same
- "Supporting_Documentation": Contains electronic version of all written 
                              materials, our sage script to choose parameters, 
                              and the submitters statements  

We list all files in the subfolders and give a brief description of each.
--------------------------------------------------------------------------------
Subfolder "KAT":
This folder contains Knowns answer tests results for proposed parameter sets.

- "PQCsignKAT_qTesla-128.rsp" : Known answer tests results for 128-bit security
  level
- "PQCsignKAT_qTesla-192.rsp" : Known answer tests results for 192-bit security
  level
- "PQCsignKAT_qTesla-256.rsp" : Known answer tests results for 256-bit security
  level

--------------------------------------------------------------------------------
Subfolder "Reference_Implementation":
This folder contains three subfolders which contain optimized implementation
for proposed parameter sets.

- "qTesla_128" : Reference implementation of qTesla with parameters for
                 NIST’s security category 1
- "qTesla_192" : Reference implementation of qTesla with parameters for
                 NIST’s security category 3
- "qTesla_256" : Reference implementation of qTesla with parameters for
                 NIST’s security category 5

--------------------------------------------------------------------------------
Subfolder "Supporting_Documentation":
This folder contains the following three subfolders and one pdf-file. 

- "Implementation_owners_statements_qTESLA": This folder contains the statements
according to Section 2.D.3 in NIST's call for proposals. Each file is named
"qTESLA-implementation-owners-statement-NAME.pdf" where NAME is the family
name of one of the implementations owners, i.e., Akleylek, Alkim, Barreto, Polat, 
Ricardini, or Zanon. 

- "Submitters_statments_qTESLA": This folder contains the statements
according to Section 2.D.1 in NIST's call for proposals. Each file is named
"qTESLA-NIST-submitters-statement-NAME.pdf" where NAME is the family name of one
of the submitters, i.e., Akleylek, Alkim, Barreto, Bindel, Buchmann, Eaton, 
Gutoski, Krämer, Longa, Polat, Ricardini, or Zanon. 

- "Script_to_choose_parameters": This folder contains all files needed to run
the sage script that we used to choose our proposed parameter sets qTESLA-128, 
qTESLA-192, and qTESLA-256. Those files are: 

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
                     do not describe them in detail here but refer the the 
                     README file of the LWE-Estimator.

- "qTESLA.pdf": This pdf file is the description of our scheme qTESLA. We give 
all supporting information about our submitted signature scheme in the pdf. 




