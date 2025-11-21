# CDT table generation for a given sigma and targeted precision beta
# Tables are generated according to the computer wordsize, e.g., prec=32 or prec=64

import time


def rho(k, sigma):
    return exp(-(k/sigma)^2/2)


hexdigits = "0123456789ABCDEF"
def hexstring(w, n):
    global hexdigits
    s = ""
    while w > 0:
        s = hexdigits[w & 15] + s
        w >>= 4
    s = ("0"*n)[0:n-len(s)] + s
    return s


# half-table with ((prec-1)*t + 1)-bit sorting keys:
def makeCDT(sigma, border, t, prec):
    print "/*************************************************************************************"
    print "* qTESLA: an efficient post-quantum signature scheme based on the R-LWE problem"
    print "*"
    print "* Abstract: CDT constants for the Gaussian sampler"
    print "**************************************************************************************/"
    print ""
    print "#ifndef CDTSAMP" + str(prec)
    print "#define CDTSAMP" + str(prec)
    print ""
    print "#include <stdint.h>"
    print "#include \"params.h\""
    print ""
    print "// sigma =", float(sigma), ",", prec*t, "-bit precision"
    # compute normalization factor:
    S = rho(0, sigma)
    for k in range(1, border + 1):
        S += 2*rho(k, sigma)
    #print "// S =", float(S)
    print ""
    print "#define CDT_ROWS " + str(border + 1)
    print "#define CDT_COLS " + str(t)
    print ""
    print "static const int" + str(prec) + "_t cdt_v[CDT_ROWS*CDT_COLS] = {"

    suffix = "LL" if prec == 64 else "L" if prec == 32 else ""
    line = "    "
    for c in range(t - 1, -1, -1):
        line += "0x" + hexstring(0, prec >> 2) + suffix + ", "
    line += "// 0"
    print line

    shift = 1 << ((prec - 1)*t)
    v = rho(0, sigma)/S

    w = floor(v*shift)
    line = "    "
    for c in range(t - 1, -1, -1):
        d = w >> ((prec - 1)*c)
        w -= d << ((prec - 1)*c)
        line += "0x" + hexstring(d, prec >> 2) + suffix + ", "
    line += "// 1"
    print line

    ok = True
    for k in range(1, border):
        v += 2*rho(k, sigma)/S

        w = floor(v*shift)
        line = "    "
        for c in range(t - 1, -1, -1):
            d = w >> ((prec - 1)*c)
            w -= d << ((prec - 1)*c)
            line += "0x" + hexstring(d, prec >> 2) + suffix + ", "
        line += "// " + str(k + 1)
        print line

        if d == ((1 << (prec - 1)) - 1):
            if k + 1 != border:
                print "// ----------------------------------------------------"
                print "// >>> PLEASE RUN THE SCRIPT AGAIN WITH border =", k + 1, "<<<"
                ok = False
                break
        else:
            if k + 1 == border:
                print "// ----------------------------------------------------"
                print "// >>> PLEASE RUN THE SCRIPT AGAIN WITH A LARGER border <<<"
                ok = False
                break
    print "}; // cdt_v"
    print ""
    if ok:
        #print "// actual precision:", float(-log(abs(S - v), 2)), "bits"
        print "// memory requirements:"
        for k in range(11, 4, -1):
            s = str(1 << k)
            s = (" "*4)[0:4-len(s)] + s
            u = str(((1 << k) + border + 1)*(t + 1)*(prec >> 3))
            u = (" "*5)[0:5-len(u)] + u
            print "//    ", s, "samples:", u, "bytes"
        print "// table alone:", (prec >> 3)*(border + 1)*t, "bytes"
        print ""
    print "#endif // CDTSAMP" + str(prec) + "\n"


flavor = "qTESLA-I"
#flavor = "qTESLA-II"
#flavor = "qTESLA-III"
#flavor = "qTESLA-p-I"
#flavor = "qTESLA-p-III"
#flavor = "qTESLA-V"
#flavor = "qTESLA-V-size"

#prec = 32
prec = 64

elapsed = -time.clock()
if flavor == "qTESLA-I":
    sigma = ceil(100*22.93)/100
    if prec == 32:
        makeCDT(sigma, 206, 2, 32)   #  beta = 64-bit samples
    else:
        makeCDT(sigma, 208, 1, 64)   #  beta = 64-bit samples
elif flavor == "qTESLA-II":
    sigma = ceil(100* 9.73)/100
    if prec == 32:
        makeCDT(sigma, 109, 3, 32)   #  beta = 96-bit samples
    else:
        makeCDT(sigma, 127, 2, 64)   #  beta = 128-bit samples
elif flavor == "qTESLA-III":
    sigma = ceil(100*10.20)/100
    if prec == 32:
        makeCDT(sigma, 132, 4, 32)   #  beta = 128-bit samples
    else:
        makeCDT(sigma, 134, 2, 64)   #  beta = 128-bit samples
elif flavor == "qTESLA-V" or flavor == "qTESLA-V-size":
    sigma = ceil(100*10.20)/100
    if prec == 32:
        makeCDT(sigma, 176, 7, 32)   #  beta = 224-bit samples
    else:
        makeCDT(sigma, 190, 4, 64)   #  beta = 256-bit samples
elif flavor == "qTESLA-p-I":
    sigma = ceil(100* 8.50)/100
    if prec == 32:
        makeCDT(sigma,  77, 2, 32)   #  beta = 64-bit samples
    else:
        makeCDT(sigma,  78, 1, 64)   #  beta = 64-bit samples
elif flavor == "qTESLA-p-III":
    sigma = ceil(100* 8.50)/100
    if prec == 32:
        makeCDT(sigma, 110, 4, 32)   # beta = 128-bit samples
    else:
        makeCDT(sigma, 111, 2, 64)   # beta = 128-bit samples
else:
    print "NOT IMPLEMENTED"
elapsed += time.clock()

#print ""
#print ">>> all done:", elapsed, "s."
