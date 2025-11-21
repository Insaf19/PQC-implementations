#! /bin/bash


get_params_h()
{
echo -ne "#ifndef PARAMS_H
#define PARAMS_H

#define PARAM_N $n
#define PARAM_N_LOG $nlog
#define PARAM_SIGMA $sigma
#define PARAM_Q $q
#define PARAM_Q_LOG $(printf %.0f $qlog)
#define PARAM_QINV $qinv
#define PARAM_B $B
#define PARAM_B_BITS $bbits

#define PARAM_K $k
#define PARAM_SIGMA_E PARAM_SIGMA

#define PARAM_W $w
#define PARAM_D $d
	
#define PARAM_KEYGEN_BOUND_E $L
#define PARAM_REJECTION PARAM_KEYGEN_BOUND_E
#define PARAM_KEYGEN_BOUND_S $Ls
#define PARAM_U $(printf %.0f $U)
#endif"
}
Line=0
# Set input file
FILE=params_list_reduced.txt
# Set output file
OUTPUT=params_rej_rate_list.txt
# Check if input file exist
[ ! -f $FILE ] && { echo "File not found: $FILE"; exit; }
# Get the system time
FIRST=$SECONDS
OLDIFS=$IFS
IFS=,;
# Get number of parameter sets to monitor processing time
Lines=$(wc -l $FILE|awk '{print $1}');
echo "there are $Lines parameters" > temp;
# ind, la, n, k, sigma, omega, L, U, q, qlog, B, d, hardness
while read line la n k s w l u q qlog B D security;
do
    # writing new values on to old one 
    echo $line
    L=$(printf %.0f $(echo "$l+0.99" |bc -l));
    U=$(printf %.0f $(echo "$u+0.99" |bc -l));
    d=$(printf %.0f $(echo "$D+0.99" |bc -l));
    echo "trying $line th of $Lines" >> temp;
    # Calculate log_2(n)
    nlog=$(printf %.0f $(echo "(l($n)+l(2)-0.11)/l(2)" | bc -l));
    # Calculate 1/q
    qinv=$(echo "1.0/$q" | bc -l);
    sigma=$(printf %.0f $(echo "$s+0.99" |bc -l));
    Ls=$(echo "14*$sigma*$w"|bc -l);
    # Calculate log_2(B)
    bbits=$(printf %.0f $(echo "l($B)/l(2)" | bc -l));
    # For now we are searching l between 2.6 and 2.7 but it is a tight range!
    echo "---" >> temp;
    # set the params.h file
    echo $(get_params_h) > ../../Implementations/Reference/params.h;
    # compile new parameters
    echo "make" >> temp;
    (cd ../../Implementations/Reference/ && make > /dev/null);
    # run the test program and save rejection ratios for check_e,w and z
    timeout 30 ../../Implementations/Reference/test/test_sign > temp.res;
    # if test program doesn't end in 30 seconds 
    # It must be stuck in somewhere so try another L
    REJRATS=$(< temp.res);
    # save the parameter set with performance results
    echo "$line,$la,$n,$k,$sigma,$q,$qlog,$qinv,$B,$bbits,$w,$d,$L,$U,$security,$REJRATS" >> $OUTPUT;
    rm -f ./temp.res;
done < $FILE;
# get the system time
LAST=$SECONDS;
RUNTIME=$(($LAST - $FIRST));
HOURS=$((RUNTIME / 3600));
RUNTIME=$((RUNTIME % 3600));
MINS=$((RUNTIME / 60));
SECS=$((RUNTIME % 60));
echo "$HOURS:$MINS:$SECS" >> temp;
IFS=$OLDIFS;
