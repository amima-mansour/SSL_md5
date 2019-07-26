/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_sha2_256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:35:20 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:25:01 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static const t_u32 g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static	void		add_len(t_u8 **msg, t_u64 bits, t_u32 len)
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

static	void		round_sha256(t_sha256_context *ctx, t_u32 *m)
{
	t_u32 i;

	i = -1;
	while (++i < 64)
	{
		ctx->t1 = ctx->var[7] + EP1(ctx->var[4]) + CH(ctx->var[4],
				ctx->var[5], ctx->var[6]) + g_k[i] + m[i];
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

static	void		subtreat_sha256(t_sha256_context *ctx, t_u8 *w)
{
	t_u32 i;
	t_u32 m[64];

	i = -1;
	while (++i < 16)
		m[i] = (((t_u32)w[WORD * i]) << (WORD_BITS - 8)) |
			(((t_u32)w[WORD * i + 1]) << (WORD_BITS - 16)) |
			(((t_u32)w[WORD * i + 2]) << (WORD_BITS - 24)) |
			(((t_u32)w[WORD * i + 3]) << (WORD_BITS - 32));
	i--;
	while (++i < 64)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
	i = -1;
	while (++i < 8)
		ctx->var[i] = ctx->state[i];
	round_sha256(ctx, m);
	i = -1;
	while (++i < 8)
		ctx->state[i] += ctx->var[i];
}

void				hash_sha_256(t_sha256_context *c, t_u8 **new_msg, t_u64 l)
{
	t_u64 offset;

	offset = 0;
	add_len(new_msg, l * 8, c->len);
	while (offset < c->len)
	{
		subtreat_sha256(c, (t_u8*)(*new_msg + offset));
		offset += 64;
	}
}
