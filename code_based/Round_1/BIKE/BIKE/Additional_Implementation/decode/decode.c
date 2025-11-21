/***************************************************************************
* Additional implementation of "BIKE: Bit Flipping Key Encapsulation". 
* Copyright (c) 2017 Nir Drucker, Shay Gueron
* (drucker.nir@gmail.com, shay.gueron@gmail.com)
* The license is detailed in the file LICENSE.txt, and applies to this file.
*
* The optimizations are based on the description developed in the paper: 
* N. Drucker, S. Gueron, 
* "A toolbox for software optimization of QC-MDPC code-based cryptosystems", 
* ePrint (2017).
* The decoder (in decoder/decoder.c) algorithm is the algorithm included in
* the early submission of CAKE (due to N. Sandrier and R Misoczki).
*
* ***************************************************************************/

#include "decode.h"
#include "stdio.h"
#include "string.h"
#include "utilities.h"
#include "measurements.h"
#include "gf2x_mul.h"

#ifdef BIKE2
  #include "ntl.h"
#endif

// Decoding (bit-flipping) parameter
#define MAX_IT 20

////////////////////////////////////////////////////////////////////////////////
//Defined in decode.S file
extern void compute_counter_of_unsat(OUT uint8_t upc[N_BITS],
                                     IN const uint8_t s[R_BITS],
                                     IN const compressed_idx_dv_t* inv_h0_compressed,
                                     IN const compressed_idx_dv_t* inv_h1_compressed);

extern void recompute(OUT syndrome_t* s,
                      IN const uint32_t numPositions,
                      IN const uint32_t positions[R_BITS],
                      IN const compressed_idx_dv_t* h_compressed);


extern void convert_to_redundant_rep(OUT uint8_t* out, 
                                     IN const uint8_t * in, 
                                     IN const uint64_t length);

////////////////////////////////////////////////////////////////////////////////

typedef ALIGN(16) struct decode_ctx_s
{
    // count the number of unsatisfied parity-checks:
#ifdef AVX512
    ALIGN(16) uint8_t upc[N_QDQWORDS_BITS];
#else
    ALIGN(16) uint8_t upc[N_DDQWORDS_BITS];
#endif
    
#ifdef CONSTANT_TIME
    e_t black_e;
    e_t gray_e;
#else
    // Black positions are the positions involved in more than "threshold" UPC
    uint32_t black_pos[N0][R_BITS];
    uint32_t num_black_pos[N0];
    
    // Gray positions are the positions involved in more than (threashold - delta) UPC
    uint32_t gray_pos [N0][R_BITS];
    uint32_t num_gray_pos [N0];

    uint32_t unflip_pos[N0][R_BITS];
    uint32_t num_unflip_pos[N0];

    uint32_t gray_pos_to_flip[N0][R_BITS]; 
    uint32_t num_gray_pos_to_flip[N0];
#endif
    int delta;
    uint32_t threshold;
} decode_ctx_t;

void split_e(OUT split_e_t* split_e, IN const e_t* e)
{
    //Copy lower bytes (e0)
    memcpy(split_e->val[0].raw, e->raw, R_SIZE);
    
    //Now load second value
    for(uint32_t i = R_SIZE ; i < N_SIZE; ++i)
    {
        split_e->val[1].raw[i - R_SIZE] = ((e->raw[i] << LAST_R_BYTE_TRAIL) | 
                                           (e->raw[i-1] >> LAST_R_BYTE_LEAD));
    }
    
    //Fix corner case
    if(N_SIZE < 2UL*R_SIZE)
    {
        split_e->val[1].raw[R_SIZE-1] = (e->raw[N_SIZE-1] >> LAST_R_BYTE_LEAD);
    }
    
    //Fix last value
    split_e->val[0].raw[R_SIZE-1] &= LAST_R_BYTE_MASK;
    split_e->val[1].raw[R_SIZE-1] &= LAST_R_BYTE_MASK;
}

// transpose a row into a column
_INLINE_ void transpose(OUT red_r_t* col, 
                        IN const red_r_t* row)
{
    col->raw[0] = row->raw[0];
    for (uint64_t i = 1; i < R_BITS ; ++i)
    {
        col->raw[i] = row->raw[(R_BITS) - i];
    }
}

