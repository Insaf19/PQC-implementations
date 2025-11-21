
# coding: utf-8

# In[12]:




# In[3]:

# Titanium parameter selection and evaluation script
# Ver. 3.0 (21 Nov 2017)
import sys;

orig_stdout = sys.stdout
f = open('Tit_pars_out.txt', 'w')
sys.stdout = f

#
# *** Part 1: Parameter Selection ***
# inputs: initial target values
R = RealField(256); # 256 bit precision reals
targn = R(620);
targk = R(255);
targm = R(1); # no of msg bits per mu coord
targd = R(ceil(256/targm));
targt = 10;
etabin = 4;
targcmp = 0;
mmargin = 30;

# error distribution std dev
sdchieq = R(sqrt(2*etabin/4));

# min/med/max quantum circuit MAXDEPTH assumptions
#log2MAXDEPTHmax = 96;
#log2MAXDEPTHmed = 64;
log2MAXDEPTHmin = 96;

# Scheme Safety margin goal ratios
# ** PLWE security ** 
# log2sec safety margin at the min of PLWE family degree range
log2secsafmarggoal = R(1.10); # quantum PLWE sec safety margin at mmid (middle dimension of family)
log2Csecsafmarggoal = R(1.05); # classical PLWE sec safety margin at mmid (middle dimension of family)
# ** LHL term **
log2LHLsafmarggoal = R(1.01);
# ** pe term **
log2pesafmarggoal = R(1.05);



# NIST cat-1/cat0/cat1/cat2/cat3/cat5 classical gate complexity goals
log2cat_1secClsgt = 79; # AES 64 classical number of gates complexity goal
log2cat0secClsgt = 111; # AES 96 classical number of gates complexity goal
log2cat1secClsgt = 143; # AES 128 classical number of gates complexity goal
log2cat2secClsgt = 175; # AES 160 classical number of gates complexity goal
log2cat3secClsgt = 207; # AES 192 classical number of gates complexity
log2cat5secClsgt = 272; # AES 256 classical number of gates complexity

def maxi(x,y) :
	if (x > y) :
		m = x;
	else :
		m = y;
	return m
																																																																																																																																										
# NIST cat-1/cat0/cat1/cat2/cat3/cat5 quantum gate complexity goals for min/med/max MAXDEPTH assumptions 
log2cat_1secmax = maxi(106-log2MAXDEPTHmin, 64/2+21); # AES 64 ("cat -1" max security target in No. of Quant. gates).
log2cat0secmax = maxi(138-log2MAXDEPTHmin, 96/2+21); # AES 96 ("cat 0" max security target in No. of Quant. gates).
log2cat1secmax = maxi(170-log2MAXDEPTHmin, 128/2+21); # AES 128 ("cat 1" max security target in No. of Quant. gates).
log2cat2secmax = maxi(202-log2MAXDEPTHmin, 160/2+21); # AES 128 ("cat 2" max security target in No. of Quant. gates).
log2cat3secmax = maxi(233-log2MAXDEPTHmin, 192/2+21); # AES 192 ("cat 3" max security target in No. of Quant. gates).
log2cat5secmax = maxi(298-log2MAXDEPTHmin, 256/2+21); # AES 256 ("cat 5" max security target in No. of Quant. gates).



# Selected category/level Goals
log2SelQsecgoal = log2cat_1secmax;
log2SelCsecgoal = log2cat_1secClsgt;

def mini(x,y) :
	if (x > y) :
		m = y;
	else :
		m = x;
	return m

# log_2(gate complexity) per G/H/XOF Random oracle call 
log2TRO = 15;
log2TQRO = 19;
DepthQRO = 2^13;
log2MAXDEPTHminprime = mini(log2MAXDEPTHmin,log2SelQsecgoal)
Q_d = 2^log2MAXDEPTHminprime/DepthQRO;



# Goals for scheme parameters (no additional safety margins)

log2Qsecgoal = R(log2SelQsecgoal + log(24)/log(2)); # add (classical) security reductions factor
log2Csecgoal = R(log2SelCsecgoal + log(24)/log(2)); # add (classical) reduction cost factor
log2DeltaLHLgoal = -R(log2SelCsecgoal + log(24)/log(2)); # add (classical) reduction cost factor
log2pegoal = mini(log2TRO-2-R(log2SelCsecgoal),log2TQRO-5-R(log(Q_d)/log(2))-R(log2SelQsecgoal)); # add (classical) reduction cost factor


# Goals for scheme parameters (with additional safety margins)
# ** PLWE security ** 
log2Qsecgoalsafe = log2secsafmarggoal*log2Qsecgoal; 
log2Csecgoalsafe = log2Csecsafmarggoal*log2Csecgoal; 
# ** LHL term **
log2DeltaLHLgoalsafe = log2LHLsafmarggoal*log2DeltaLHLgoal; 
# ** pe term **
log2pegoalsafe = log2pesafmarggoal*log2pegoal; 

# Estimated correctenss zpe
# z(pe)
zpe = R(sqrt(2*log(2)*(-log2pegoalsafe + log(2*targd)/log(2))));
 
# find by bisection smallest Bc such that tLHK(Bc) < t - 0.01
Bclo = R(8);
Bchi = R(2^40);
epsterm = R(2^(-32));
targ = R(targt-0.001);

while (Bchi > (Bclo + epsterm)) :
	Bcnew = (Bclo + Bchi)/2;
	lnew = floor(log(Bcnew)/log(2));
	l2new = lnew + 1;
	rhonew = (2^(2*l2new) - Bcnew^2)/(2^(2*l2new)-2^(2*lnew));
	BLnew = 2^(lnew*rhonew)*2^(l2new*(1-rhonew));
	qnew = 1.03*2*2^(targm)*zpe*sqrt(Bcnew^2/12+Bcnew/4+1/6)*sdchieq*sqrt((targk+1)*targt);
	tLOnew = R((2*(-log2DeltaLHLgoalsafe-1) + (targn+targk+targd)*log(qnew)/log(2))/((targk+1)*log(BLnew)/log(2)));
	if (tLOnew < targ) :
		Bchi = Bcnew;
	else :
		Bclo = Bcnew;

pklen = floor(R((targk+targd)*targt*log(qnew)/log(2)))+1;
ctxtlen = floor(R((targn+targk+targd)*log(qnew)/log(2)))+1;

print("Given Parameter values:");
print("n"); print(targn);
print("k"); print(targk);
print("d"); print(targd);
print("m"); print(targm);
print("t"); print(targt);
print("etabin"); print(etabin);
print("sdchieq"); print(sdchieq);

print("Given Eval Goals (without additional safety margin):");
print("log2Qsecgoal"); print(log2Qsecgoal);
print("log2Csecgoal"); print(log2Csecgoal); 
print("log2DeltaLHLgoal"); print(log2DeltaLHLgoal);  
print("log2pegoal"); print(log2pegoal);  

# safety margin goals
print("Safety margin ratio goals:");
print("log2secsafmarggoal"); print(log2secsafmarggoal); 
print("log2Csecsafmarggoal"); print(log2Csecsafmarggoal);
print("log2LHLsafmarggoal"); print(log2LHLsafmarggoal); 
print("log2pesafmarggoal"); print(log2pesafmarggoal);

# Goals for scheme parameters (with additional safety margins)
print("Given Eval Goals (without additional safety margin):");
print("log2Qsecgoalsafe"); print(log2Qsecgoalsafe);
print("log2Csecgoalsafe"); print(log2Csecgoalsafe); 
print("log2DeltaLHLgoalsafe"); print(log2DeltaLHLgoalsafe);  
print("log2pegoalsafe"); print(log2pegoalsafe);  
  

