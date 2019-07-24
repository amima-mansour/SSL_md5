#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static void			        add_len(uint8_t **msg, size_t bits, uint32_t len)
{
	(*msg)[len + 7] = bits;
	(*msg)[len + 6] = bits >> 8;
	(*msg)[len + 5] = bits >> 16;
	(*msg)[len + 4] = bits >> 24;
	(*msg)[len + 3] = bits >> 32;
	(*msg)[len + 2] = bits >> 40;
	(*msg)[len + 1] = bits >> 48;
	(*msg)[len] = bits >> 56;
}

static	void				round_sha256(t_sha256_context *ctx, uint32_t *m, const uint32_t k[])
{
	uint32_t i;

	i = -1;
	while (++i < 64)
	{
		ctx->t1 = ctx->var[7] + EP1(ctx->var[4]) + CH(ctx->var[4],
				ctx->var[5], ctx->var[6]) + k[i] + m[i];
		ctx->t2 = EP0(ctx->var[0]) + MAJ(ctx->var[0], ctx->var[1],
				ctx->var[2]);
		ctx->var[7] = ctx->var[6];
		ctx->var[6] = ctx->var[5];
		ctx->var[5] = ctx->var[4];
		ctx->var[4] = ctx->var[3] + ctx->t1;
		ctx->var[3] = ctx->var[2];
		ctx->var[2] = ctx->var[1];
		ctx->var[1] = ctx->var[0];
		ctx->var[0] = ctx->t1 + ctx->t2;
	}
}

static	void				subtreat_sha256(t_sha256_context *ctx, uint8_t *w, const uint32_t k[])
{
	uint32_t i;
	uint32_t j;
	uint32_t m[64];

	i = -1;
	j = 0;
	while (++i < 16)
	{
		m[i] = (w[j] << 24) | (w[j + 1] << 16) | (w[j + 2] << 8) | (w[j + 3]);
		j += 4;
	}
	i--;
	while (++i < 64)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	i = -1;
	while (++i < 8)
		ctx->var[i] = ctx->state[i];
	round_sha256(ctx, m, k);
	i = -1;
	while (++i < 8)
		ctx->state[i] += ctx->var[i];
}

void		hash_sha_256(t_sha256_context *c, uint8_t **new_msg, size_t len, const uint32_t k[])
{
	uint32_t offset;

	offset = 0;
    add_len(new_msg, len * 8, c->len);
	while (offset < c->len)
	{
		subtreat_sha256(c, (uint8_t*)(*new_msg + offset), k);
		offset += 64;
	}
}