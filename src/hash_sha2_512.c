#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void				round_sha512(t_sha512_context *ctx, uint64_t *w, const uint32_t k[])
{
    int i;
    int j;

	i = -1;
	while (++i < 80)
	{
		ctx->t1 = ctx->var[7] + SIGMA1(ctx->var[4]) + CH(ctx->var[4],
				ctx->var[5], ctx->var[6]) + k[i] + w[i];
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
        j = -1;
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
static	void				subtreat_sha512(t_sha512_context *ctx, uint64_t *w, const uint32_t k[])
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
	round_sha512(ctx, m, k);
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

void		hash_sha_512(t_sha256_context *c, uint8_t **new_msg, size_t len, const uint32_t k[])
{
	uint32_t offset;

	offset = 0;
    add_len(new_msg, len * 8, c->len);
	while (offset < c->len)
	{
		subtreat_sha512(c, (uint8_t*)(*new_msg + offset), k);
		offset += 128;
	}
}