print("pre-NTT Optimization Results:");
print("zpe"); print(zpe);
print("Bchi"); print(Bchi);
print("Bclo"); print(Bclo);
print("Bchi"); print(Bchi);
print("lnew"); print(lnew);
print("l2new"); print(l2new);
print("rhonew"); print(rhonew);
print("qnew"); print(qnew);
print("log2qnew"); print(R(log(qnew)/log(2)));
print("tLOnew"); print(tLOnew);
print("pk len"); print(pklen);
print("ctxt len"); print(ctxtlen);

# add NTT and primality constraints: find a suitable prime q and print out exact value
# NTT dimensions:
dCT = 256; # Cooley Tukey dimension factor
# find bet1 : smallest integer such that D1 = bet1*dCT >= d+k
bet1 = Integer(ceil((targd+targk)/dCT));
D1 = bet1 * dCT;
# find bet2 : smallest integer such that D2 = bet2*dCT >= n+k
bet2 = Integer(ceil((targn+targk)/dCT));
D2 = bet2 * dCT;
# find bet3 : smallest integer such that D3 = bet3*dCT >= n+d+k
bet3 = Integer(ceil((targn+targd+targk)/dCT));
D3 = bet3 * dCT;
# Find prime q = 1 mod (lc*dCT) closest to qnew
lc = lcm(bet1,bet2);
lc = lcm(lc,bet3);


gam0 = Integer(round((qnew-1)/(lc*dCT)));
delt = 0;
sgn = 1; 
qntt = 1 + gam0*lc*dCT;

# search up for qntt
while not(is_prime(qntt)) :
	delt = delt + 1;
	gam = gam0 + sgn*delt;
	qntt = Integer(1 + gam*lc*dCT);


#while not(is_prime(qntt)) :
#	if (sgn < 0) :
#		sgn = 1;
#		delt = delt + 1;
#	else :
#	   sgn = -1;
#	gam = gam0 + sgn*delt;
#	qntt = Integer(1 + gam*lc*dCT);
#	if (qntt < 0) : 
#		qntt = (-1)*qntt;

# force qntt
#qntt = 118273

# adjustment: find by bisection smallest Bc such that tLHK(Bc) < t - 0.01 for the qntt
Bclo = R(8);
Bchi = R(2^40);
epsterm = R(2^(-32));
targ = R(targt-0.01);

while (Bchi > (Bclo + epsterm)) :
	Bcnew = (Bclo + Bchi)/2;
	lnew = floor(log(Bcnew)/log(2));
	l2new = lnew + 1;
	rhonew = (2^(2*l2new) - Bcnew^2)/(2^(2*l2new)-2^(2*lnew));
	BLnew = 2^(lnew*rhonew)*2^(l2new*(1-rhonew));
	tLOnew = R((2*(-log2DeltaLHLgoalsafe-1) + (targn+targk+targd)*log(qntt)/log(2))/((targk+1)*log(BLnew)/log(2)));
	if (tLOnew < targ) :
		Bchi = Bcnew;
	else :
		Bclo = Bcnew;

pklen = R((targk+targd)*targt*log(qntt)/log(2));
ctxtlen = R((targn+targk+targd)*log(qntt)/log(2));
# z(pe)
lnew = floor(log(Bchi)/log(2));
l2new = lnew + 1;
Beffc = sqrt(2^(2*lnew)*rhonew+2^(2*l2new)*(1-rhonew));
chirsdeff = R(sqrt((Beffc)^2/12 + Beffc/4 + 1/6));
zpentt = (qntt-1)/( 1.01*2*2^(targm)*chirsdeff*sdchieq*sqrt((targk+1)*targt) ); 
lg2pentt = (-zpentt^2/2)/log(2) + log(2*targd)/log(2);
# ((q-1)/2^(ms+1))/(chirsdeff*sdchieq*sqrt(Ndec))

print("post-NTT results:");
print("NTT-compatible q found: qntt"); print(qntt);
print("log2qntt"); print(R(log(qntt)/log(2)));
print("NTT dimensions:");
print("D1"); print(D1);
print("bet1"); print(bet1);
print("D2"); print(D2);
print("bet2"); print(bet2);
print("D3"); print(D3);
print("bet3"); print(bet3);
print("lc"); print(lc);
print("n"); print(targn);
print("k"); print(targk);
print("d"); print(targd);
print("m"); print(targm);
print("sdchieq"); print(sdchieq);
print("t"); print(targt);
print("log2pegoal"); print(log2pegoal);
#
#
print("zpentt"); print(zpentt);
print("Bchi"); print(Bchi);
print("Bclo"); print(Bclo);
print("Bchi"); print(Bchi);
print("lnew"); print(lnew);
print("l2new"); print(l2new);
print("rhonew"); print(rhonew);
print("qntt"); print(qntt);
print("log2qntt"); print(R(log(qntt)/log(2)));
print("tLOnew"); print(tLOnew);
print("pk len"); print(pklen);
print("ctxt len"); print(ctxtlen);
print("lg2pentt"); print(R(lg2pentt));

#print("target log2cat1secmin"); print(log2cat1secmin);
#print("target log2cat1secmed"); print(log2cat1secmed);
#print("target log2cat1secmax"); print(log2cat1secmax);
#print("target log2cat3secmin"); print(log2cat3secmin);
#print("target log2cat3secmed"); print(log2cat3secmed);
#print("target log2cat3secmax"); print(log2cat3secmax);
#print("target log2cat5secmin"); print(log2cat5secmin);
#print("target log2cat5secmed"); print(log2cat5secmed);
#print("target log2cat5secmax"); print(log2cat5secmax);

print("Computing Parameter Eval...");

# *** Part 2: Parameter Evaluation ***

# define scheme parameters for eval functions
n = R(targn);
k = R(targk);
t = R(targt);
ms = R(targm); # msg bits per coord
d = R(256/ms);
q = qntt;
cmp = targcmp;
B = Integer(2^(lnew)); # b1 = lnew - 1 , 
B2 = Integer(2*B); # b2 = lnew
# fraction of B coordinates over all ris, remaining are B2
rho = rhonew;
# number of r_i*e_i terms in each decryption error coordinate
Ndec = (k+1)*t;
# Number of B coordinates over all ris, remaining Ndec-Ndec1 are B2
Ndec1  = round(rho*(k+1)*t) - (round(rho*(k+1)*t) % 8);
# max error coordinate absolute value for correct decryption 
tdec = (q-1)/2^(ms+1)-2^(cmp);
mmin = n-mmargin;
etabin = etabin;

# define error distribution: chi_e = BinDiff(etabin)
# etabin = binomial number of Bernoulli samples parameter (std dev parameter)
pbin = R(1/2); # binomial Bernoulli bias parameter
# domain abs value max 
De = Integer(etabin); 
# prob. distribution table
# high precision probability mass function table (positive side only, prob. of both plus and minus x)
chieq = range(0,De+1);
chieq[0] = R(0);
for x in [0..De] :	
	chieq[0] = R(chieq[0]) + (binomial(etabin,x)*R(pbin)^(x)*R(1-pbin)^(etabin-x))^2; 
for x in [1..De] :
	chieq[x] = R(0);
	for xp in [0..De] :
		chieq[x] = R(chieq[x]) + 2*(binomial(etabin,xp)*R(pbin)^(xp)*R(1-pbin)^(etabin-xp)) * (binomial(etabin,x+xp)*R(pbin)^(x+xp)*R(1-pbin)^(etabin-(x+xp)));

# variance and std. dev. of chieq
varchieq = R(0);
for x in [0..De] :	
	varchieq = varchieq + R(chieq[x])*R(x)^2;
sdchieq  = sqrt(varchieq);

print("Binomial chie " ); print(chieq);
print("param: etabin "); print(etabin);
print("param: pbin "); print(pbin);
print("chie std dev "); print(sdchieq);