void compute_syndrome(OUT syndrome_t* syndrome,
                      IN const ct_t* ct,
                      IN const sk_t* sk)
{
    const pad_sk_t pad_sk = {{.val=sk->bin[0]}, {.val=sk->bin[1]}};
    
    //gf2x_mod_mul requires the values to be 64bit padded and extra (dbl) space for the results
    dbl_pad_syndrome_t pad_s;
#ifdef BIKE2
    const pad_ct_t pad_ct = {.val=*ct};
    gf2x_mod_mul(pad_s[0].qw, pad_ct.qw, pad_sk[0].qw);
#else
    const pad_ct_t pad_ct = {{.val=ct->val[0]}, {.val=ct->val[1]}};

    //compute s = c0*h0 + c1*h1:
    gf2x_mod_mul(pad_s[0].qw, pad_ct[0].qw, pad_sk[0].qw);
    gf2x_mod_mul(pad_s[1].qw, pad_ct[1].qw, pad_sk[1].qw);

    gf2x_add(pad_s[0].val.raw, pad_s[0].val.raw, pad_s[1].val.raw, R_SIZE);
#endif
    //Converting to redunandt representation and then transposing the value.
    red_r_t s_tmp_bytes = {0};
    convert_to_redundant_rep(s_tmp_bytes.raw, pad_s[0].val.raw, sizeof(s_tmp_bytes));
    transpose(&syndrome->dup1, &s_tmp_bytes);
}

_INLINE_ uint32_t get_adhoc_threshold(IN const decode_ctx_t* ctx)
{
    uint32_t max_upc = 0;
    for (uint32_t i = 0; i < N_BITS; i++)
    {
        const uint32_t mask = secure_ge32(ctx->upc[i], max_upc);
        max_upc += (ctx->upc[i] - max_upc) * mask;
    }

    return  max_upc - ctx->delta;
}

_INLINE_ uint32_t get_fixed_threshold(IN const red_r_t* s,
                                      IN const uint32_t iter)
{
    // Compute syndrome weight
    uint32_t syndrome_weight = count_ones(s->raw, R_BITS);

    // Set threshold according to syndrome weight
    uint32_t threshold = 0; 
    
    if (iter == 0) {
        if (syndrome_weight >= 15175) {
                threshold = 84; // never reached in practice
        } else if (syndrome_weight >= 14944) {
                threshold = 83;
        } else if (syndrome_weight >= 14713) {
                threshold = 82;
        } else if (syndrome_weight >= 14483) {
                threshold = 81;
        } else if (syndrome_weight >= 14254) {
                threshold = 80;
        } else if (syndrome_weight >= 14026) {
                threshold = 79;
        } else {
                // never reached in practice
                threshold = 78; 
        }
    } else if (iter == 1) {
        if (syndrome_weight <= 11895) {
                threshold = 71;
        } else if (syndrome_weight <= 12440) {
                threshold = 72;
        } else if (syndrome_weight <= 12860) {
                threshold = 73;
        } else if (syndrome_weight <= 13175) {
                threshold = 74;
        } else if (syndrome_weight <= 13399) {
                // never reached in practice
                threshold = 75; 
        } else {
                // never reached in practice
                threshold = 76; 
        }
    } else { // iter > 1
        if (syndrome_weight <= 10850) {
                threshold = 69;
        } else if (syndrome_weight <= 11865) {
                threshold = 70;
        } else if (syndrome_weight <= 12370) {
                // never reached in practice
                threshold = 71; 
        } else {
                // never reached in practice
                threshold = 72; 
        }
    }

    DMSG("    Thresold: %d\n", threshold);

    return threshold;
}

#ifdef CONSTANT_TIME
void recompute_syndrome(OUT syndrome_t* syndrome,
                       IN const ct_t* ct,
                       IN const sk_t* sk,
                       IN const e_t* e)
{
    //Split e into e0 and e1. Initialization is done in split_e.
    split_e_t splitted_e;
    split_e(&splitted_e, e);

#ifdef BIKE2
    ct_t tmp_ct;

    //Adapt the ciphertext with e1
    ntl_mod_mul(tmp_ct.raw, splitted_e.val[1].raw, sk->pk.raw);
    gf2x_add(tmp_ct.raw, tmp_ct.raw, ct->raw, R_SIZE);

    //Adapt the ciphertext with e0
    gf2x_add(tmp_ct.raw, tmp_ct.raw, splitted_e.val[0].raw, R_SIZE);
#else
    ct_t tmp_ct = *ct;

    //Adapt the ciphertext
    gf2x_add(tmp_ct.val[0].raw, tmp_ct.val[0].raw, splitted_e.val[0].raw, R_SIZE);
    gf2x_add(tmp_ct.val[1].raw, tmp_ct.val[1].raw, splitted_e.val[1].raw, R_SIZE);
#endif
    
    //recompute the syndromee
    compute_syndrome(syndrome, &tmp_ct, sk);
}

///////////////////////////////////////////////////////////
// find_error1/2 are defined in ASM files
//////////////////////////////////////////////////////////
void find_error1(IN OUT e_t* e,
                 OUT e_t* black_e,
                 OUT e_t* gray_e,
                 IN const uint8_t* upc,
                 IN const uint32_t black_th,
                 IN const uint32_t gray_th);

