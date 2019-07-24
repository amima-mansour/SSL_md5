/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:48:17 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 13:58:57 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void				init_sha256(t_sha256_context *c)
{
	c->len = 0;
	c->state[0] = 0x6a09e667;
	c->state[1] = 0xbb67ae85;
	c->state[2] = 0x3c6ef372;
	c->state[3] = 0xa54ff53a;
	c->state[4] = 0x510e527f;
	c->state[5] = 0x9b05688c;
	c->state[6] = 0x1f83d9ab;
	c->state[7] = 0x5be0cd19;
}


void						sha256(char *msg, t_flags flags, char *filename)
{
	t_sha256_context		c;
	uint8_t				*new_msg;

	init_sha256(&c);
	if ((c.len = prepare_msg(msg, &new_msg)))
	{
		hash_sha_256(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha256(c, flags, filename, "SHA256");
	}
}