# define randomness distribution: chir (used for a fraction rho of r_i coeffs)
# uniform on (-B/2,B/2) WITHOUT 0 (positive side only, prob. of both plus and minus)
chir = [1..(B/2+1)];
sum = 0;
chir[0]=R(0);
for x in [1..B/2] :	
	chir[x] = R(2/B);
	sum = sum + chir[x];
# compute min-entropy minentchir of chir
minentchir = R(log(B)/log(2));
print("minentchir "); print(minentchir);

# define randomness distribution 2: chir2 (used for a fraction 1-rho of r_i coeffs)
# uniform on (-B2/2,B2/2) WITHOUT 0 (positive side only, prob. of both plus and minus)
chir2 = [1..(B2/2+1)];
sum = 0;
chir2[0]=R(0);
for x in [1..B2/2] :	
	chir2[x] = R(2/B2);
	sum = sum + chir2[x];
# compute min-entropy minentchir2 of chir2
minentchir2 = R(log(B2)/log(2));
print("minentchir2 "); print(minentchir2);

# compute mean min-entropy of r_i's per coordinate
meanminent = R(Ndec1/Ndec)*minentchir + R(1-Ndec1/Ndec)*minentchir2; 
print("meanminent "); print(meanminent);


# compute chire product distribution per coordinate (positive side only, prob, of both plus and minus)
chire = [1..(De*(B/2)+1)];
for x in [0..De*(B/2)] :
	chire[x] = R(0);
	for y in [1..B/2] :
	        if ( ((x % y) == 0) and ( (x/y) <= De ) ) :
			chire[x] = chire[x] + chir[y]*R(chieq[Integer(round(x/y))]); 
chire[0] = R(chir[0]) + R(1-chir[0])*R(chieq[0]);

#De =1;
#chire = [1..(B/2+1)];
#sum = 0;
#chire[0]=0;
#for x in [1..B/2] :	
#	chire[x] = 2*R(1/B);
#	sum = sum + chire[x];



# compute variance of chire
varchire = R(0);
D = De*(B/2); # support max value for chire
for x in [0..D] :
	varchire = varchire + R(x)^2*chire[x];


# compute chire2 product distribution per coordinate (positive side only, prob, of both plus and minus)
chire2 = [1..(De*(B2/2)+1)];
for x in [0..De*(B2/2)] :
	chire2[x] = R(0);
	for y in [1..B2/2] :
	        if ( ((x % y) == 0) and ( (x/y) <= De ) ) :
			chire2[x] = chire2[x] + chir2[y]*R(chieq[Integer(round(x/y))]); 
chire2[0] = R(chir2[0]) + R(1-chir2[0])*R(chieq[0]);

# compute variance of chire2
varchire2 = R(0);
Dr = De*(B2/2); # support max value for chire
for x in [0..Dr] :
	varchire2 = varchire2 + R(x)^2*chire2[x];


# numerical Hoeffding decryption error probability bound

# MomGF(chire,s,D): returns value of moment gen. function (MGF) of distrib. chire at s.
# Assumes chire is symmetric about 0 with prob(x) + prob(-x) = chire(x) for 0 < x <= D, prob(0)=chire(0).
# D is the largest positive x in support of chire
def MomGF(chire,s,D) :
	mgf = R(chire[0]);
	for x in [1..D] :
		mgf = mgf + R((chire[x]/2)*(exp(s*x)+exp(-s*x)));
	return mgf

# DerMomGF(chire,s,D): returns value of first derivative of moment gen. function (MGF) of distrib. chire at s.
# Assumes chire is symmetric about 0 with prob(x) + prob(-x) = chire(x) for 0 < x <= D, prob(0)=chire(0).
# D is the largest positive x in support of chire
def DerMomGF(chire,s,D) :
	dermgf = R(0);
	for x in [1..D] :
		dermgf = dermgf + R((chire[x]/2)*x*(exp(s*x)-exp(-s*x)));
	return dermgf

# do a bisection search for shoff such that Hoffding pe bound, phoff(shoff) = MomGF(chire,shoff,D)^(Ndec1) * MomGF(chire2,shoff,D)^(Ndec-Ndec1)/exp(shoff*tdec), is minimized
# shoff satisfies phoff'(shoff) = 0, i.e. g(shoff) = (Ndec1/Ndec)*DerMomGF(chire,shoff,D)/MomGF(chire,shoff,D) + ((Ndec-Ndec1)/Ndec)*DerMomGF(chire2,shoff,D2)/MomGF(chire2,shoff,D2) = tdec/Ndec.
# Bisection search on g searches for shoff satisfying latter condition. 
shofflo = R(0);
shoffhi = R(30);
epsterm = R(2^(-32));
targ = R(tdec/Ndec);

while (shoffhi > (shofflo + epsterm)) :
	shoffnew = (shofflo + shoffhi)/2;
	gvalnew = R(Ndec1/Ndec)*R(DerMomGF(chire,shoffnew,D)/MomGF(chire,shoffnew,D)) + R((Ndec-Ndec1)/Ndec)*R(DerMomGF(chire2,shoffnew,Dr)/MomGF(chire2,shoffnew,Dr));
	if (gvalnew > targ) :
		shoffhi = shoffnew;
	else :
		shofflo = shoffnew;
# compute Hoffding bound on pe at optimal shoff
mgfhoff = R(MomGF(chire,shoffhi,D));
mgfhoff2 = R(MomGF(chire2,shoffhi,Dr));
log2mgfhoff = R(log(mgfhoff)/log(2));
log2mgfhoff2 = R(log(mgfhoff2)/log(2));
pehoff = R(2*d*mgfhoff^(Ndec1)*mgfhoff2^(Ndec-Ndec1)/exp(shoffhi*tdec));
log2pehoff = R(log(pehoff)/log(2));


print("finished bisection search for shoff up to tolerance "); print(epsterm);
print("shofflo " ) ; print(shofflo);
print("shoffhi " ); print(shoffhi);
print("tdec " ); print(tdec);
print("Ndec " ); print(Ndec);
print("Ndec1 " ); print(Ndec1);
print("log2mgfhoff " ); print(log2mgfhoff);
print("log2mgfhoff2 " ); print(log2mgfhoff2);
print("pehoff " ); print(pehoff);
print("log2pehoff " ); print(log2pehoff);

# LHL lower bound condition on t
print("LHL lower bound on t");
tlo = ( 2*(-R(log2DeltaLHLgoalsafe)-1) + R((n+d+k)*log(q)/R(log(2))) ) / ((k+1)*meanminent);
print("tlo " ); print(tlo);
# LHL log(1/Delta_LHL) achieved with actual t and B, B2, Ndec1 pars
DeltaLHLAch =  0.5 * ( R(B)^(-Ndec1) * R(B2)^(-(Ndec-Ndec1)) * R(q)^(n+d+k) )^(0.5);
log2DeltaLHLAch = R(log(DeltaLHLAch)/log(2)); 


# complexity estimate of PLWE security against BKZ attacks 
# core SVP hardness approach

# Tbkz(b): returns time estimate for Quantum sieve SVP BKZ with block size b
def Tbkz(b) :
	# constants
	cQ = R(0.265) ; # quantum SVP sieve hypercone filtering exponent constant (Laarhoven et al, 2015).

	Tb = R(2^(cQ * b));

	return Tb

# TCbkz(b): returns time estimate for Classical sieve SVP BKZ with block size b
def TCbkz(b) :
	# constants
	cQ = R(0.292) ; # classical SVP sieve hypercone filtering exponent constant (Laarhoven et al, 2015).

	Tb = R(2^(cQ * b));

	return Tb



# deltbkz(b): returns Hermite Factor estimate for BKZ with block size b
# assumes GSA model for GSO of BKZ output vector lengths (Schnorr, 2003)
def deltbkz(b) :

	bp = R(b / (2*pi*exp(1)));
	ex = R(1/(2*(b-1)));
	delt = R( bp * (pi*b)^(1/b) )^(ex);

	return delt


