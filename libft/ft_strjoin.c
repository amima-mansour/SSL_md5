/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 12:18:23 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 10:10:48 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = ft_strnew(ft_strlen(s2) + ft_strlen(s1) + 1);
	if (str)
	{
		i = 0;
		j = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			++i;
		}
		while (s2[j])
		{
			str[i + j] = s2[j];
			++j;
		}
		str[i + j] = '\0';
	}
	return (str);
}
