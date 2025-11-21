/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
* ***************************************************************************/

#include "stdio.h"
#include "string.h"

#include "kem.h"
#include "sampling.h"
#include "parallel_hash.h"
#include "decode.h"
#include "gf2x_mul.h"
#include "measurements.h"

#ifdef BIKE2
    #include "ntl.h"
#endif

_INLINE_ status_t encrypt(OUT ct_t* ct,
                          IN const e_t* e,
                          IN const pk_t* pk,
                          IN const seed_t* seed)
{
    status_t res = SUCCESS;
    padded_r_t m = {0};
    dbl_pad_ct_t p_ct;

    //Split e into e0 and e1. Initialization is done in split_e
    split_e_t splitted_e;
    split_e(&splitted_e, e);
    
    EDMSG("e0: "); print((uint64_t*)splitted_e.val[0].raw, R_BITS);
    EDMSG("e1: "); print((uint64_t*)splitted_e.val[1].raw, R_BITS);

#ifdef BIKE2
    //Pad the public key
    const pad_pk_t p_pk = {{.val = *pk, .pad = {0}}};

    ntl_mod_mul(p_ct.val.raw, splitted_e.val[1].raw, p_pk.val.raw);
    gf2x_add(p_ct.val.raw, p_ct.val.raw, splitted_e.val[0].raw, R_SIZE);
    
    *ct = p_ct.val;
    EDMSG("c:  "); print((uint64_t*)ct->raw, R_BITS);
#else
    //Pad the public key
    const pad_pk_t p_pk = {{.val = pk->val[0], .pad = {0}},
                           {.val = pk->val[1], .pad = {0}}};

    DMSG("    Sampling m.\n");
    res = sample_uniform_r_bits(m.val.raw, seed, NO_RESTRICTION); CHECK_STATUS(res);

    EDMSG("m:  "); print((uint64_t*)m.val.raw, R_BITS);

    DMSG("    Calculating the ciphertext.\n");

    gf2x_mod_mul(p_ct[0].qw, m.qw, p_pk[0].qw);
    gf2x_mod_mul(p_ct[1].qw, m.qw, p_pk[1].qw);

    DMSG("    Addding Error to the ciphertext.\n");

    gf2x_add(p_ct[0].val.raw, p_ct[0].val.raw, splitted_e.val[0].raw, R_SIZE);
    gf2x_add(p_ct[1].val.raw, p_ct[1].val.raw, splitted_e.val[1].raw, R_SIZE);

    //Copy the data outside
    ct->val[0] = p_ct[0].val;
    ct->val[1] = p_ct[1].val;

    EDMSG("c0: "); print((uint64_t*)ct->val[0].raw, R_BITS);
    EDMSG("c1: "); print((uint64_t*)ct->val[1].raw, R_BITS);
#endif

EXIT:

    return res;
}


//Generate the Shared Secret (K(e))
_INLINE_ void get_ss(OUT ss_t* out, IN const e_t* e)
{
    DMSG("    Enter get_ss.\n");

    //Calculate the hash
    sha_hash_t hash = {0};
    parallel_hash(&hash, e->raw, sizeof(*e));

    //Truncate the final hash into K by copying only the LSBs
    memcpy(out->raw, hash.raw, sizeof(*out));

    DMSG("    Exit get_ss.\n");
}

