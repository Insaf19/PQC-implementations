Script to run experiments that support the conjecture used in the security reduction 
of the lattice-based signature scheme qTESLA 
--------------------------------------------------------------------------------
Authors: Edward Eaton
Owners: All submitters of qTESLA by name. 
--------------------------------------------------------------------------------

This sage script can be used to run experiments for the two provable secure parameter sets 
of the lattice-based signature scheme qTESLA. 


The main function 
"experimentsSecurityConjecture()" takes no input. By default it samples
values according to the conjecture and qTESLA-p-III 10,000 times. The function
prints information about the number of runs that are done for orientation. 
In case an example that contradicts the statement of our conjecture is found, 
the functions prints "Likely counterexample observed:" and the values "y" and "z". 