# LWEdualatk(dp,q,b,alpha): returns parameters of optimized dimension LWE dual lattice attack
# against LWE in dim. dp, modulus q, assuming BKZ block size b, LWE noise parameter alpha
# returns:
#   voptlen = Euclidean length of BKZ output vector vopt in dual lattice
#   mopt = optimum number of LWE samples for dual attack
#   tauopt = voptlen*alpha (sd of Gaussian in distinguishing attack)
#   epsopt = upper bound on optimal attack distinguishing advantage
def LWEdualatk(dp,q,b,alpha) :

	voptlen = R(deltbkz(b)^(-1) * 2^(2*sqrt(dp*log(q)/log(2)*log(deltbkz(b))/log(2))));
	mopt = R(sqrt( (dp*log(q)/log(2))/(log(deltbkz(b))/log(2)) ));
	tauopt = R(voptlen * alpha);
	epsopt = R(4 * exp(-2*pi^2*tauopt^2));	

	return voptlen, mopt, tauopt, epsopt


# LWEdualComplexMinTHighAdv(dp,q,alpha): returns quantum CoreSVP complexity of LWE dual lattice BKZ attack
# New Hope approach: Choose BKZ block size b to minimize Run-time for high advantage distinguisher, 
# assume each BKZ run gives Tbkz indep. short vectors in dual
# attack against LWE in dim. dp, modulus q, assuming BKZ block size b, LWE noise parameter alpha
# returns:
#   boptlo = lo bnd on optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
#   bopthi = hi bnd on optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
#   logToptlo = lo bnd on log(Tbkz(bopt)), base 2.
#   logTopthi = hi bnd on log(Tbkz(bopt)), base 2. 
def LWEdualComplexMinTHighAdv(dp,q,alpha) :

	# Bisection search on b to find optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
	boptlo = R(40);
	bopthi = R(1500);
	epsterm = R(2^(-32));

#	out = file('newloop.txt','w');
#	out.write(str("new loop iters:")+'\n');
	while (bopthi > (boptlo + epsterm)) :
#		out.write("start of iteration"+'\n');
#		out.write("boptlo"); out.write(str(boptlo)+'\n');
#		out.write("bopthi"); out.write(str(bopthi)+'\n');

		boptnew = (boptlo + bopthi)/2;
		logTbkznew = log(Tbkz(boptnew))/log(2);
		voptlen, mopt, tauopt, epsopt = LWEdualatk(dp,q,boptnew,alpha) 
		loginvepssq = log(1/epsopt^2)/log(2);
		if (logTbkznew > loginvepssq) :
			bopthi = boptnew;
		else :
			boptlo = boptnew;
#		out.write("end of iteration");
#		out.write("boptnew"); out.write(str(boptnew)+'\n');
#		out.write("logTbkznew"); out.write(str(logTbkznew)+'\n');
#		out.write("voptlen, mopt, tauopt, epsopt"); out.write(str(voptlen)+'\n'+str(mopt)+'\n'+str(tauopt)+'\n'+str(epsopt)+'\n');
#		out.write("loginvepssq"); out.write(str(loginvepssq)+'\n');

#	out.close();


	logToptlo = log(Tbkz(boptlo))/R(log(2));
	logTopthi = log(Tbkz(bopthi))/R(log(2));
	voptlenlo, moptlo, tauoptlo, epsoptlo = LWEdualatk(dp,q,boptlo,alpha) 
	voptlenhi, mopthi, tauopthi, epsopthi = LWEdualatk(dp,q,bopthi,alpha) 

	return boptlo, bopthi, logToptlo, logTopthi, voptlenlo, moptlo, tauoptlo, epsoptlo, voptlenhi, mopthi, tauopthi, epsopthi


# LWECdualComplexMinTHighAdv(dp,q,alpha): returns classical CoreSVP complexity of LWE dual lattice BKZ attack
# New Hope approach: Choose BKZ block size b to minimize Run-time for high advantage distinguisher, 
# assume each BKZ run gives Tbkz indep. short vectors in dual
# attack against LWE in dim. dp, modulus q, assuming BKZ block size b, LWE noise parameter alpha
# returns:
#   boptlo = lo bnd on optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
#   bopthi = hi bnd on optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
#   logToptlo = lo bnd on log(Tbkz(bopt)), base 2.
#   logTopthi = hi bnd on log(Tbkz(bopt)), base 2. 
def LWECdualComplexMinTHighAdv(dp,q,alpha) :

	# Bisection search on b to find optimal b satisfying Tbkz(b) ~ 1/epsopt^2(b)
	boptlo = R(40);
	bopthi = R(1500);
	epsterm = R(2^(-32));

	while (bopthi > (boptlo + epsterm)) :
		boptnew = (boptlo + bopthi)/2;
		logTbkznew = log(TCbkz(boptnew))/log(2);
		voptlen, mopt, tauopt, epsopt = LWEdualatk(dp,q,boptnew,alpha) 
		loginvepssq = log(1/epsopt^2)/log(2);
		if (logTbkznew > loginvepssq) :
			bopthi = boptnew;
		else :
			boptlo = boptnew;

	logToptlo = log(TCbkz(boptlo))/R(log(2));
	logTopthi = log(TCbkz(bopthi))/R(log(2));
	voptlenlo, moptlo, tauoptlo, epsoptlo = LWEdualatk(dp,q,boptlo,alpha) 
	voptlenhi, mopthi, tauopthi, epsopthi = LWEdualatk(dp,q,bopthi,alpha) 

	return boptlo, bopthi, logToptlo, logTopthi, voptlenlo, moptlo, tauoptlo, epsoptlo, voptlenhi, mopthi, tauopthi, epsopthi



# LWEdualComplexMinTtoAdvRatio(dp,q,alpha): returns quantum CoreSVP complexity of LWE dual lattice BKZ attack
# Modified New Hope approach: Choose BKZ block size b to minimize Run-time / advantage ratio of distinguisher, 
# assume each BKZ run gives Tbkz indep. short vectors in dual, therefore amplifying adv. by sqrt{Tbkz} factor
# attack against LWE in dim. dp, modulus q, assuming BKZ block size b, LWE noise parameter alpha
# returns:
#   boptlo = lo bnd on optimal b 
#   bopthi = hi bnd on optimal b 
#   logToptlo = lo bnd on log(Tbkz(bopt)), base 2.
#   logTopthi = hi bnd on log(Tbkz(bopt)), base 2. 
def LWEdualComplexMinTtoAdvRatio(dp,q,alpha,bmax) :

	# Bisection search on b to find optimal b minimizing T/eps ratio
	boptlo = R(40);
	bopthi = R(bmax);
	epsterm = R(1);
	epsder = R(0.1);

	while (bopthi > (boptlo + epsterm)) :
		boptnew = (boptlo + bopthi)/2;
		boptnewp = boptnew + epsder; # derivative estimation
		logTbkznew = R(log(Tbkz(boptnew))/log(2));
		voptlen, mopt, tauopt, epsopt = LWEdualatk(dp,q,boptnew,alpha) 
		loginveps = R(log(1/epsopt)/log(2));
		logTbkznewp = R(log(Tbkz(boptnewp))/log(2));
		voptlenp, moptp, tauoptp, epsoptp = LWEdualatk(dp,q,boptnewp,alpha) 
		loginvepsp= R(log(1/epsoptp)/log(2));
		dernew = (0.5*logTbkznewp + loginvepsp - (0.5*logTbkznew + loginveps)); 

		if (dernew > 0) :
			bopthi = boptnew;
		else :
			boptlo = boptnew;

	logToptlo = R(log(Tbkz(boptlo))/R(log(2)));
	logTopthi = R(log(Tbkz(bopthi))/R(log(2)));
	voptlenlo, moptlo, tauoptlo, epsoptlo = LWEdualatk(dp,q,boptlo,alpha)
	voptlenhi, mopthi, tauopthi, epsopthi = LWEdualatk(dp,q,bopthi,alpha) 

	return boptlo, bopthi, logToptlo, logTopthi, voptlenlo, moptlo, tauoptlo, epsoptlo, voptlenhi, mopthi, tauopthi, epsopthi


