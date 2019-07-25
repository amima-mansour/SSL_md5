/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:46:26 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 11:43:29 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

void			init_flags(t_flags *flags)
{
	flags->r = 0;
	flags->p = 0;
	flags->s = 0;
	flags->q = 0;
	flags->str = NULL;
}

void			all_cmd(t_hash_functions hash[])
{
	hash[0].name = "md5";
	hash[1].name = "sha256";
	hash[3].name = "sha512";
	hash[2].name = "sha224";
	hash[4].name = "sha384";
	hash[5].name = "sha512256";
	hash[6].name = "sha512224";
	hash[0].f = &md5;
	hash[1].f = &sha256;
	hash[2].f = &sha224;
	hash[3].f = &sha512;
	hash[4].f = &sha384;
	hash[6].f = &sha512224;
	hash[5].f = &sha512256;
}

int				flags_check(char **argv, int argc, t_flags *flags, int start)
{
	if (start == 1)
		init_flags(flags);
	while (++start < argc)
	{
		if (ft_strcmp(argv[start], "-r") == 0)
			flags->r = 1;
		else if (ft_strcmp(argv[start], "-p") == 0)
			flags->p = 1;
		else if (ft_strcmp(argv[start], "-s") == 0)
		{
			flags->s = 1;
			if (++start == argc)
				s_error(argv[1]);
			else
				flags->str = argv[start++];
			break ;
		}
		else if (ft_strcmp(argv[start], "-q") == 0)
			flags->q = 1;
		else if (argv[start][0] == '-')
			flag_error(argv[start][1], argv[1]);
		else
			break ;
	}
	return (start);
}

void			cmd_check(char *s, void (**cmd)(char*, t_flags, char*))
{
	t_hash_functions hash[NB_FUNCTIONS];

	all_cmd(hash);
	if (ft_strcmp(s, "md5") == 0)
		*cmd = &md5;
	else if (ft_strcmp(s, "sha256") == 0)
		*cmd = &sha256;
	else if (ft_strcmp(s, "sha512") == 0)
		*cmd = &sha512;
	else if (ft_strcmp(s, "sha224") == 0)
		*cmd = &sha224;
	else if (ft_strcmp(s, "sha384") == 0)
		*cmd = &sha384;
	else if (ft_strcmp(s, "sha512256") == 0)
		*cmd = &sha512256;
	else if (ft_strcmp(s, "sha512224") == 0)
		*cmd = &sha512224;
	else
		cmd_error(hash, s);
}

char			*file_check(char *arg, char *cmd)
{
	char	*str;
	char	ch;
	int		fd;
	size_t	i;

	str = NULL;
	i = 0;
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		file_error(cmd, arg);
		return (str);
	}
	while (read(fd, &ch, 1) > 0)
		i++;
	close(fd);
	str = (char*)malloc(sizeof(char) * (i + 1));
	if ((fd = open(arg, O_RDONLY)) > 0)
		i = 0;
	while (read(fd, &ch, 1) > 0)
		str[i++] = ch;
	str[i] = '\0';
	return (str);
}
