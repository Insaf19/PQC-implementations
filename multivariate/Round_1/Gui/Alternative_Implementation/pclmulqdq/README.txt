This folder contains the c-code of our implementation of the Gui Signature scheme optimized for pclmulqdq instructions.

The folder contains the three subfolders
Gui-184
Gui-312 and
Gui-448

each of which contains the code for one of the proposed parameter sets.
For the content of the subfolders, see the corresponding README.txt files.

Type 'make'. It will generate an executable using the source files from the directory specified by PROJ_DIR.     

The default value of PROJ_DIR is Gui-184.  To generate executable files
PQCgenKAT_sign, gui-genkey, gui-sign, and gui-verify
from other directories, please type "make PROJ=Gui-312" or 
"make PROJ=Gui-448".

For explanation of files under these directories, please refer to the
README.txt in each directory.

other files under this directory are:
PQCgenKAT_sign.c - source file for program generating the KAT files
gui-{genkey,sign,verify}.c - source file for testing programs
util.c - small utility programs
util.h - header for utility programs

            
The single algorithms gui-genkey, gui-sign and gui-verify are used as follows.
  (1)
  Run:  gui-genkey pk.txt sk.txt [seed_file]
  gui-genkey generates a Gui key pair and stores it in the files pk.txt and sk.txt.
  If seed_file is set, the algorithm uses the content of seed_file as seed for the PRNG and outputs the used randomness in the terminal.
  (2)
  Run:  gui-sign sk.txt  file_to_be_signed [seed_file] > signaturegile.txt
  gui-sign reads in the secret key from sk.txt and the message from file_to_be_signed.
  If seed_file is set, rainbow-sign uses the content of seed_file as seed for the PRNG and outputs the used randomness in the terminal.
  (3)
  Run: gui-verify pk.txt file_to_be_signed signaturefile.txt
  The algorithm reads in the public key, the signed document and the signature and outputs TRUE or FALSE. 
  
  Remark: The length of the seed read in by algorithms gui-genkey and gui-sign is fixed to 48 bytes (=384 bit).