# LWECdualComplexMinTtoAdvRatio(dp,q,alpha,bmax): returns classical CoreSVP complexity of LWE dual lattice BKZ attack
# Modified New Hope approach: Choose BKZ block size b to minimize Run-time / advantage ratio of distinguisher, 
# assume each BKZ run gives Tbkz indep. short vectors in dual, therefore amplifying adv. by sqrt{Tbkz} factor
# attack against LWE in dim. dp, modulus q, assuming BKZ block size b, LWE noise parameter alpha
# returns:
#   boptlo = lo bnd on optimal b 
#   bopthi = hi bnd on optimal b 
#   logToptlo = lo bnd on log(Tbkz(bopt)), base 2.
#   logTopthi = hi bnd on log(Tbkz(bopt)), base 2. 
def LWECdualComplexMinTtoAdvRatio(dp,q,alpha,bmax) :

	# Bisection search on b to find optimal b minimizing T/eps ratio
	boptlo = R(40);
	bopthi = R(bmax);
	epsterm = R(1);
	epsder = R(0.1);

	while (bopthi > (boptlo + epsterm)) :
		boptnew = (boptlo + bopthi)/2;
		boptnewp = boptnew + epsder; # derivative estimation
		logTbkznew = R(log(TCbkz(boptnew))/log(2));
		voptlen, mopt, tauopt, epsopt = LWEdualatk(dp,q,boptnew,alpha) 
		loginveps = R(log(1/epsopt)/log(2));
		logTbkznewp = R(log(TCbkz(boptnewp))/log(2));
		voptlenp, moptp, tauoptp, epsoptp = LWEdualatk(dp,q,boptnewp,alpha) 
		loginvepsp= R(log(1/epsoptp)/log(2));
		dernew = (0.5*logTbkznewp + loginvepsp - (0.5*logTbkznew + loginveps)); 

		if (dernew > 0) :
			bopthi = boptnew;
		else :
			boptlo = boptnew;

	logToptlo = R(log(TCbkz(boptlo))/R(log(2)));
	logTopthi = R(log(TCbkz(bopthi))/R(log(2)));
	voptlenlo, moptlo, tauoptlo, epsoptlo = LWEdualatk(dp,q,boptlo,alpha)
	voptlenhi, mopthi, tauopthi, epsopthi = LWEdualatk(dp,q,bopthi,alpha) 

	return boptlo, bopthi, logToptlo, logTopthi, voptlenlo, moptlo, tauoptlo, epsoptlo, voptlenhi, mopthi, tauopthi, epsopthi




# PLWE distinguishing attack complexity estimates

# MAX FAMILY DIMENSION m = n SECURITY ESTIMATES
m = n; # max PLWE dimension
alpha = R(sdchieq)/R(q); # LWE alpha parameter (in terms of noise standard deviation).

# compute quantum complexity 1 of PLWE dist. attack: min T for high advantage
print("Running PLWE estimate 1, inputs:");
print("m"); print(m);
print("q"); print(q);
print("alpha"); print(alpha);
boptloHAdv, bopthiHAdv, logToptloHAdv, logTopthiHAdv, voptlenloHA, moptloHA, tauoptloHA, epsoptloHA, voptlenhiHA, mopthiHA, tauopthiHA, epsopthiHA = LWEdualComplexMinTHighAdv(m,q,alpha);

print("Complexity quantum estimate 1 for PLWE dist. attack: min T for high advantage:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdv " ) ; print(boptloHAdv);
print("bopthiHAdv " ) ; print(bopthiHAdv);
print("logToptloHAdv " ) ; print(logToptloHAdv);
print("logTopthiHAdv " ) ; print(logTopthiHAdv);
print("loginvepssqloHAdv " ) ; print(R(log(1/epsoptloHA^2)/R(log(2))));
print("loginvepssqhiHAdv " ) ; print(R(log(1/epsopthiHA^2)/R(log(2))));
print("voptlenloHA " ) ; print(voptlenloHA);
print("voptlenhiHA " ) ; print(voptlenhiHA);
print("moptloHA " ) ; print(moptloHA);
print("mopthiHA " ) ; print(mopthiHA);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHA " ) ; print(tauoptloHA);
print("tauopthiHA " ) ; print(tauopthiHA);
log2THAmaxm = logToptloHAdv;

# compute quantum complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRat, bopthiRat, logToptloRat, logTopthiRat, voptlenloRat, moptloRat, tauoptloRat, epsoptloRat, voptlenhiRat, mopthiRat, tauopthiRat, epsopthiRat = LWEdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdv);

print("Complexity quantum estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRat " ) ; print(boptloRat);
print("bopthiRat " ) ; print(bopthiRat);
print("logToptloRat " ) ; print(logToptloRat);
print("logTopthiRat " ) ; print(logTopthiRat);
print("loginvepsloRat " ) ; print(R(log(1/epsoptloRat)/R(log(2))));
print("loginvepshiRat " ) ; print(R(log(1/epsopthiRat)/R(log(2))));
print("log(sqrt(ToptloRat)/epsloRat) " ) ; print(0.5*logToptloRat+R(log(1/epsoptloRat)/R(log(2))));
print("log(sqrt(TopthiRat)/epshiRat) " ) ; print(0.5*logTopthiRat+R(log(1/epsopthiRat)/R(log(2))));
print("voptlenloRat " ) ; print(voptlenloRat);
print("voptlenhiRat " ) ; print(voptlenhiRat);
print("moptloRat " ) ; print(moptloRat);
print("mopthiRat " ) ; print(mopthiRat);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRat " ) ; print(tauoptloRat);
print("tauopthiRat " ) ; print(tauopthiRat);
log2Tepsmaxm = logToptloRat;


# compute classical complexity 1 of PLWE dist. attack: min T for high advantage
boptloHAdvC, bopthiHAdvC, logToptloHAdvC, logTopthiHAdvC, voptlenloHAC, moptloHAC, tauoptloHAC, epsoptloHAC, voptlenhiHAC, mopthiHAC, tauopthiHAC, epsopthiHAC = LWECdualComplexMinTHighAdv(m,q,alpha);