////////////////////////////////////////////////////////////////
//The three APIs below (keygeneration, encapsulate, decapsulate) are defined by NIST:
//In addition there are two KAT versions of this API as defined.
////////////////////////////////////////////////////////////////
int crypto_kem_keypair(OUT unsigned char *pk, OUT unsigned char *sk)
{
    //Convert to this implementation types
    sk_t* l_sk = (sk_t*)sk;
    pk_t* l_pk = (pk_t*)pk;
    
    status_t res = SUCCESS;

    //For DRBG and AES_PRF
    double_seed_t seeds = {0};
    aes_ctr_prf_state_t h_prf_state = {0};
    
    //Get the entrophy seeds
    get_seeds(&seeds, KEYGEN_SEEDS);

    DMSG("  Enter crypto_kem_keypair.\n");
    DMSG("    Calculating the secret key.\n");

    //Both h0 and h1 use the same context
    init_aes_ctr_prf_state(&h_prf_state, MAX_AES_INVOKATION, &seeds.s1);

    //Padded for internal use
    //We don't want to send the padded data outside to save BW.
    pad_sk_t p_sk = {0};
    res = generate_sparse_fake_rep(p_sk[0].val.raw, l_sk->wlist[0].val, DV, 
                                   FAKE_DV, R_BITS, sizeof(p_sk[0]), &h_prf_state);
    CHECK_STATUS(res);
    res = generate_sparse_fake_rep(p_sk[1].val.raw, l_sk->wlist[1].val, DV, 
                                   FAKE_DV, R_BITS, sizeof(p_sk[1]), &h_prf_state); 
    CHECK_STATUS(res);

    //Copy data
    l_sk->bin[0] = p_sk[0].val;
    l_sk->bin[1] = p_sk[1].val;
        
    DMSG("    Calculating the public key.\n");
#ifdef BIKE2
    uint8_t inv1[R_SIZE];
    ntl_inv_mod(inv1, l_sk->bin[0].raw);
    ntl_mod_mul(l_pk->raw, l_sk->bin[1].raw, inv1);
    l_sk->pk = *l_pk;
#else
    //Must intialized padding to zero!!
    padded_r_t g = {.pad = {0}};
    res = sample_uniform_r_bits(g.val.raw, &seeds.s2, MUST_BE_ODD);  
    CHECK_STATUS(res);

    //PK is dbl padded because modmul require scratch space for the multiplication result
    dbl_pad_pk_t p_pk = {0};

    // Calculate (g0, g1) = (g*h1, g*h0)
    gf2x_mod_mul(p_pk[0].qw, g.qw, p_sk[1].qw);
    gf2x_mod_mul(p_pk[1].qw, g.qw, p_sk[0].qw);

    //Copy the data outside
    l_pk->val[0] = p_pk[0].val;
    l_pk->val[1] = p_pk[1].val;

    EDMSG("g:  "); print((uint64_t*)g.val.raw, R_BITS);
#endif

    EDMSG("h0: "); print((uint64_t*)&l_sk->bin[0], R_BITS);
    EDMSG("h1: "); print((uint64_t*)&l_sk->bin[1], R_BITS);
    EDMSG("h0c:"); print((uint64_t*)&l_sk->wlist[0], SIZEOF_BITS(compressed_idx_dv_t));
    EDMSG("h1c:"); print((uint64_t*)&l_sk->wlist[1], SIZEOF_BITS(compressed_idx_dv_t));

#ifdef BIKE2
    EDMSG("g0: "); print((uint64_t*)l_pk->raw, R_BITS);
#else
    EDMSG("g0: "); print((uint64_t*)p_pk[0].val.raw, R_BITS);
    EDMSG("g1: "); print((uint64_t*)p_pk[1].val.raw, R_BITS);
#endif

EXIT:

    DMSG("  Exit crypto_kem_keypair.\n");
    return res;
}

//Encapsulate - pk is the public key,
//              ct is a key encapsulation message (ciphertext),
//              ss is the shared secret.
int crypto_kem_enc(OUT unsigned char *ct,
                   OUT unsigned char *ss,
                   IN  const unsigned char *pk)
{
    DMSG("  Enter crypto_kem_enc.\n");

    status_t res = SUCCESS;

    //Convert to this implementation types
    const pk_t* l_pk = (pk_t*)pk;
    ct_t* l_ct = (ct_t*)ct;
    ss_t* l_ss = (ss_t*)ss;
    padded_e_t e = {0};

    //For NIST DRBG_CTR.
    double_seed_t seeds = {0};
    aes_ctr_prf_state_t e_prf_state = {0};

    //Get the entrophy seeds
    get_seeds(&seeds, ENCAPS_SEEDS);

    //Random data generator.
    // Using first seed.
    init_aes_ctr_prf_state(&e_prf_state, MAX_AES_INVOKATION, &seeds.s1);

    DMSG("    Generating error.\n");
    compressed_idx_t_t dummy;
    res = generate_sparse_rep(e.val.raw, dummy.val, T1, N_BITS, sizeof(e), &e_prf_state); CHECK_STATUS(res);

    EDMSG("e:  "); print((uint64_t*)e.val.raw, sizeof(e.val)*8);

    // Computing ct = enc(pk, e)
    // Using second seed
    DMSG("    Encrypting.\n");
    res = encrypt(l_ct, &e.val, l_pk, &seeds.s2);  
    CHECK_STATUS(res);

    DMSG("    Generating shared secret.\n");
    get_ss(l_ss, &e.val);

    EDMSG("ss: "); print((uint64_t*)l_ss->raw, SIZEOF_BITS(*l_ss));

EXIT:

    DMSG("  Exit crypto_kem_enc.\n");
    return res;
}

//Decapsulate - ct is a key encapsulation message (ciphertext),
//              sk is the private key,
//              ss is the shared secret
int crypto_kem_dec(OUT unsigned char *ss,
                   IN const unsigned char *ct,
                   IN const unsigned char *sk)
{
    DMSG("  Enter crypto_kem_dec.\n");
    
    //Convert to this implementation types
    const sk_t* l_sk = (sk_t*)sk;
    const ct_t* l_ct = (ct_t*)ct;
    ss_t* l_ss = (ss_t*)ss;
    
    //Must be initialized to zero!!!
    syndrome_t syndrome = {0};
    e_t e = {0};
    
    DMSG("  Computing s.\n");
    compute_syndrome(&syndrome, l_ct, l_sk);

    DMSG("  Decoding.\n");
    if (decode(&e, &syndrome, l_ct, l_sk) != 0)
    {
        DMSG("    Decoding result: failure!\n");
        return E_DECODING_FAILURE;
    }

    // Check if the error weight is exactly t
    if (count_ones(e.raw, sizeof(e)) != T1)
    {
        MSG("    Error weight is not t\n");
        return E_ERROR_WEIGHT_IS_NOT_T;
    }

    get_ss(l_ss, &e);

    DMSG("  Exit crypto_kem_dec.\n");
    return SUCCESS;
}
