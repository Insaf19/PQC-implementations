import csv
import tempfile
import os
import math
import itertools


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
            csvfile, fieldnames=parameter_list,extrasaction='ignore')
        writer.writerow(parameter_dict)

def calculate_sigma(params):
    params['sigma'] = RR(params['xi'] * 1.0) / math.sqrt(2 * math.log(2))
    return params['sigma']


def calculate_Le(params):
    params['Le'] = params['eta_e'] * params['h'] * params['sigma']
    return params['Le']

def calculate_E(params):
    Le = params['Le']
    n = params['n']
    if (n%3!=0):
        params['E'] = Le
    else:
        params['E'] = 2 * Le
    return params['E']

def calculate_Ls(params):
    params['Ls'] = params['eta_s'] * params['h'] * params['sigma']
    return params['Ls']

def calculate_S(params):
    Ls = params['Ls']
    n = params['n']
    if (n%3!=0):
        params['S'] = Ls
    else:
        params['S'] = 2 * Ls
    return params['S']

def calculate_B(params):
    n = params['n']
    Ls = params['Ls']
    M = params['M']
    # n root of M
    nm = (M ** (1. / (n)))

    if(n%3!=0):
        initial_B = (nm + 2 * Ls - 1) * 1.0 / (2 * (1 - nm))
    else:
        initial_B = (nm + 4 * Ls - 1) * 1.0 / (2 * (1 - nm))
    initial_B = 2 ** ceil(RR(log(initial_B,2))) - 1
    params['B'] = initial_B
    return params['B']

def calculate_d(params):
    Le = params['Le']
    k = params['k']
    n = params['n']
    B = params['B']
		# you have to set self.current_param_object.d in the end

    initial_d = ceil(log(B,2))+1

    ls = (0.3 ** (1./ (k*n)))
    t = 1 - ls
    if (n%3!=0):
        dv = (2*Le + 1) / t
    else:
        dv = (4*Le + 1) / t
    params['d'] = int(max(ceil(math.log(dv, 2)),initial_d))
    return params['d']

def calculate_h(params):
    n = params['n']
    la = params['la']
    # you have to set self.current_param_object.h in the end

    h = 1
    while 2**h * binomial(n, h) < 2**(2*la):
        h += 1
    params['h'] = h
    return params['h']

def calculate_q_heuristic(params):
    n = params['n']
    d = params['d']
    B = params['B']

    initial_q = 4*B+1
    initial_q_second = 2**(d+1) +1
    initial_q = int(max(initial_q,initial_q_second))
    q_found = False
    while not q_found:
        initial_q = next_prime(initial_q)
        if (n%3!=0):
            q_found = (initial_q % (2 * n) == 1)
        else:
            q_found = (initial_q % (n/6) == 1) and (initial_q % 9 == 1)
    params['q'] = initial_q
    return params['q']

def calculate_q_provable(params):
    calculate_dH(params)
    calculate_dS(params)
    calculate_dL(params)
    dS = params['dS']
    dH = params['dH']
    dL = params['dL']
    k = params['k']
    la = params['la']
    qs = params['qs']
    qh = params['qh']

    n = params['n']
    d = params['d']
    B = params['B']

    initial_q = 4*B+1
    initial_q_second = 2**(d+1) +1 
    initial_q_third = (dS * dH * dL)** (1./(n*k))
    initial_q_forth = (3.*2.**(4. * la + k * n * d ) * qs**3. * (qs + qh)**2.)**(1./(n*k))

    initial_q = int(max(initial_q,initial_q_second,initial_q_third,initial_q_forth))
    q_found = False
    while not q_found:
        initial_q = next_prime(initial_q)
        if (n%3!=0):
            q_found = (initial_q % (2 * n) == 1)
        else:
            q_found = (initial_q % (n/6) == 1) and (initial_q % 9 == 1)
    params['q'] = initial_q
    return params['q']
    
def calculate_dH(params):
    sm = 0
    for j in incl_range(0, params['h'], 1):
        for i in incl_range(0, params['h'] - j, 1):
            sm += binomial(params['k'] * params['n'], 2 * i) * 2**(2*i) * binomial(params['k'] * params['n'] - 2 * i, j) * 2**j
    params['dH'] = sm
    return params['dH']

def calculate_dS(params):
    n = params['n']
    if (n%3!=0):
        params['dS'] = (4 * (params['B'] - params['Ls']) + 1) ** params['n']
    else:
        params['dS'] = (4 * (params['B'] - 2 * params['Ls']) + 1) ** params['n']
    return params['dS']

def calculate_dL(params):
    params['dL'] = (2 ** (params['d'] + 1) + 1) ** (params['n']*params['k'])
    return params['dL']


def calculate_pksize(params):
    k = params['k']
    n = params['n']
    q = params['q']
    kappa = params['kappa']

    params['pksize'] = (k * n * (math.ceil(math.log(q, 2))) + kappa)/8
    return params['pksize']

def calculate_sksize(params):
    n = params['n']
    sigma = params['sigma']
    k = params['k']
    kappa = params['kappa']
    la = params['la']

    if (la==95):
        if(sigma==22.93):
            t=209
	elif(sigma==8.5):
            t=79
    elif(la==128):
        t=128
    elif(la==160):
        if(sigma==10.2):
            t=135
        elif(sigma==8.5):
            t=112
    elif(la==225):
        t=191
    elif(la==256):
        t=191

    params['sksize'] =  (n * (k+1) * (math.ceil(math.log(t-1,2))+1) + 2*kappa) / 8
    return params['sksize']

