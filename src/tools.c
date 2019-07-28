/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:47:15 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 18:49:26 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

void	convert_to_hex(unsigned char nb, char *s)
{
	s[0] = HEXBASE[nb / 16];
	s[1] = HEXBASE[nb % 16];
}

int		ft_strcmp(char const *str1, char const *str2)
{
	unsigned char	*s2;
	unsigned char	*s1;
	size_t			i;

	i = 0;
	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	*ft_memcpy_64(void *dest, const void *src, t_u64 len)
{
	char			*d;
	const	char	*s;

	s = src;
	d = dest;
	while (len--)
		*d++ = *s++;
	return (dest);
}

void	*ft_calloc(t_u64 nmemb, size_t size)
{
	void	*block;

	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	return (block);
}

char	*ft_strjoin_s(char const *s1, char const *s2, t_u64 l)
{
	char	*str;
	t_u64	i;
	size_t	j;
	t_u64	limit;

	if ((str = (char*)malloc(l + 1)))
	{
		i = -1;
		j = 0;
		limit = (l / BUF - 1) * BUF;
		if (l % BUF != 0)
			limit = l - l % BUF;
		while (++i < limit)
			str[i] = s1[i];
		while (i < l)
		{
			str[i] = s2[j];
			++j;
			++i;
		}
		str[l] = '\0';
	}
	return (str);
}
