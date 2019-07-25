/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 10:00:06 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:00:56 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void	init_sha512(t_sha512_context *c)
{
	c->len = 0;
	c->state[0] = 0x6A09E667F3BCC908;
	c->state[1] = 0xBB67AE8584CAA73B;
	c->state[2] = 0x3C6EF372FE94F82B;
	c->state[3] = 0xA54FF53A5F1D36F1;
	c->state[4] = 0x510E527FADE682D1;
	c->state[5] = 0x9B05688C2B3E6C1F;
	c->state[6] = 0x1F83D9ABFB41BD6B;
	c->state[7] = 0x5BE0CD19137E2179;
}

void			print_sha512(t_sha512_context c, t_flags fl, char *f, char *s1)
{
	char *s;

	if (ft_strcmp(s1, "SHA512") == 0)
		s = str_msg_sha(NULL, &c, 64, WORD_64);
	else if (ft_strcmp(s1, "SHA384") == 0)
		s = str_msg_sha(NULL, &c, 48, WORD_64);
	else if (ft_strcmp(s1, "SHA512224") == 0)
		s = str_msg_sha(NULL, &c, 28, WORD_64);
	else
		s = str_msg_sha(NULL, &c, 32, WORD_64);
	if (s)
	{
		print_hash(s, fl, f, s1);
		free(s);
	}
}

void			sha512(char *msg, t_flags flags, char *filename)
{
	t_sha512_context		c;
	t_u8					*new_msg;

	init_sha512(&c);
	if ((c.len = prepare_msg_sha512(msg, &new_msg)))
	{
		hash_sha_512(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha512(c, flags, filename, "SHA512");
	}
}
