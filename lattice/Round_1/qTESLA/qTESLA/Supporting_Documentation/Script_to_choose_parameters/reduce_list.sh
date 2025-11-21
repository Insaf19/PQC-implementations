#! /bin/bash

# Set input file
FILE=params_list.txt
# Set output file
OUTPUT=params_list_reduced.txt
# Check if input file exist
[ ! -f $FILE ] && { echo "File not found: $FILE"; exit; }
# Get rid of empty lines and comments, then print only parameters used in the implementation.
#ind, la, n, k, sigma, omega, L, U, q, qlog, B, d, hardness    
awk -F"," 'BEGIN{i=0}{if($2 == 128 || $2 == 192 || $2 == 256) printf "%d,%d,%d,%d,%.1f,%d,%.1f,%.1f,%d,%.1f,%d,%.1f,%.2f\n", i++,$2, $3, $4, $9, $10, $11, $12, $13, $14, $15, $16, $27}' $FILE >$OUTPUT

