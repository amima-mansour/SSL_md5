/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:51:52 by amansour          #+#    #+#             */
/*   Updated: 2017/09/14 10:42:11 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"
#include "../libft/libft.h"

t_r			*build_strcuture(const int fd, t_r **get)
{
	t_r *m;
	t_r *c;

	c = *get;
	while (c && c->fd != fd)
		c = c->nxt;
	if (!c && (m = (t_r*)malloc(sizeof(t_r))))
	{
		m->fd = fd;
		m->nxt = NULL;
		m->s = NULL;
		if ((c = *get))
		{
			while (c->nxt)
				c = c->nxt;
			c->nxt = m;
		}
		else
			*get = m;
		return (m);
	}
	return (c);
}

size_t		ft_end(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	return (i);
}

void		ft_build(char **str, char *s)
{
	char *s2;

	s2 = NULL;
	if ((s2 = (char*)malloc(sizeof(char) * (ft_strlen(*str) +
						ft_strlen(s) + 1))))
	{
		if (**str)
			ft_strcpy(s2, *str);
		ft_strncat(s2, s, ft_strlen(s));
		s2[ft_strlen(s) + ft_strlen(*str)] = '\0';
	}
	if (**str)
		free(*str);
	*str = s2;
	return ;
}

int			get_line(char **line, char **str)
{
	if ((*str) && ft_strlen(*str) != ft_end(*str))
	{
		*str = *str + (ft_end(*str) + 1);
		(*line)[ft_end(*line)] = '\0';
		return (1);
	}
	*str = NULL;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_r	*get;
	t_r			*current;
	int			i;
	char		*str;

	if (!line || fd < 0 || !(current = build_strcuture(fd, &get))
			|| !(str = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	*line = (current->s) ? ft_strdup(current->s) : "\0";
	if (get_line(line, &(current->s)) == 1)
		return (1);
	while (((i = read(fd, str, BUFF_SIZE)) == BUFF_SIZE) &&
			(!(ft_memchr((void*)str, '\n', BUFF_SIZE))))
		ft_build(line, str);
	if (i <= 0 && !(*line)[0])
		return (i);
	str[i] = '\0';
	current->s = ft_strdup(str);
	ft_build(line, str);
	free(str);
	get_line(line, &(current->s));
	return (1);
}
