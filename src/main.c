/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:23:47 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:26:23 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/ft_ssl.h"

static void		hash_stdin(t_flags flags, void (*cmd)(char*, t_flags, char*, t_u64))
{
	char	*str;
	t_u64	len;		

	len = read_stdin(&str);
	flags.p == 1 ? ft_putendl(str) : 0;
	cmd(str, flags, NULL, len);
	free(str);
}

static	void	hash_file(t_flags flags, void (*cmd)(char*, t_flags, char*, t_u64),
		char *s, char *c)
{
	char *msg;
	t_u64	len;

	len = file_check(s, c, &msg);
	if (msg)
	{
		cmd(msg, flags, s, len);
		free(msg);
	}
}

int				main(int argc, char **argv)
{
	t_flags	flags;
	void	(*cmd)(char*, t_flags, char*, t_u64);
	int		i;

	(argc < 2) ? usage() : 0;
	cmd_check(argv[1], &cmd);
	i = flags_check(argv, argc, &flags, 1);
	if (flags.p || (!flags.s && (i == argc)))
		hash_stdin(flags, cmd);
	while (flags.str)
	{
		cmd(flags.str, flags, flags.str, ft_strlen(flags.str));
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
