from sage.all import *
from random import randint

################################################################################
## qTESLA-p-I
# n = 1024
# q = 485978113
# d = 22
# B = 2**21 - 1
# LE = 554

## qTESLA-p-III
n = 2048
q = 1129725953
d = 24
B = 2**23 - 1
LE = 901

## Definition of the polynomial and residue class ring
R = PolynomialRing(GF(q),'x')
x = R.gen()
S = R.quotient(x**(n) + 1,'a')
a = S.gen()

def zeroCentredMod(i,j):
    c = i % j
    threshold = floor(j/2)
    if c <= threshold:
        return c
    else:
        return c - j

def roundInt(i):
    return ( zeroCentredMod(i,q) - zeroCentredMod( zeroCentredMod(i,q),(2**d)))/(2**d)

def roundRingElement(r):
    rounded = 0
    for i in range(n):
        rounded += S(roundInt( Integer(r[i])))*(a**i)
    return rounded

def sampleFromDeltaY():
    result = 0
    for i in range(n):
        result += S( randint(0,4*B -1) - 2*B )*(a**i)
    return result

def isInvertible(r):
    try:
        m = r**(-1)
    except ZeroDivisionError:
        return False
    return True

def isInDeltaLPlus(r):
    for i in range(n):
        if ( abs( zeroCentredMod( Integer(r[i]), q) ) > 2**d + 2*LE - 1):
            return False
    return True

def experimentsSecurityConjecture():
    NUM_SAMPLES = 10000
    for i in range(NUM_SAMPLES):
        if i % 1000 == 0:
            print i
        y = sampleFromDeltaY()
        if not isInvertible(y):
            z = S.random_element()
            if isInDeltaLPlus(z*y):
                print "Likely counterexample observed: "
                print y
                print z


