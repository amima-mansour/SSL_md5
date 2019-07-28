/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:08:53 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 09:43:41 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	const	t_u32	g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

static	const	t_u32	g_t[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void						print_md5(t_md5_context c, t_flags flags, char *f)
{
	char *s;

	s = str_msg_md5(c);
	if (s)
	{
		print_hash(s, flags, f, "MD5");
		free(s);
	}
}

static	void				init_md5(t_md5_context *context)
{
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
	context->len = 0;
}

static	void				put_in_variable(t_md5_context *c,
			t_u32 f, t_u32 w, t_u32 i)
{
	t_u32 temp;

	temp = c->var[3];
	c->var[3] = c->var[2];
	c->var[2] = c->var[1];
	c->var[1] += ROTLEFT((c->var[0] + f + g_t[i] + w), g_s[i]);
	c->var[0] = temp;
}

static	void				subtreat_md5(t_md5_context *c, t_u32 *w)
{
	t_u32 i;
	t_u32 g;

	i = -1;
	while (++i < 16)
		put_in_variable(c, F(c->var[1], c->var[2], c->var[3]), w[i], i);
	while (i < 32)
	{
		g = (5 * i + 1) % 16;
		put_in_variable(c, G(c->var[1], c->var[2], c->var[3]), w[g], i++);
	}
	while (i < 48)
	{
		g = (3 * i + 5) % 16;
		put_in_variable(c, H(c->var[1], c->var[2], c->var[3]), w[g], i++);
	}
	while (i < 64)
	{
		g = (7 * i) % 16;
		put_in_variable(c, I(c->var[1], c->var[2], c->var[3]), w[g], i++);
	}
}

void						md5(char *msg, t_flags f, char *filename, t_u64 l)
{
	t_u64				offset;
	t_md5_context		c;
	t_u8				*new_msg;
	t_u64				len_bits;

	init_md5(&c);
	len_bits = l * 8;
	if ((c.len = prepare_msg(msg, &new_msg, l)))
	{
		ft_memcpy_64(new_msg + c.len, &(len_bits), 4);
		offset = 0;
		while (offset < c.len)
		{
			c.i = -1;
			while (++(c.i) < 4)
				c.var[c.i] = c.state[c.i];
			subtreat_md5(&c, (t_u32 *)(new_msg + offset));
			offset += 64;
			c.i = -1;
			while (++(c.i) < 4)
				c.state[c.i] += c.var[c.i];
		}
		free(new_msg);
		print_md5(c, f, filename);
	}
}
