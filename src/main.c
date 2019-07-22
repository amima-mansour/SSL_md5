/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:47 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 18:45:02 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/ft_ssl.h"

static	void		hash_stdin(t_flags flag, void (*cmd)(char*, t_flags, char*))
{
	char	*str;

	get_next_line(0, &str);
	if (flag.p)
		ft_putendl(str);
	cmd(str, flag, NULL);
	free(str);
}

static	void		hash_file(t_flags flags, void (*cmd)(char*, t_flags, char*),
		char *s, char *c)
{
	char *msg;

	if ((msg = file_check(s, c)))
	{
		cmd(msg, flags, s);
		free(msg);
	}
}

int					main(int argc, char **argv)
{
	t_flags	flags;
	void	(*cmd)(char*, t_flags, char*);
	int		i;

	(argc < 2) ? usage() : 0;
	cmd = cmd_check(argv[1]);
	i = flags_check(argv, argc, &flags, 1);
	if (flags.p || (!flags.s && (i == argc)))
		hash_stdin(flags, cmd);
	while (flags.str)
	{
		cmd(flags.str, flags, flags.str);
		flags.str = NULL;
		i = flags_check(argv, argc, &flags, i - 1);
	}
	while (i < argc)
	{
		hash_file(flags, cmd, argv[i], argv[1]);
		i++;
	}
	return (0);
}
