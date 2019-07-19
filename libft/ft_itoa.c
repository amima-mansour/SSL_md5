/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 17:24:52 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 14:42:35 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_str(int n, size_t index, int sign)
{
	char	*str;

	if ((str = ft_strnew(index)))
	{
		str[index] = '\0';
		str[--index] = n % 10 + '0';
		n /= 10;
		while (n)
		{
			--index;
			str[index] = n % 10 + '0';
			n /= 10;
		}
		if (sign == -1)
			str[0] = '-';
	}
	return (str);
}

static char		*ft_min(void)
{
	char *str;

	if ((str = (char*)malloc(sizeof(char) * 12)))
	{
		str[0] = '-';
		str[1] = '2';
		str[2] = '1';
		str[3] = '4';
		str[4] = '7';
		str[5] = '4';
		str[6] = '8';
		str[7] = '3';
		str[8] = '6';
		str[9] = '4';
		str[10] = '8';
		str[11] = 0;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	int		sign;
	size_t	index;
	int		nb;

	sign = 1;
	index = 1;
	if (n == -2147483648)
		return (ft_min());
	nb = n;
	if (n < 0)
	{
		sign = -1;
		index += 1;
		nb = -nb;
	}
	n /= 10;
	while (n)
	{
		index++;
		n /= 10;
	}
	return (ft_str(nb, index, sign));
}
