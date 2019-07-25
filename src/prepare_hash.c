/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:22:36 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:30:22 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

t_u64				prepare_msg_sha512(char *msg, t_u8 **new_msg)
{
	size_t		len;
	t_u64		new_len;

	len = ft_strlen(msg);
	new_len = len * 8 + 1;
	while (new_len % 1024 != 896)
		new_len++;
	new_len /= 8;
	if (!((*new_msg) = ft_calloc(new_len + 128, 1)))
		return (0);
	ft_memcpy((*new_msg), msg, len);
	(*new_msg)[len] = 128;
	return (new_len);
}

t_u32				prepare_msg(char *msg, t_u8 **new_msg)
{
	size_t		len;
	int			new_len;

	len = ft_strlen(msg);
	new_len = len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	if (!((*new_msg) = ft_calloc(new_len + 64, 1)))
		return (0);
	ft_memcpy((*new_msg), msg, len);
	(*new_msg)[len] = 128;
	return (new_len);
}
