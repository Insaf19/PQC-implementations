Script to choose parameters for the lattice-based signature scheme qTESLA 
for the submission of NIST's call for post-quantum proposals
--------------------------------------------------------------------------------
Authors: Nina bindel and Jefferson Ricardini
Owners: All submitters of qTESLA by name. 
--------------------------------------------------------------------------------

This sage script choose parameters according for the lattice-based signature
scheme qTESLA to the tight security reduction in the quantum random oracle model.

The main function 
"calculate_params()" takes as input "xi, n, eta_e, eta_s, M, kappa, lamb" and 
saves all computed parameters in a dictonary. The names of the parameters are 
according to the names given in the submission document except for "lamb" which
corresponds to the security parameters "lambda" in the document.

To compute the hardness it calls the LWE-Estiator in the function "call_LWE_Estimator".

All functions to choose parameters are in the file "parameterchoice.sage". All
other files belong to the LWE-Estimator. More information about the usage of 
the LWE-Estimator can be found in "README_LWE_Estimator.rst".