print("Complexity classical estimate 1 for PLWE dist. attack: min T for high advantage:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdvC " ) ; print(boptloHAdvC);
print("bopthiHAdvC " ) ; print(bopthiHAdvC);
print("logToptloHAdvC " ) ; print(logToptloHAdvC);
print("logTopthiHAdvC " ) ; print(logTopthiHAdvC);
print("loginvepssqloHAdvC " ) ; print(R(log(1/epsoptloHAC^2)/R(log(2))));
print("loginvepssqhiHAdvC " ) ; print(R(log(1/epsopthiHAC^2)/R(log(2))));
print("voptlenloHAC " ) ; print(voptlenloHAC);
print("voptlenhiHAC " ) ; print(voptlenhiHAC);
print("moptloHAC " ) ; print(moptloHAC);
print("mopthiHAC " ) ; print(mopthiHAC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHAC " ) ; print(tauoptloHAC);
print("tauopthiHAC " ) ; print(tauopthiHAC);
log2THAmaxmC = logToptloHAdvC;


# compute Classical complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRatC, bopthiRatC, logToptloRatC, logTopthiRatC, voptlenloRatC, moptloRatC, tauoptloRatC, epsoptloRatC, voptlenhiRatC, mopthiRatC, tauopthiRatC, epsopthiRatC = LWECdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdvC);

print("Complexity classical estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRatC " ) ; print(boptloRatC);
print("bopthiRatC " ) ; print(bopthiRatC);
print("logToptloRatC " ) ; print(logToptloRatC);
print("logTopthiRatC " ) ; print(logTopthiRatC);
print("loginvepsloRatC " ) ; print(R(log(1/epsoptloRatC)/R(log(2))));
print("loginvepshiRatC " ) ; print(R(log(1/epsopthiRatC)/R(log(2))));
print("log(sqrt(ToptloRatC)/epsloRatC) " ) ; print(0.5*logToptloRatC+R(log(1/epsoptloRatC)/R(log(2))));
print("log(sqrt(TopthiRatC)/epshiRatC) " ) ; print(0.5*logTopthiRatC+R(log(1/epsopthiRatC)/R(log(2))));
print("voptlenloRatC " ) ; print(voptlenloRatC);
print("voptlenhiRatC " ) ; print(voptlenhiRatC);
print("moptloRatC " ) ; print(moptloRatC);
print("mopthiRatC " ) ; print(mopthiRatC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRatC " ) ; print(tauoptloRatC);
print("tauopthiRatC " ) ; print(tauopthiRatC);
log2TepsmaxmC = logToptloRatC;

# MIDDLE FAMILY DIMENSION m= (n+mmin)/2 SECURITY ESTIMATES
m = (n+mmin)/2; # MID PLWE dimension
alpha = R(sdchieq)/R(q); # LWE alpha parameter (in terms of noise standard deviation).

# compute quantum complexity 1 of PLWE dist. attack: min T for high advantage
print("Running PLWE estimate 1, inputs:");
print("m"); print(m);
print("q"); print(q);
print("alpha"); print(alpha);
boptloHAdv, bopthiHAdv, logToptloHAdv, logTopthiHAdv, voptlenloHA, moptloHA, tauoptloHA, epsoptloHA, voptlenhiHA, mopthiHA, tauopthiHA, epsopthiHA = LWEdualComplexMinTHighAdv(m,q,alpha);

print("Complexity quantum estimate 1 for PLWE dist. attack: min T for high advantage:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdv " ) ; print(boptloHAdv);
print("bopthiHAdv " ) ; print(bopthiHAdv);
print("logToptloHAdv " ) ; print(logToptloHAdv);
print("logTopthiHAdv " ) ; print(logTopthiHAdv);
print("loginvepssqloHAdv " ) ; print(R(log(1/epsoptloHA^2)/R(log(2))));
print("loginvepssqhiHAdv " ) ; print(R(log(1/epsopthiHA^2)/R(log(2))));
print("voptlenloHA " ) ; print(voptlenloHA);
print("voptlenhiHA " ) ; print(voptlenhiHA);
print("moptloHA " ) ; print(moptloHA);
print("mopthiHA " ) ; print(mopthiHA);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHA " ) ; print(tauoptloHA);
print("tauopthiHA " ) ; print(tauopthiHA);
log2THAmidm = logToptloHAdv;

# compute quantum complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRat, bopthiRat, logToptloRat, logTopthiRat, voptlenloRat, moptloRat, tauoptloRat, epsoptloRat, voptlenhiRat, mopthiRat, tauopthiRat, epsopthiRat = LWEdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdv);

print("Complexity quantum estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRat " ) ; print(boptloRat);
print("bopthiRat " ) ; print(bopthiRat);
print("logToptloRat " ) ; print(logToptloRat);
print("logTopthiRat " ) ; print(logTopthiRat);
print("loginvepsloRat " ) ; print(R(log(1/epsoptloRat)/R(log(2))));
print("loginvepshiRat " ) ; print(R(log(1/epsopthiRat)/R(log(2))));
print("log(sqrt(ToptloRat)/epsloRat) " ) ; print(0.5*logToptloRat+R(log(1/epsoptloRat)/R(log(2))));
print("log(sqrt(TopthiRat)/epshiRat) " ) ; print(0.5*logTopthiRat+R(log(1/epsopthiRat)/R(log(2))));
print("voptlenloRat " ) ; print(voptlenloRat);
print("voptlenhiRat " ) ; print(voptlenhiRat);
print("moptloRat " ) ; print(moptloRat);
print("mopthiRat " ) ; print(mopthiRat);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRat " ) ; print(tauoptloRat);
print("tauopthiRat " ) ; print(tauopthiRat);
log2Tepsmidm = logToptloRat;


# compute classical complexity 1 of PLWE dist. attack: min T for high advantage
boptloHAdvC, bopthiHAdvC, logToptloHAdvC, logTopthiHAdvC, voptlenloHAC, moptloHAC, tauoptloHAC, epsoptloHAC, voptlenhiHAC, mopthiHAC, tauopthiHAC, epsopthiHAC = LWECdualComplexMinTHighAdv(m,q,alpha);

print("Complexity classical estimate 1 for PLWE dist. attack: min T for high advantage:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdvC " ) ; print(boptloHAdvC);
print("bopthiHAdvC " ) ; print(bopthiHAdvC);
print("logToptloHAdvC " ) ; print(logToptloHAdvC);
print("logTopthiHAdvC " ) ; print(logTopthiHAdvC);
print("loginvepssqloHAdvC " ) ; print(R(log(1/epsoptloHAC^2)/R(log(2))));
print("loginvepssqhiHAdvC " ) ; print(R(log(1/epsopthiHAC^2)/R(log(2))));
print("voptlenloHAC " ) ; print(voptlenloHAC);
print("voptlenhiHAC " ) ; print(voptlenhiHAC);
print("moptloHAC " ) ; print(moptloHAC);
print("mopthiHAC " ) ; print(mopthiHAC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHAC " ) ; print(tauoptloHAC);
print("tauopthiHAC " ) ; print(tauopthiHAC);
log2THAmidmC = logToptloHAdvC;


# compute Classical complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRatC, bopthiRatC, logToptloRatC, logTopthiRatC, voptlenloRatC, moptloRatC, tauoptloRatC, epsoptloRatC, voptlenhiRatC, mopthiRatC, tauopthiRatC, epsopthiRatC = LWECdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdvC);

print("Complexity classical estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRatC " ) ; print(boptloRatC);
print("bopthiRatC " ) ; print(bopthiRatC);
print("logToptloRatC " ) ; print(logToptloRatC);
print("logTopthiRatC " ) ; print(logTopthiRatC);
print("loginvepsloRatC " ) ; print(R(log(1/epsoptloRatC)/R(log(2))));
print("loginvepshiRatC " ) ; print(R(log(1/epsopthiRatC)/R(log(2))));
print("log(sqrt(ToptloRatC)/epsloRatC) " ) ; print(0.5*logToptloRatC+R(log(1/epsoptloRatC)/R(log(2))));
print("log(sqrt(TopthiRatC)/epshiRatC) " ) ; print(0.5*logTopthiRatC+R(log(1/epsopthiRatC)/R(log(2))));
print("voptlenloRatC " ) ; print(voptlenloRatC);
print("voptlenhiRatC " ) ; print(voptlenhiRatC);
print("moptloRatC " ) ; print(moptloRatC);
print("mopthiRatC " ) ; print(mopthiRatC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRatC " ) ; print(tauoptloRatC);
print("tauopthiRatC " ) ; print(tauopthiRatC);
log2TepsmidmC = logToptloRatC;


# MIN FAMILY DIMENSION m = mmin SECURITY ESTIMATES
m = mmin; # min PLWE dimension
alpha = R(sdchieq)/R(q); # LWE alpha parameter (in terms of noise standard deviation).

# compute complexity 1 of PLWE dist. attack: min T for high advantage
boptloHAdv, bopthiHAdv, logToptloHAdv, logTopthiHAdv, voptlenloHA, moptloHA, tauoptloHA, epsoptloHA, voptlenhiHA, mopthiHA, tauopthiHA, epsopthiHA = LWEdualComplexMinTHighAdv(m,q,alpha);

print("Complexity estimate 1 for PLWE dist. attack: min T for high advantage:");
print("min PLWE dimension mmin=d+k"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdv " ) ; print(boptloHAdv);
print("bopthiHAdv " ) ; print(bopthiHAdv);
print("logToptloHAdv " ) ; print(logToptloHAdv);
print("logTopthiHAdv " ) ; print(logTopthiHAdv);
print("loginvepssqloHAdv " ) ; print(R(log(1/epsoptloHA^2)/R(log(2))));
print("loginvepssqhiHAdv " ) ; print(R(log(1/epsopthiHA^2)/R(log(2))));
print("voptlenloHA " ) ; print(voptlenloHA);
print("voptlenhiHA " ) ; print(voptlenhiHA);
print("moptloHA " ) ; print(moptloHA);
print("mopthiHA " ) ; print(mopthiHA);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHA " ) ; print(tauoptloHA);
print("tauopthiHA " ) ; print(tauopthiHA);
log2THAminm = logToptloHAdv;

# compute complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRat, bopthiRat, logToptloRat, logTopthiRat, voptlenloRat, moptloRat, tauoptloRat, epsoptloRat, voptlenhiRat, mopthiRat, tauopthiRat, epsopthiRat = LWEdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdv);

print("Complexity estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("min PLWE dimension m=d+k"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRat " ) ; print(boptloRat);
print("bopthiRat " ) ; print(bopthiRat);
print("logToptloRat " ) ; print(logToptloRat);
print("logTopthiRat " ) ; print(logTopthiRat);
print("loginvepsloRat " ) ; print(R(log(1/epsoptloRat)/R(log(2))));
print("loginvepshiRat " ) ; print(R(log(1/epsopthiRat)/R(log(2))));
print("log(sqrt(ToptloRat)/epsloRat) " ) ; print(0.5*logToptloRat+R(log(1/epsoptloRat)/R(log(2))));
print("log(sqrt(TopthiRat)/epshiRat) " ) ; print(0.5*logTopthiRat+R(log(1/epsopthiRat)/R(log(2))));
print("voptlenloRat " ) ; print(voptlenloRat);
print("voptlenhiRat " ) ; print(voptlenhiRat);
print("moptloRat " ) ; print(moptloRat);
print("mopthiRat " ) ; print(mopthiRat);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRat " ) ; print(tauoptloRat);
print("tauopthiRat " ) ; print(tauopthiRat);
log2Tepsminm = logToptloRat;


# compute classical complexity 1 of PLWE dist. attack: min T for high advantage
boptloHAdvC, bopthiHAdvC, logToptloHAdvC, logTopthiHAdvC, voptlenloHAC, moptloHAC, tauoptloHAC, epsoptloHAC, voptlenhiHAC, mopthiHAC, tauopthiHAC, epsopthiHAC = LWECdualComplexMinTHighAdv(m,q,alpha);

print("Complexity classical estimate 1 for PLWE dist. attack: min T for high advantage:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptHAdv up to tolerance "); print(epsterm);
print("boptloHAdvC " ) ; print(boptloHAdvC);
print("bopthiHAdvC " ) ; print(bopthiHAdvC);
print("logToptloHAdvC " ) ; print(logToptloHAdvC);
print("logTopthiHAdvC " ) ; print(logTopthiHAdvC);
print("loginvepssqloHAdvC " ) ; print(R(log(1/epsoptloHAC^2)/R(log(2))));
print("loginvepssqhiHAdvC " ) ; print(R(log(1/epsopthiHAC^2)/R(log(2))));
print("voptlenloHAC " ) ; print(voptlenloHAC);
print("voptlenhiHAC " ) ; print(voptlenhiHAC);
print("moptloHAC " ) ; print(moptloHAC);
print("mopthiHAC " ) ; print(mopthiHAC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloHAC " ) ; print(tauoptloHAC);
print("tauopthiHAC " ) ; print(tauopthiHAC);
log2THAminmC = logToptloHAdvC;


# compute Classical complexity 2 of PLWE dist. attack: min T/eps ratio 
boptloRatC, bopthiRatC, logToptloRatC, logTopthiRatC, voptlenloRatC, moptloRatC, tauoptloRatC, epsoptloRatC, voptlenhiRatC, mopthiRatC, tauopthiRatC, epsopthiRatC = LWECdualComplexMinTtoAdvRatio(m,q,alpha,boptloHAdvC);

print("Complexity classical estimate 2 for PLWE dist. attack: min T/eps ratio:");
print("max PLWE dimension m=n"); print(m);
print("finished bisection search for boptTtoAdvRatio up to tolerance "); print(epsterm);
print("boptloRatC " ) ; print(boptloRatC);
print("bopthiRatC " ) ; print(bopthiRatC);
print("logToptloRatC " ) ; print(logToptloRatC);
print("logTopthiRatC " ) ; print(logTopthiRatC);
print("loginvepsloRatC " ) ; print(R(log(1/epsoptloRatC)/R(log(2))));
print("loginvepshiRatC " ) ; print(R(log(1/epsopthiRatC)/R(log(2))));
print("log(sqrt(ToptloRatC)/epsloRatC) " ) ; print(0.5*logToptloRatC+R(log(1/epsoptloRatC)/R(log(2))));
print("log(sqrt(TopthiRatC)/epshiRatC) " ) ; print(0.5*logTopthiRatC+R(log(1/epsopthiRatC)/R(log(2))));
print("voptlenloRatC " ) ; print(voptlenloRatC);
print("voptlenhiRatC " ) ; print(voptlenhiRatC);
print("moptloRatC " ) ; print(moptloRatC);
print("mopthiRatC " ) ; print(mopthiRatC);
print("t*m (max mopt possible)"); print(t*m);
print("tauoptloRatC " ) ; print(tauoptloRatC);
print("tauopthiRatC " ) ; print(tauopthiRatC);
log2TepsminmC = logToptloRatC;


# print overall parameters summary
# scheme parameters
print("PARAMETERS and RESULTS SUMMARY");
print("==============================");
print("n " ) ; print(n);
print("k " ) ; print(k);
print("t " ) ; print(t);
print("d " ) ; print(d);
print("ms" ) ; print(ms);
print("B " ) ; print(B);
print("B2" ) ; print(B2);
print("rho") ; print(rho);
print("Ndec1"); print(Ndec1);
print("Ndec"); print(Ndec);
print("q " ) ; print(q);
print("chie: binomial difference, eta"); print(etabin);
print("chir: Unif(-B/2,...,B/2) WITHOUT 0 (frac rho of ri coeffs), Unif(-B2/2,...,B2/2) WITHOUT 0 (frac (1-rho) of ri coeffs)");
print("mmin " ) ; print(mmin);
print("mmid " ) ; print((mmin+n)/2);
print("mmargin = gap1 =" ) ; print(mmargin);
print("gap2 = n-(d+k)-gap1 = " ) ; print(n-(d+k)-mmargin);
print("cmp = " ) ; print(cmp);
#DepthRO = 2^17;
#Q_d = 2^log2MAXDEPTHmin/DepthRO+1;
print("Q_d = ") ; print(Q_d);
# Security Results summary
print("log2 of dec. error prob. " ) ; print(log2pehoff);
print("LHL t lower bnd "); print(tlo);
print("quantum security levels:");
print("log2THAmaxm "); print(log2THAmaxm);
print("log2THAmidm "); print(log2THAmidm);
print("log2THHminm "); print(log2THAminm);
print("log2Tepsmaxm "); print(log2Tepsmaxm);
print("log2Tepsmidm "); print(log2Tepsmidm);
print("log2Tepsminm "); print(log2Tepsminm);
print("classical security levels:");
print("log2THAmaxmC "); print(log2THAmaxmC);
print("log2THAmidmC "); print(log2THAmidmC);
print("log2THHminmC "); print(log2THAminmC);
print("log2TepsmaxmC "); print(log2TepsmaxmC);
print("log2TepsmidmC "); print(log2TepsmidmC);
print("log2TepsminmC "); print(log2TepsminmC);

print("sdchieq " ) ; print(sdchieq);

# Key/ctxt length summary
ell0 = R(floor(log(q)/log(2))+1);
print("ell0"); print(ell0);
pklenresCPA = 32 + ceil(R(t*D1*ell0/8));
pklenresCCA = pklenresCPA;
print("pk len (no A), byte "); print(pklenresCCA);
ctxtlenresCPA = ceil(R(D2*ell0/8)) + ceil(R(d*(ell0 - cmp)/8));
ctxtlenresCCA = ctxtlenresCPA + 32; 
print("ctxt len, byte "); print(ctxtlenresCCA);

#other pars
print("other pars summary:");
Beffc = sqrt(B^2*rho+B2^2*(1-rho));
chirsdeff = R(sqrt((Beffc)^2/12 + Beffc/4 + 1/6));
BLHL = 2^(meanminent);
lgcor = R(log(((q-1)/2^(ms+1))/(chirsdeff*sdchieq*sqrt(Ndec)))/log(2));
lgsec = R(log(q/sdchieq)/log(2));
lgLHL = R(log(q/BLHL)/log(2));
zcorrCLTheur = R(sqrt(2*log(2)*((-1)*log2pehoff+log(2*d)/log(2))));
zcorrhoff = R(2^(lgcor));
print("Eff. B for corr. Beffc " ) ; print(Beffc);
print("eff. chir sd= " ); print(chirsdeff);
print("Eff. B for LHL BLHL "); print(BLHL);
print("lg corr ratio: lg(((q-1)/2^(ms+1))/(Beffc*sdchieq*sqrt(Ndec)))"); print(lgcor);
print("lg sec ratio: lg(q/sdchieq)"); print(lgsec);
print("lg LHL ratio: lg(q/BLHL) "); print(lgLHL);
print("heur. corr z (CLT heuristic): "); print(zcorrCLTheur);
print("proven corr z (numerical Hoffding): "); print(zcorrhoff);
print("compression LS bits removed, cmp: "); print(cmp);


# RESULT SUMMARY
# check if goals met and compute safety margins

print("PLWE QUANTUM SECURITY SUMMARY:");
print("log2Qsecgoal (no safety margin)"); print(log2Qsecgoal);
print("log2Qsecgoalsafe (with safety margin)"); print(log2Qsecgoalsafe);
print("log2QsecClaimminm (claimed, min PLWE dim)"); print(log2Tepsminm);
print("log2QsecClaimmidm (claimed, mid PLWE dim)"); print(log2Tepsmidm);
print("log2QsecClaimmaxm (claimed, max PLWE dim)"); print(log2Tepsmaxm);
print("Qsec min margin"); print(log2Tepsminm/log2Qsecgoal);
print("Qsec mid margin"); print(log2Tepsmidm/log2Qsecgoal);
print("Qsec max margin"); print(log2Tepsmaxm/log2Qsecgoal);
if ((log2Tepsmidm > log2Qsecgoalsafe) and (log2Tepsminm > log2Qsecgoal))  :
	print("PLWE Qsec goals OK");
else :
	print("PLWE Qsec goals FAIL");

print("PLWE CLASSICAL SECURITY SUMMARY:");
print("log2Csecgoal (no safety margin)"); print(log2Csecgoal);
print("log2Csecgoalsafe (with safety margin)"); print(log2Csecgoalsafe);
print("log2CsecClaimminm (claimed, min PLWE dim)"); print(log2TepsminmC);
print("log2CsecClaimminm (claimed, mid PLWE dim)"); print(log2TepsmidmC);
print("log2CsecClaimmaxm (claimed, max PLWE dim)"); print(log2TepsmaxmC);
print("Csec min margin"); print(log2TepsminmC/log2Csecgoal);
print("Csec mid margin"); print(log2TepsmidmC/log2Csecgoal);
print("Csec max margin"); print(log2TepsmaxmC/log2Csecgoal);
if ((log2TepsmidmC > log2Csecgoalsafe) and (log2TepsminmC > log2Csecgoal)) :
	print("PLWE Csec goals OK");
else :
	print("PLWE Csec goals FAIL");

print("LHL ADVANTAGE SUMMARY:");
print("log2DeltaLHLgoal (no safety margin)"); print(log2DeltaLHLgoal);
print("log2DeltaLHLgoalsafe (with safety margin)"); print(log2DeltaLHLgoalsafe);
print("logDeltaLHLAch (achieved)"); print(log2DeltaLHLAch);
print("logDeltaLHL achieved margin"); print(log2DeltaLHLAch/log2DeltaLHLgoal);
if (log2DeltaLHLAch < log2DeltaLHLgoalsafe) :
	print("LHL safety goal OK");
else :
	print("LHL safety goal FAIL");

print("ERROR PROBABILITY SUMMARY:");
print("log2pegoal (no safety margin)"); print(log2pegoal);
print("log2pegoalsafe (with safety margin)"); print(log2pegoalsafe);
print("log2pehoff (achieved)"); print(log2pehoff);
print("log2pehoff achieved margin"); print(log2pehoff/log2pegoal);
if (log2pehoff < log2pegoalsafe) :
	print("pe safety goal OK");
else :
	print("pe safety goal FAIL");

print("OVERALL SCHEME CLASSICAL CLAIMED SECURITY:");
print("log2SelCsecgoal (no safety margin)"); print(log2SelCsecgoal);
log2ScmCsecClaim = -R(log(6*2^(-log2TepsminmC) + 6*2^(log2DeltaLHLAch) + 2^(log2pehoff-log2TRO) + 20*2^(-(256+log2TRO)))/log(2));
print("log2ScmCsecClaim (Lower Bound)"); print(log2ScmCsecClaim);
print("log2ScmCsecClaim claimed margin"); print(log2ScmCsecClaim/log2SelCsecgoal);
if (log2ScmCsecClaim > log2SelCsecgoal) :
	print("Classical overall Scheme Lower Bound goal OK");
else :
	print("Classical overall Scheme Lower Bound goal FAIL");
log2ScmCsecClaim2 = -R(log(6*2^(-log2TepsminmC) + 6*2^(log2DeltaLHLAch) + 2^(log2pehoff-log2TRO))/log(2));
print("log2ScmCsecClaim2 (Lower Bound, neglecting RO term)"); print(log2ScmCsecClaim2);
print("log2ScmCsecClaim2 margin"); print(log2ScmCsecClaim2/log2SelCsecgoal);


print("OVERALL SCHEME QUANTUM CLAIMED SECURITY:");
print("log2SelQsecgoal (no safety margin)"); print(log2SelQsecgoal);
log2ScmQsecClaim = -R(log(6*2^(-log2Tepsminm) + 6*2^(log2DeltaLHLAch) + 8*Q_d*2^(log2pehoff-log2TQRO) + 8*20*Q_d*2^(-(256+log2TQRO)))/log(2));
print("log2ScmQsecClaim "); print(log2ScmQsecClaim);
print("log2ScmQsecClaim claimed margin"); print(log2ScmQsecClaim/log2SelQsecgoal);
if (log2ScmQsecClaim > log2SelQsecgoal) :
	print("Quantum overall Scheme goal OK");
else :
	print("Quantum overall Scheme goal FAIL");


print("KEY/CTXT LENGTH SUMMARY:");
print("pk len (no A), byte "); print(pklenresCCA);
print("ctxt len, byte "); print(ctxtlenresCCA);

sys.stdout = orig_stdout;
f.close();



# In[ ]:





# In[ ]:




# In[ ]:



