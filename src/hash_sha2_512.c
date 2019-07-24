#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static const uint64_t g_k[80] = {
    0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F,
    0xE9B5DBA58189DBBC, 0x3956C25BF348B538, 0x59F111F1B605D019,
    0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118, 0xD807AA98A3030242,
    0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
    0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235,
    0xC19BF174CF692694, 0xE49B69C19EF14AD2, 0xEFBE4786384F25E3,
    0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65, 0x2DE92C6F592B0275,
    0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
    0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F,
    0xBF597FC7BEEF0EE4, 0xC6E00BF33DA88FC2, 0xD5A79147930AA725,
    0x06CA6351E003826F, 0x142929670A0E6E70, 0x27B70A8546D22FFC,
    0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
    0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6,
    0x92722C851482353B, 0xA2BFE8A14CF10364, 0xA81A664BBC423001,
    0xC24B8B70D0F89791, 0xC76C51A30654BE30, 0xD192E819D6EF5218,
    0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
    0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99,
    0x34B0BCB5E19B48A8, 0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB,
    0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3, 0x748F82EE5DEFB2FC,
    0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
    0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915,
    0xC67178F2E372532B, 0xCA273ECEEA26619C, 0xD186B8C721C0C207,
    0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178, 0x06F067AA72176FBA,
    0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
    0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC,
    0x431D67C49C100D4C, 0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A,
    0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817
};

static	void				round_sha512(t_sha512_context *ctx, uint64_t *w)
{
    int i;
	int j;

	i = -1;
	while (++i < 80)
	{
		j = -1;
		if (i == 1)
		{
			while(++j < 8)
				printf("%d => %llx ", i, ctx->var[j]);
			printf("\n");
		}
		ctx->t1 = ctx->var[7] + SIGMA1(ctx->var[4]) + CH(ctx->var[4],
				ctx->var[5], ctx->var[6]) + g_k[i] + w[i];
		ctx->t2 = SIGMA0(ctx->var[0]) + MAJ(ctx->var[0], ctx->var[1],
				ctx->var[2]);
        ctx->var[7] = ctx->var[6];
		ctx->var[6] = ctx->var[5];
		ctx->var[5] = ctx->var[4];
		ctx->var[4] = ctx->var[3] + ctx->t1;
		ctx->var[3] = ctx->var[2];
		ctx->var[2] = ctx->var[1];
		ctx->var[1] = ctx->var[0];
		ctx->var[0] = ctx->t1 + ctx->t2;
		j  = -1;
		if (i == 1)
		{
			while(++j < 8)
				printf("%d => %llx ", i, ctx->var[j]);
			printf("\n");
		}
    }
}

static  uint64_t            byteswap64(uint64_t x)
{
    uint32_t a;
    uint32_t b;

    a = x >> 32;
    b = (uint32_t) x;
    return ((uint64_t) BYTESWAP(b) << 32) | (uint64_t) BYTESWAP(a);
}

static	void				subtreat_sha512(t_sha512_context *ctx, uint8_t *w)
{
	uint32_t i;
	uint32_t j;
	uint64_t m[80];

	i = -1;
	j = 0;
	while (++i < 16)
        m[i] = byteswap64(w[i]);
	i--;
	while (++i < 80)
		m[i] = S1(m[i - 2]) + m[i - 7] + S0(m[i - 15]) + m[i - 16];
    i = -1;
	while (++i < 8)
		ctx->var[i] = ctx->state[i];
	round_sha512(ctx, m);
    i = -1;
	while (++i < 8)
		ctx->state[i] += ctx->var[i];
}

static	void				add_len(uint8_t **msg, uint64_t bits, uint64_t len)
{
    int i;

    i = -1;
    while (++i < 8)
        (*msg)[len + i] = 0;
    (*msg)[len + 15] = bits;
	(*msg)[len + 14] = bits >> 8;
	(*msg)[len + 13] = bits >> 16;
	(*msg)[len + 12] = bits >> 24;
	(*msg)[len + 11] = bits >> 32;
	(*msg)[len + 10] = bits >> 40;
	(*msg)[len + 9] = bits >> 48;
    (*msg)[len + 8] = bits >> 56;
}

void		hash_sha_512(t_sha512_context *c, uint8_t **new_msg, size_t len)
{
	uint32_t offset;

	offset = -1;
    add_len(new_msg, len * 8, c->len);
	while(++offset < 128)
		printf("%x", (*new_msg)[offset]);
	printf("\n");
	offset = 0;
	while (offset < c->len)
	{
		subtreat_sha512(c, (uint8_t*)(*new_msg + offset));
		offset += 128;
	}
}
