/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:41:19 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 13:49:20 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char *p;
	char *str;

	p = (char*)ptr;
	if (size <= (ft_strlen(p) + 1))
		return (ptr);
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	if ((str = (char*)malloc(sizeof(char*) * size)))
	{
		ft_strncpy(str, p, size);
		free(ptr);
		ptr = NULL;
	}
	return ((void*)str);
}