void find_error2(IN OUT e_t* e,
                 OUT e_t* pos_e,
                 IN const uint8_t* upc,
                 IN const uint32_t threshold);

_INLINE_ void fix_error1(IN OUT syndrome_t* s,
                         IN OUT e_t* e, 
                         IN OUT decode_ctx_t* ctx,
                         IN const sk_t* sk,
                         IN const ct_t* ct)
{
    find_error1(e, &ctx->black_e, &ctx->gray_e, 
                ctx->upc, 
                ctx->threshold, 
                ctx->threshold - ctx->delta + 1);

    recompute_syndrome(s, ct, sk, e);
}

_INLINE_ void fix_black_error(IN OUT syndrome_t* s,
                              IN OUT e_t* e, 
                              IN OUT decode_ctx_t* ctx,
                              IN const sk_t* sk,
                              IN const ct_t* ct)
{
    find_error2(e, &ctx->black_e, ctx->upc, ((DV+1)/2)+1);
    recompute_syndrome(s, ct, sk, e);
}

_INLINE_ void fix_gray_error(IN OUT syndrome_t* s,
                             IN OUT e_t* e, 
                             IN OUT decode_ctx_t* ctx,
                             IN const sk_t* sk,
                             IN const ct_t* ct)
{
    find_error2(e, &ctx->gray_e, ctx->upc, ((DV+1)/2)+1);
    recompute_syndrome(s, ct, sk, e);
}

#else

_INLINE_ void update_e(IN OUT e_t* e, 
                       IN const uint32_t pos, 
                       IN const uint8_t part)
{
    const uint32_t transpose_pos = (pos == 0 ? 0 : (R_BITS - pos)) + (part*R_BITS);
    const uint32_t byte_pos = (transpose_pos >> 3);
    const uint32_t bit_pos = (transpose_pos & 0x7);

    e->raw[byte_pos] ^= BIT(bit_pos);
    EDMSG("      flipping position: %u transpose %u byte_pos %u\n", (uint32_t)(pos + (part*R_BITS)), transpose_pos, byte_pos);
}

_INLINE_ void fix_error1(IN OUT syndrome_t* s,
                         IN OUT e_t* e, 
                         IN OUT decode_ctx_t* ctx,
                         IN const sk_t* sk,
                         IN const ct_t* ct)
{
    UNUSED(ct);

    for (uint64_t j = 0; j < N0; j++)
    {
        ctx->num_black_pos[j] = 0;
        ctx->num_gray_pos[j] = 0;

        for (uint64_t i = 0; i < R_BITS; i++)
        {
            if (ctx->upc[i + (j*R_BITS)] >= ctx->threshold)
            {
                ctx->black_pos[j][ctx->num_black_pos[j]++] = i;
                update_e(e, i, j);
            }
            else if(ctx->upc[i + (j*R_BITS)] > ctx->threshold - ctx->delta) 
            {
                ctx->gray_pos[j][ctx->num_gray_pos[j]++] = i;
            }
        }

        recompute(s, ctx->num_black_pos[j], ctx->black_pos[j], &sk->wlist[j]);
    }
    
}

_INLINE_ void fix_black_error(IN OUT syndrome_t* s,
                              IN OUT e_t* e, 
                              IN OUT decode_ctx_t* ctx,
                              IN const sk_t* sk,
                              IN const ct_t* ct)
{
    UNUSED(ct);

    for (uint64_t j = 0; j < N0; j++)
    {
        ctx->num_unflip_pos[j] = 0;
        for (uint64_t i = 0; i < ctx->num_black_pos[j]; i++)
        {
            uint32_t pos = ctx->black_pos[j][i];
            if (ctx->upc[pos + (j*R_BITS)] > (DV+1)/2)
            {
                ctx->unflip_pos[j][ctx->num_unflip_pos[j]++] = pos;
                update_e(e, pos, j);
            }
        }
        recompute(s, ctx->num_unflip_pos[j], ctx->unflip_pos[j], &sk->wlist[j]);
    }
}

_INLINE_ void fix_gray_error(IN OUT syndrome_t* s,
                             IN OUT e_t* e, 
                             IN OUT decode_ctx_t* ctx,
                             IN const sk_t* sk,
                             IN const ct_t* ct)
{
    UNUSED(ct);

    for (uint64_t j = 0; j < N0; j++)
    {
        ctx->num_gray_pos_to_flip[j] = 0;
        for (uint64_t i = 0; i < ctx->num_gray_pos[j]; i++)
        {
            uint32_t pos = ctx->gray_pos[j][i];
            if (ctx->upc[pos + (j*R_BITS)] > (DV+1)/2)
            {
                ctx->gray_pos_to_flip[j][ctx->num_gray_pos_to_flip[j]++] = pos;
                update_e(e, pos, j);
            }
        }
        recompute(s, ctx->num_gray_pos_to_flip[j], ctx->gray_pos_to_flip[j], &sk->wlist[j]);
    }
}

