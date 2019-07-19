/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 20:43:39 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 10:27:25 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(big);
	j = ft_strlen(little);
	if (!little)
		return ((char*)big);
	while (i >= j)
	{
		i--;
		if (!ft_memcmp((void const*)big, (void const*)little, j))
			return ((char*)big);
		big++;
	}
	return (NULL);
}
