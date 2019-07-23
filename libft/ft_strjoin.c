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
	size_t	len;

	if (!s2)
		return (NULL);
	len = (!s1) ? 0: ft_strlen(s1);
	str = ft_strnew(ft_strlen(s2) + len);
	if (str)
	{
		i = -1;
		j = 0;
		while (++i < len)
			str[i] = s1[i];
		while (s2[j])
		{
			str[i + j] = s2[j];
			j++;
		}
		str[i + j] = '\0';
	}
	return (str);
}
