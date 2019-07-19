/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:30:01 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 17:13:07 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int n, int fd)
{
	int		sign;
	char	end;
	int		pow;
	char	c;

	sign = (n < 0) ? -1 : 1;
	if (n < 0)
		write(fd, "-", 1);
	end = '0' + sign * (n % 10);
	pow = 1;
	if (!(n = sign * (n / 10)))
	{
		write(fd, &end, 1);
		return ;
	}
	while (n / pow)
		pow *= 10;
	while (pow != 1)
	{
		pow /= 10;
		c = '0' + n / pow;
		write(fd, &c, 1);
		n %= pow;
	}
	write(fd, &end, 1);
}
