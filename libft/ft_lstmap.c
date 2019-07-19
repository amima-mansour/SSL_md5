/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 11:12:30 by amansour          #+#    #+#             */
/*   Updated: 2017/04/28 15:00:39 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *element))
{
	t_list *maillon;
	t_list *new;
	t_list *previous;

	if (lst == NULL)
		return (NULL);
	new = (t_list*)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new = f(lst);
	new->next = NULL;
	previous = new;
	lst = lst->next;
	while (lst != NULL)
	{
		maillon = f(lst);
		maillon->next = NULL;
		lst = lst->next;
		previous->next = maillon;
		previous = maillon;
	}
	return (new);
}
