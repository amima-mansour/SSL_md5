/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:02:45 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 14:15:00 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_inverse(void *buff1, void *buff2, size_t size)
{
	size_t	j;
	char	temp;

	if (buff1 && buff2)
	{
		j = 0;
		while (j < size)
		{
			temp = ((char*)buff1)[j];
			((char*)buff1)[j] = ((char*)buff2)[j];
			((char*)buff2)[j] = temp;
			j++;
		}
	}
}