def calculate_sigsize(params):
    kappa = params['kappa']
    n = params['n']
    B = params['B']
    Ls = params['Ls']
    if (n%3!=0):
        params['sigsize'] = (kappa + n * (math.ceil(math.log(B - Ls, 2)) + 1))/8
    else: 
        params['sigsize'] = (kappa + n * (math.ceil(math.log(B - 2 * Ls, 2)) + 1))/8
    return params['sigsize']


################################################################################
def call_LWE_Estimator(params):
    n = params['n']
    q = params['q']
    sigma = params['sigma']
    k= params['k']

    load("estimator.py")
    alpha = sqrt(2*pi)*sigma / q
    cost_model = BKZ.qsieve
    costs = estimate_lwe(n, alpha, q, n*k, reduction_cost_model=cost_model)
    hardness_lwe = costs['usvp']['rop']
    for alg in costs:
        hardness_alg = costs[alg]['rop']
        if hardness_lwe > hardness_alg:
            hardness_lwe = hardness_alg

    params['hardness'] = RR(log(hardness_lwe,2))
    
    cost_model = partial(BKZ.ADPS16,mode="quantum")
    costs = estimate_lwe(n, alpha, q, n*k, reduction_cost_model=cost_model)
    hardness_lwe = costs['usvp']['rop']
    for alg in costs:
        hardness_alg = costs[alg]['rop']
        if hardness_lwe > hardness_alg:
            hardness_lwe = hardness_alg
    params['hardness_ADPS16']=RR(log(hardness_lwe,2))

    return params['hardness']

################################################################################
def calculate_params(sigma, k, n, eta_e, eta_s, M, kappa, la, prof):
    assert prof in ["Heuristic","Provably-Secure"], 'Proof for parameter selection should be either "Heuristic" or "Provably-Secure".' 
    parameters = {}
    parameters['sigma'] = sigma
    parameters['k'] = k
    parameters['n'] = n
    parameters['eta_e'] = eta_e
    parameters['eta_s'] = eta_s
    parameters['M'] = M
    parameters['kappa'] = kappa
    parameters['la'] = la
    parameters['qs'] = 2 ** 64
    parameters['qh'] = 2 ** 128

    #sigma = calculate_sigma(parameters)
    h = calculate_h(parameters)
    Le = calculate_Le(parameters)
    Ls = calculate_Ls(parameters)
    E = calculate_E(parameters)
    S = calculate_S(parameters)
    B = calculate_B(parameters)
    d = calculate_d(parameters)

    if prof == "Heuristic":
        q = calculate_q_heuristic(parameters)
    elif prof == "Provably-Secure":
        q = calculate_q_provable(parameters)

    parameters['logq'] = round(RR(log(q,2)),3)
    pksize = calculate_pksize(parameters)
    sksize = calculate_sksize(parameters)
    sigsize = calculate_sigsize(parameters)

    if parameters['q']>2**(32):
        parameters['hardness'] = 0
    else: 
        parameters['hardness'] = call_LWE_Estimator(parameters)
    
    return parameters

def print_qtesla_parameters():
    parameter_list = [
        'sigma', 'la', 'n', 'k', 'eta_e', 'eta_s', 'M', 'kappa',
        'h', 'Le', 'Ls', 'E', 'S', 'q', 'logq', 'B', 'd', 'pksize',
        'sksize', 'sigsize'] + ['hardness'] + ['hardness_ADPS16']

    print "qTesla Heuristic category 1 parameters"
    print """calculate_params(22.93,1,512,2.306,2.306,0.3,256,95,"Heuristic")"""
    params=calculate_params(22.93,1,512,2.306,2.306,0.3,256,95,"Heuristic")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"

    print "qTesla Heuristic category 2 parameters"
    print """calculate_params(9.73,1,768,2.264,2.264,0.3,256,128,"Heuristic")"""
    params=calculate_params(9.73,1,768,2.264,2.264,0.3,256,128,"Heuristic")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"
   
    print "qTesla Heuristic category 3 parameters"
    print """calculate_params(10.2,1,1024,2.344,2.519,0.3,256,160,"Heuristic")"""
    params=calculate_params(10.2,1,1024,2.344,2.519,0.3,256,160,"Heuristic")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"

    print "qTesla Heuristic category 5 parameters"
    print """calculate_params(10.2,1,2048,2.498,2.498,0.3,256,225,"Heuristic")"""
    params=calculate_params(10.2,1,2048,2.498,2.498,0.3,256,225,"Heuristic")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"

    print "qTesla Heuristic category 5 (size) parameters"
    print """calculate_params(10.2,1,1536,2.282,2.282,0.3,256,256,"Heuristic")"""
    params=calculate_params(10.2,1,1536,2.282,2.282,0.3,256,256,"Heuristic")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"

    print "qTesla Provable category 1 parameters"   
    print """"calculate_params(8.5,4,1024,2.61,2.61,0.3,256,95,"Provably-Secure")"""
    params=calculate_params(8.5,4,1024,2.61,2.61,0.3,256,95,"Provably-Secure")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"

    print "qTesla Provable category 3 parameters"   
    print """calculate_params(8.5,5,2048,2.65,2.65,0.3,256,160,"Provably-Secure")"""
    params=calculate_params(8.5,5,2048,2.65,2.65,0.3,256,160,"Provably-Secure")
    print "\n",['{}'.format(round(params[k],3)).rstrip('0').rstrip('.') for k in parameter_list],"\n"



