/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 20:23:47 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 17:37:55 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	while (n >= ft_strlen(little) && *big)
	{
		if (!ft_memcmp((void const*)big, (void const*)little,
					ft_strlen(little)))
			return ((char*)big);
		big++;
		n--;
	}
	return (NULL);
}
