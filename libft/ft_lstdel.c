/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:37:00 by amansour          #+#    #+#             */
/*   Updated: 2017/04/28 14:59:46 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *maillon;

	while (*alst != NULL)
	{
		maillon = *alst;
		(*alst) = (*alst)->next;
		del(maillon->content, maillon->content_size);
		free(maillon);
		maillon = NULL;
	}
	alst = NULL;
	return ;
}
