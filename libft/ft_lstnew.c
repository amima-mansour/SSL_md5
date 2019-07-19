/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:17:23 by amansour          #+#    #+#             */
/*   Updated: 2017/04/28 15:00:59 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list		*list;
	char		*str;

	list = (t_list*)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		str = (char*)malloc(size * sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strcpy(str, (char const*)content);
		list->content = (void*)str;
		list->content_size = size;
	}
	list->next = NULL;
	return (list);
}
