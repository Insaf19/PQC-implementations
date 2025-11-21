import os
from Keccak import cSHAKE256
import Fec
from math import ceil,floor

class InvalidCiphertextException(Exception): pass
class InvalidParameterException(Exception): pass

def _hex(ba): return "".join("%02x" % c for c in ba)
def _bitarray(nbits): return bytearray(int(ceil(nbits/8.)))

class Bear(object):
    CSHAKE_N = ""
    CSHAKE_S = "ThreeBears"
    _all = []
    
    def __str__(self): return self.NAME
    
    @staticmethod
    def _decodeInteger(vec):
        "Byte array -> single integer"
        return sum(v<<(8*i) for (i,v) in enumerate(vec))

    def _encodeVector(self,xs):
        "Array of integers mod N -> byte array"
        ret = bytearray()
        for x in xs:
            x %= self.N
            ret += bytearray([(x>>(8*i)) & 0xFF for i in range(self.NBYTES_N)])
        return ret

    def _parameter_block(self):
        "Parameter block to domain-separate our hash from other ThreeBears"
        return bytearray([
            self.VERSION, self.PRIVATE_KEY_BYTES,self.MATRIX_SEED_BYTES,self.ENC_SEED_BYTES,
            self.IV_BYTES,self.SHARED_SECRET_BYTES, self.LGX, self.D&0xFF, self.D>>8,
            self.d, int(self.VARIANCE*128)-1, self.LPR_BITS, self.FEC_BITS, self.CCA
        ])

    def _hash(self,purpose,string,length):
        "Hash a byte string with diversified cSHAKE XOF"
        return cSHAKE256(N=self.CSHAKE_N,S=self.CSHAKE_S).hash(
            self._parameter_block()+bytearray([0,purpose])+string,length=length)

    def _seed_to_matrix(self,seed):
        "Expand public key seed to a d*d matrix"
        d = self.d
        return [[
            self._decodeInteger(self._hash(0,seed+bytearray([i+j*d]),length=self.NBYTES_N))
            for j in range(d)]
            for i in range(d)]
            
    def _psi(self,byte):
        "Per-digit noise distribution"
        adj = int(self.VARIANCE*128)
        ret = 0
        while adj>64:
            ret += ((byte+64)>>8) + ((byte-64)>>8)
            byte = (byte<<2) & 0xFF
            adj -= 64
        ret += ((byte+adj)>>8) + ((byte-adj)>>8)
        return ret

    def _noise(self,why,seed,iv):
        "Sample from noise distribution"
        expanded = self._hash(why,seed+bytearray([iv]),length=self.D)
        return sum( self._psi(byte) << (self.LGX*i)
                    for i,byte in enumerate(expanded) )
    
    def keypair(self,ask):
        "Get pubkey from ask"
        if len(ask) != self.PRIVATE_KEY_BYTES: raise InvalidParameterException()
        seed = self._hash(1,ask,length=self.MATRIX_SEED_BYTES)
        d = self.d
        avec = [self._noise(1,ask,i  ) for i in range(d)]
        evec = [self._noise(1,ask,i+d) for i in range(d)]
        matr = self._seed_to_matrix(seed)
        pubvec = [ sum(a*m*self.CLAR for a,m in zip(avec,row)) + e
                   for e,row in zip(evec,matr) ]
        return seed + self._encodeVector(pubvec)
    
    def encapsulate(self,apk,seed,iv=bytearray()):
        "Encapsulate to public key apk; return (shared_secret,capsule)"
        if len(seed) != self.ENC_SEED_BYTES: raise InvalidParameterException()
        if len(iv) != self.IV_BYTES: raise InvalidParameterException()
        
        mseed = apk[:self.MATRIX_SEED_BYTES]
        hash_ctx = mseed + seed + iv
        
        nb = self.NBYTES_N
        d = self.d
        
        b_vector   = [self._noise(2,hash_ctx,i)   for i in range(d)]
        epsilon_b  = [self._noise(2,hash_ctx,i+d) for i in range(d)]
        epsilon_pr =  self._noise(2,hash_ctx,2*d)
        
        matrix = self._seed_to_matrix(mseed)
        matrix_transpose = [[matrix[i][j] for i in range(d)] for j in range(d)]
        bpk = self._encodeVector([
            sum(b*m*self.CLAR for b,m in zip(b_vector,row)) + e
              for e,row in zip(epsilon_b,matrix_transpose) ])
    
        apk_expanded = [self._decodeInteger(apk[i*nb+self.MATRIX_SEED_BYTES:(i+1)*nb+self.MATRIX_SEED_BYTES])
            for i in range(d)]
    
        c = sum(a*b for a,b in zip(b_vector,apk_expanded)) * self.CLAR + epsilon_pr
        c = c % self.N

        dem = _bitarray(self.ENCRYPTED_BITS*self.LPR_BITS)        
        if not self.CCA:
            seed = self._hash(2,hash_ctx,self.ENC_SEED_BYTES)
            hash_ctx = mseed + seed + iv
        if self.FEC_BITS: seed=Fec.append(seed)

        assert(self.LPR_BITS==4) # MAGIC
        sb = (byte >> j for byte in seed for j in xrange(8))
        for i,(lo,hi) in enumerate(zip(sb,sb)):
            if i >= len(dem): break
            lo_nib = (c >> (self.LGX*(i+1)-4)) + (lo<<3)
            hi_nib = (c >> (self.LGX*(self.D-i)-4)) + (hi<<3)
            dem[i] = (lo_nib & 0x0F) | (hi_nib<<4 & 0xF0)
        
        capsule = bpk + dem + iv
        return self._hash(2, hash_ctx, self.SHARED_SECRET_BYTES), capsule

    def decapsulate(self,ask,capsule,implicit=False):
        "Decrypt a capsule"
        nb = self.NBYTES_N
        d = self.d

        a_vector = [self._noise(1,ask,i) for i in range(d)]
        B_vector = [self._decodeInteger(capsule[i*nb:(i+1)*nb]) for i in range(d)]
        c = sum(a*bb for a,bb in zip(a_vector,B_vector))*self.CLAR % self.N

        assert(self.LPR_BITS==4) # MAGIC
        seed = _bitarray(self.ENCRYPTED_BITS)
        demlen = int(ceil(self.ENCRYPTED_BITS*self.LPR_BITS/8.))
        for i,byte in enumerate(capsule[nb*d:nb*d+demlen]):
            lo_ours = c >> (self.LGX*(i+1)-5)
            hi_ours = c >> (self.LGX*(self.D-i)-5)
            lo_delta = 2* byte     + 8 - lo_ours
            hi_delta = 2*(byte>>4) + 8 - hi_ours
            seed[i/4] |= ((lo_delta>>4 & 1) | (hi_delta>>3 & 2)) << ((2*i) % 8)
        
        if self.FEC_BITS: seed=Fec.correct(seed)
        iv = capsule[len(capsule)-self.IV_BYTES:]
        
        if self.CCA:
            apk = self.keypair(ask)
            shared_secret,capsule2 = self.encapsulate(apk,seed,iv)
            if capsule2 == capsule: return shared_secret
            elif implicit:
                prfk = self._hash(1,ask + bytearray([0xFF]),self.PRIVATE_KEY_BYTES)
                return self._hash(3,prfk+capsule,self.SHARED_SECRET_BYTES)
            else: raise InvalidCiphertextException("Re-encrypt failed")
        else:
            mseed = self._hash(1,ask,length=self.MATRIX_SEED_BYTES)
            return self._hash(2,mseed+seed+iv,self.SHARED_SECRET_BYTES)
    
    def __init__(self,name,variance,d,cca,useFec,IV_BYTES=0, D=312,lgx=10):
        "Create a ThreeBears instance with given parameters"
        # Parameter block
        self.VERSION = 1
        self.PRIVATE_KEY_BYTES   = 40
        self.MATRIX_SEED_BYTES   = 24
        self.ENC_SEED_BYTES = 32
        self.IV_BYTES = IV_BYTES
        self.TARGHI_UNRUH_BYTES  = 0
        self.SHARED_SECRET_BYTES = 32
        self.LGX = lgx
        self.D = D
        self.d = d
        self.VARIANCE = variance
        self.LPR_BITS = 4
        self.FEC_BITS = 18 if useFec else 0
        self.CCA = cca
        
        # Derived parameters
        self.x = 2**lgx
        self.N = self.x**D - self.x**(D//2) - 1
        self.NBYTES_N = int(ceil(lgx*D/8.))
        self.CLAR = self.x**(D//2) - 1
        self.ENCRYPTED_BITS = self.ENC_SEED_BYTES*8 + self.FEC_BITS
        
        self.NAME = name
        Bear._all.append(self)
    
BabyBearEphem = Bear("BabyBearEphem",  32.0/32, 2, False, True)
BabyBear      = Bear("BabyBear",       18.0/32, 2, True,  True)
MamaBearEphem = Bear("MamaBearEphem",  28.0/32, 3, False, True)
MamaBear      = Bear("MamaBear",       13.0/32, 3, True,  True)
PapaBearEphem = Bear("PapaBearEphem",  24.0/32, 4, False, True)
PapaBear      = Bear("PapaBear",       10.0/32, 4, True,  True)

if __name__ == "__main__":
    verbose = False
    for bear in Bear._all:
        n = 2
        passes = 0
        pada = bytearray(bear.PRIVATE_KEY_BYTES - bear.SHARED_SECRET_BYTES)
        padb = bytearray(bear.ENC_SEED_BYTES - bear.SHARED_SECRET_BYTES)
        ask = bytearray(bear.SHARED_SECRET_BYTES) + pada
        bsk_seed = bytearray(bear.SHARED_SECRET_BYTES) + padb
        try:
            for i in xrange(n):
                bsk_seed[0] ^= 1 # so it's different from Alice's seed
                apk = bear.keypair(ask)

                bob_secret, bpk = bear.encapsulate(apk,bsk_seed+padb,bytearray(bear.IV_BYTES))
                
                if bear.CCA and (i&1):
                    print _hex(bpk)
                    bpk[(i//8) % len(bpk)] ^= 1<<(i%8)
                    print _hex(bpk)
                    shouldfail = True
                else: shouldfail = False
                
                alice_secret = bear.decapsulate(ask,bpk,implicit=shouldfail)
                
                if (alice_secret == bob_secret) == (not shouldfail):
                    passes += 1

                if verbose:
                    print "Alice's public key:\n"
                    print _hex(apk)

                    print "\nAlice's private key:\n"
                    print _hex(ask)

                    print "\nBob's capsule:\n"
                    print _hex(bpk)

                    print "\nShared secret:\n"
                    print _hex(alice_secret)

                ask,bsk_seed = alice_secret+pada,bob_secret+padb
        except Exception as e:
            print "Caught",e,"!"
    
        print "%s: pass %d / %d trials\n   mc=%s\n" % \
            (bear.NAME, passes, n, _hex(ask))