#endif

int decode(OUT e_t* e,
           OUT syndrome_t* s,
           IN const ct_t* ct,
           IN const sk_t* sk)
{
    int code_ret = -1;
    syndrome_t original_s;

#ifdef CONSTANT_TIME
    decode_ctx_t ctx = {0};
#else
    //No need to init (performance)
    decode_ctx_t ctx;
    UNUSED(ct);
#endif
    
    ALIGN(16) compressed_idx_dv_t inv_h_compressed[N0] = {0};
    for (uint64_t i = 0; i < FAKE_DV; i++)
    {
        inv_h_compressed[0].val[i].val = R_BITS - sk->wlist[0].val[i].val;
        inv_h_compressed[1].val[i].val = R_BITS - sk->wlist[1].val[i].val; 

#ifdef CONSTANT_TIME
        inv_h_compressed[0].val[i].used = sk->wlist[0].val[i].used;
        inv_h_compressed[1].val[i].used = sk->wlist[1].val[i].used;
#endif
    }

    original_s.dup1 = s->dup1;

    for(ctx.delta = MAX_DELTA; 
        (ctx.delta >= 0) && (!iszero(s->dup1.raw, sizeof(s->dup1))); 
        ctx.delta--)
    {
        //Reset the error
        memset(e, 0, sizeof(*e));
        
        //Reset the syndrom
        s->dup1 = original_s.dup1;
        s->dup2 = original_s.dup1;

        for (uint32_t iter = 0; iter < MAX_IT; iter++)
        {
            DMSG("    Iteration: %d\n", iter);
            DMSG("    Weight of e: %llu\n", count_ones(e->raw, sizeof(*e)));
            DMSG("    Weight of syndrome: %llu\n", count_ones(s->dup1.raw, sizeof(s->dup1)));

            compute_counter_of_unsat(ctx.upc, s->raw, &inv_h_compressed[0], &inv_h_compressed[1]);

#ifdef FIXED_TH
            ctx.threshold = get_fixed_threshold(&s->dup1, iter);
#else //ADHOC_TH
            ctx.threshold = get_adhoc_threshold(&ctx);
#endif
            fix_error1(s, e, &ctx, sk, ct);

            // Decoding Step I: check if syndrome is 0 (successful decoding)
            if (iszero(s->dup1.raw, sizeof(s->dup1)))
            {
                code_ret = 0;
                break;
            }

            DMSG("    Weight of e: %llu\n", count_ones(e->raw, sizeof(*e)));
            DMSG("    Weight of syndrome: %llu\n", count_ones(s->dup1.raw, sizeof(s->dup1)));

            //Make sure both duplication are the same!
            memcpy(s->dup2.raw, s->dup1.raw, sizeof(s->dup1));

            // Recompute the UPC
            compute_counter_of_unsat(ctx.upc, s->raw, &inv_h_compressed[0], &inv_h_compressed[1]);

            // Decoding Step II: Unflip positions that still have high number of UPC associated
            fix_black_error(s, e, &ctx, sk, ct);
            
            DMSG("    Weight of e: %llu\n", count_ones(e->raw, sizeof(*e)));
            DMSG("    Weight of syndrome: %llu\n", count_ones(s->dup1.raw, sizeof(s->dup1)));

            // Decoding Step II: Check if syndrome is 0 (successful decoding)
            if (iszero(s->dup1.raw, sizeof(s->dup1)))
            {
                code_ret = 0;
                break;
            }

            //Make sure both duplication are the same!
            memcpy(s->dup2.raw, s->dup1.raw, sizeof(s->dup1));

            //Recompute UPC
            compute_counter_of_unsat(ctx.upc, s->raw, &inv_h_compressed[0], &inv_h_compressed[1]);
    
            // Decoding Step III: Flip all gray positions associated to high number of UPC 
            fix_gray_error(s, e, &ctx, sk, ct);
        
            // Decoding Step III: Check for successful decoding
            if (iszero(s->dup1.raw, sizeof(s->dup1)))
            {
                code_ret = 0;
                break;
            }
            
            //Make sure both duplication are the same!
            memcpy(s->dup2.raw, s->dup1.raw, sizeof(s->dup1));
        }
    }
    
    DMSG("    Weight of syndrome: 0\n");

    return code_ret;
}
