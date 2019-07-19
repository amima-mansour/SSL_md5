/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:33:17 by amansour          #+#    #+#             */
/*   Updated: 2017/09/14 10:40:08 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# define BUFF_SIZE 200

typedef struct	s_r
{
	int			fd;
	char		*s;
	struct s_r	*nxt;
}				t_r;

int				get_next_line(const int fd, char **line);

#endif
