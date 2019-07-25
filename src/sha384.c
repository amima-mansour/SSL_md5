/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:59:08 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 09:59:40 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void		init_sha384(t_sha512_context *c)
{
	c->len = 0;
	c->state[0] = 0xcbbb9d5dc1059ed8;
	c->state[1] = 0x629a292a367cd507;
	c->state[2] = 0x9159015a3070dd17;
	c->state[3] = 0x152fecd8f70e5939;
	c->state[4] = 0x67332667ffc00b31;
	c->state[5] = 0x8eb44a8768581511;
	c->state[6] = 0xdb0c2e0d64f98fa7;
	c->state[7] = 0x47b5481dbefa4fa4;
}

void				sha384(char *msg, t_flags flags, char *filename)
{
	t_sha512_context	c;
	t_u8				*new_msg;

	init_sha384(&c);
	if ((c.len = prepare_msg_sha512(msg, &new_msg)))
	{
		hash_sha_512(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha512(c, flags, filename, "SHA384");
	}
}
