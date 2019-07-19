/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 16:03:53 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 15:03:17 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*str1;
	char const	*str2;

	str1 = (char*)dest;
	str2 = (char const*)src;
	if (str2 > str1)
		return (ft_memcpy(dest, src, n));
	else if (str1 == str2)
		return (dest);
	else
		while (n-- > 0)
			str1[n] = str2[n];
	return (dest);
}
