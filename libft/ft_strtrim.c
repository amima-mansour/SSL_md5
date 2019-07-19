/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:27:53 by amansour          #+#    #+#             */
/*   Updated: 2017/05/01 11:33:55 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	while (*s && (*s == '\t' || *s == '\n' || *s == ' '))
	{
		s++;
	}
	i = ft_strlen(s) - 1;
	while (i >= 0 && (s[i] == '\t' || s[i] == '\n' || s[i] == ' '))
	{
		i--;
	}
	if ((str = ft_strnew(i + 1)))
	{
		if ((i + 2) != 1)
			ft_strncpy(str, s, i + 1);
		str[i + 1] = '\0';
	}
	return (str);
}
