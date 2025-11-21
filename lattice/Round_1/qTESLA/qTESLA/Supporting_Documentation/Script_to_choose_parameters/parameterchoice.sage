import csv
import tempfile
import os
import math
import itertools

################################################################################
def calculate_sigma(params):
    params['sigma'] = RR(params['xi'] * 1.0) / math.sqrt(2 * math.log(2))
    return params['sigma']

#####################
def calculate_Le(params):
    params['Le'] = params['eta_e'] * params['h'] * params['sigma']
    return params['Le']

#####################
def calculate_Ls(params):
    params['Ls'] = params['eta_s'] * params['h'] * params['sigma']
    return params['Ls']

#####################
def calculate_B(params):
    n = params['n']
    Ls = params['Ls']
    M = params['M']
    # n-th root of M
    nm = (M ** (1. / (n)))

    initial_B = (nm + 2 * Ls - 1) * 1.0 / (2 * (1 - nm))
    initial_B = 2 ** ceil(RR(log(initial_B,2))) - 1
    print "log(B,2) = ", RR(log(initial_B,2))
    params['B'] = initial_B
    return params['B']

#####################
def calculate_d(params):
    Le = params['Le']
    n = params['n']
    # you have to set self.current_param_object.d in the end

    ls = (0.3 ** (1./ (n)))
    t = 1 - ls
    dv = (2*Le + 1) / t
    params['d'] = ceil(math.log(dv, 2))
    return params['d']

#####################
def calculate_h(params):
    n = params['n']
    lamb = params['lamb']

    h = 1
    while 2**h * binomial(n, h) < 2**(2*lamb):
        h += 1
    params['h'] = h
    return params['h']

#####################
def calculate_q(params):
    dS = params['dS']
    dH = params['dH']
    dL = params['dL']
    lamb = params['lamb']
    d = params['d']
    qs = params['qs']
    qh = params['qh']
    n = params['n']

    initial_q = (dS * dH * dL)** (1./(n))
    initial_q_second = (3.*2.**(4. * lamb + n * (d + 1)) * qs**3. * (qs + qh)**2.)**(1./(n))

    initial_q = int(max(initial_q,initial_q_second))
    q_found = False
    while not q_found:
        initial_q = next_prime(initial_q)
        q_found = (initial_q % (2 * n) == 1)  
        if q_found and RR(log(initial_q, 2)) > 26:
            q_found = nice_prime(initial_q)
    params['q'] = initial_q
    return params['q']

def nice_prime(q):
    r = ceil(log(q, 2))

    for s in range(0, r):
        if q == 2**r - 2**s + 1:
            return True

    return False

#####################
def calculate_dH(params):
    sm = 0
    for j in incl_range(0, params['h'], 1):
        for i in incl_range(0, params['h'] - j, 1):
            sm += binomial(params['n'], 2 * i) * 2**(2*i) * \
                  binomial(params['n'] - 2 * i, j) * 2**j
    params['dH'] = sm
    return params['dH']

def calculate_dS(params):
    params['dS'] = (4 * (params['B'] - params['Ls']) + 1) ** params['n']
    return params['dS']

def calculate_dL(params):
    params['dL'] = (2 ** (params['d'] + 1) + 1)
    return params['dL']

#####################
def calculate_pksize(params):
    n = params['n']
    q = params['q']
    kappa = params['kappa']

    params['pksize'] = n * (math.ceil(math.log(q, 2))) + kappa
    return params['pksize']

def calculate_sksize(params):
    n = params['n']
    sigma = params['sigma']
    kappa = params['kappa']
    lamb = params['lamb']

    if (lamb==128):
        t=13.4
    elif (lamb==192):
        t=16.4
    elif (lamb==256):
        t=18.9
    else:
        t=14

    params['sksize'] =  n * 2 * math.ceil(math.log(t * sigma + 1,2)) + kappa
    return params['sksize']

def calculate_sigsize(params):
    kappa = params['kappa']
    n = params['n']
    B = params['B']
    Ls = params['Ls']
    params['sigsize'] = kappa + n * (
        math.ceil(math.log(B - Ls, 2)) + 1)
    return params['sigsize']

################################################################################
def call_LWE_Estimator(params):
    n = params['n']
    q = params['q']
    sigma = params['sigma']

    load("estimator.py")
    alpha = sigma / q
    costs = estimate_lwe(n, alpha, q, n, reduction_cost_model=BKZ.qsieve)
    #costs = estimate_lwe(n, alpha, q, n)
    hardness_usvp = costs['usvp']['rop']
    hardness_lwe = hardness_usvp
    for alg in costs:
        hardness_alg = costs[alg]['rop']
        if hardness_lwe > hardness_alg:
            hardness_lwe = hardness_alg

    params['hardness'] = RR(log(hardness_lwe,2))
    return params['hardness']

################################################################################
def calculate_params(xi, n, eta_e, eta_s, M, kappa, lamb):

    parameters = {}
    parameters['xi'] = xi
    parameters['n'] = n
    parameters['eta_e'] = eta_e
    parameters['eta_s'] = eta_s
    parameters['M'] = M
    parameters['kappa'] = kappa
    parameters['lamb'] = lamb
    parameters['qs'] = 2 ** 64
    parameters['qh'] = 2 ** 128

    sigma = calculate_sigma(parameters)
    h = calculate_h(parameters)
    Ls = calculate_Ls(parameters)
    Le = calculate_Le(parameters)  
    B = calculate_B(parameters)  
    d = calculate_d(parameters)  
    dH = calculate_dH(parameters)  
    dS = calculate_dS(parameters)  
    dL = calculate_dL(parameters)  
    q = calculate_q(parameters)  
    parameters['logq'] = RR(log(q,2))
    
    pksize = calculate_pksize(parameters)
    sksize = calculate_sksize(parameters)
    sigsize = calculate_sigsize(parameters)

    hardness = call_LWE_Estimator(parameters)

    return parameters

##############
def range_calculate_params(xi_start, xi_end, xi_step, n_start, n_end, n_step, eta_e, eta_s, M, kappa, lamb,
                           filename):

    xi_range = incl_range(xi_start, xi_end, xi_step)
    n_range = incl_range(n_start, n_end, n_step)

    parameter_list = [
        'xi', 'lamb', 'n', 'eta_e', 'eta_s', 'M', 'kappa', 'sigma',
        'h', 'Le', 'Ls', 'q', 'logq', 'B', 'd', 'qs' , 'qh', 'pksize',
        'sksize', 'sigsize'] + ['dH', 'dS', 'dL', 'hardness']
    write_header_to_csv(filename, parameter_list)

    parameter_combinations = itertools.product(xi_range, n_range)

    for combination in parameter_combinations:
        parameters = calculate_params(combination[0], combination[1], 
                                      combination[2], eta_e, eta_s, M, kappa, lamb)

        if parameters['hardness']>= parameters['lamb']: 
            write_params_to_csv(filename, parameter_list, parameters)

################################################################################
def incl_range(l, u, s):
    return range(l, u+1, s)

def write_header_to_csv(filename, header_list):
    with open(filename, "w") as csvfile:
        writer = csv.DictWriter(
            csvfile, fieldnames=header_list)
        writer.writeheader()

def write_params_to_csv(filename, parameter_list, parameter_dict):
    with open(filename, "a") as csvfile:
        writer = csv.DictWriter(
            csvfile, fieldnames=parameter_list)
        writer.writerow(parameter_dict)
