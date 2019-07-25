/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:41:41 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 11:41:47 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void	init_sha512224(t_sha512_context *c)
{
	c->len = 0;
	c->state[0] = 0x8C3D37C819544DA2;
	c->state[1] = 0x73E1996689DCD4D6;
	c->state[2] = 0x1DFAB7AE32FF9C82;
	c->state[3] = 0x679DD514582F9FCF;
	c->state[4] = 0x0F6D2B697BD44DA8;
	c->state[5] = 0x77E36F7304C48942;
	c->state[6] = 0x3F9D85A86A1D36C8;
	c->state[7] = 0x1112E6AD91D692A1;
}

void			sha512224(char *msg, t_flags flags, char *filename)
{
	t_sha512_context		c;
	t_u8					*new_msg;

	init_sha512224(&c);
	if ((c.len = prepare_msg_sha512(msg, &new_msg)))
	{
		hash_sha_512(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha512(c, flags, filename, "SHA512224");
	}
}
