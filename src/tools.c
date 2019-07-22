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

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char			*d;
	const	char	*s;

	s = src;
	d = dest;
	while (len--)
		*d++ = *s++;
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*block;

	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	return (block);
}
