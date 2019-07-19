/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 11:12:37 by amansour          #+#    #+#             */
/*   Updated: 2017/05/01 12:54:40 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *scr, size_t size)
{
	int j;
	int len;

	len = (int)ft_strlen(dest);
	if (((int)size - len - 1) <= 0)
		return (ft_strlen(scr) + size);
	j = 0;
	while (scr[j] && ((int)size - len - 1) > j)
	{
		dest[len + j] = scr[j];
		j++;
	}
	dest[len + j] = '\0';
	return ((size_t)len + ft_strlen(scr));
}
