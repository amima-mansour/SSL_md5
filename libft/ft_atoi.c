/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:44:06 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 17:10:06 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_blanks(char const *str)
{
	while ((*str >= 7 && *str <= 13) || *str == 32)
	{
		str++;
	}
	return ((char *)str);
}

static int	ft_result(char *str, int sign)
{
	int n;

	n = 0;
	while (*str && ft_isdigit(*str))
	{
		n = n * 10 + sign * (*str - '0');
		str++;
	}
	return (n);
}

int			ft_atoi(char const *s)
{
	int		sign;
	char	*str;

	sign = 1;
	str = ft_blanks(s);
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '+' || str[0] == '-')
		str++;
	return (ft_result(str, sign));
}
