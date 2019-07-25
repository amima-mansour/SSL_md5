/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 10:01:18 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:01:32 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

void		read_stdin(char **str)
{
	char	*buf;
	char	*temp;
	char	ch;
	int		i;

	*str = NULL;
	buf = ft_strnew(BUF);
	i = 0;
	while (read(0, &ch, 1) > 0)
	{
		if ((i % BUF) == 0 && i > 0)
		{
			temp = *str;
			*str = ft_strjoin(temp, buf);
			temp ? free(temp) : 0;
			buf ? free(buf) : 0;
			buf = ft_strnew(BUF);
		}
		buf[i++ % BUF] = ch;
	}
	temp = ft_strjoin(*str, buf);
	buf ? free(buf) : 0;
	*str ? free(*str) : 0;
	*str = temp;
}
