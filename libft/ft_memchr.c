/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 18:29:32 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 09:12:54 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char const	*str;

	str = (unsigned char const*)s;
	while (n != 0)
	{
		if (*str == (unsigned char)c)
			return ((void*)str);
		n--;
		str++;
	}
	return (NULL);
}
