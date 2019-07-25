/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:42:09 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 11:42:13 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void	init_sha512256(t_sha512_context *c)
{
	c->len = 0;
	c->state[0] = 0x22312194FC2BF72C;
	c->state[1] = 0x9F555FA3C84C64C2;
	c->state[2] = 0x2393B86B6F53B151;
	c->state[3] = 0x963877195940EABD;
	c->state[4] = 0x96283EE2A88EFFE3;
	c->state[5] = 0xBE5E1E2553863992;
	c->state[6] = 0x2B0199FC2C85B8AA;
	c->state[7] = 0x0EB72DDC81C52CA2;
}

void			sha512256(char *msg, t_flags flags, char *filename)
{
	t_sha512_context		c;
	t_u8					*new_msg;

	init_sha512256(&c);
	if ((c.len = prepare_msg_sha512(msg, &new_msg)))
	{
		hash_sha_512(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha512(c, flags, filename, "SHA512256");
	}
}
