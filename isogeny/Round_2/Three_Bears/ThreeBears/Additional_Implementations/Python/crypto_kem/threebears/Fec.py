
def _shift(a,n=1,f=0x211):
    "Return a>>n in binary ring described by f"
    for i in range(n):
        if a&1: a ^= f
        a>>=1
    return a
    
def _compute(data):
    "Compute FEC on data"
    r = 0
    for d in data: r = _shift(r^d,8,0x46231)
    return r

def append(data):
    "Append correction information to data"
    fec = _compute(data)
    return data + bytearray(fec>>(8*i) & 0xFF for i in range(3))

def correct(data):
    "Correct up to 2 errors in error-corrected data"
    data = bytearray(data)
    
    def _mul(a,b):
        r=0
        for i in range(9):
            if (b>>(8-i))&1: r ^= a
            a = _shift(a,1)
        return r

    def _htr(x):
        table = [292, 266, 299, 471, 308, 267, 372, 500, 0]
        ret = 0
        for i in xrange(9):
            ret ^= ((x>>i)&1) * table[i]
        return ret
    
    # a = _compute(data)
    # ... but actually only process two bits of last byte
    a = _compute(data[:-1])
    a = _shift(a^data[-1],2,0x46231)
    
    # c = a*reverse(a), but use _shift to reduce it
    reva = sum((a>>i&1)<<(17-i) for i in xrange(18))
    c = _mul(_shift(a,9),_shift(reva,9))
    
    # FLT inverse
    inv = c
    for i in xrange(7): inv = _mul(_mul(inv,inv),c)
    inv = _shift(_mul(inv,inv),17) # To cancel out above shifts and reversal
    
    # Adjust for length))
    a = _shift(a,511+(8*len(data)-6))
    b = _mul(a,_htr(inv))
    
    for c in [b,a^b]:
        for i in range(len(data)):
            if c < 256 and c&(c-1) == 0:
                data[i] ^= c
            c = _shift(c,8)
    return data[:-3]

if __name__ == "__main__":
    L = 7
    ret = "Pass"
    errors = [(i,j) for i in range(L) for j in range(8)]
    for i1,j1 in errors:
        for i2,j2 in errors:
            if (i1,j1) < (i2,j2): continue
            data = bytearray(L)
            data[i1] ^= 1<<j1
            if (i1,j1) != (i2,j2): data[i2] ^= 1<<j2
            if append(correct(data)) != bytearray(L):
                ret = "Fail"
                print("Fail %d,%d; %d,%d" % (i1,j1,i2,j2))
    print("%s FEC test (len=%d)\n" % (ret,L))
