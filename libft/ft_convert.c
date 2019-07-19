/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:30:58 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 14:10:16 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert(char *str, int base_size)
{
	int n;
	int sign;

	n = 0;
	if (!str)
		return (0);
	sign = (str[0] == '-') ? -1 : 1;
	if (sign == -1)
		str++;
	while (*str)
	{
		n *= base_size;
		if (ft_isdigit(*str))
			n += *str - '0';
		if (ft_toupper(*str))
			n += *str - 'A' + 10;
		if (ft_tolower(*str))
			n += *str - 'a' + 10;
		str++;
	}
	return (sign * n);
}
