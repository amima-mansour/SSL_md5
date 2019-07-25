/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:22:36 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 18:56:14 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

U64	prepare_msg_sha512(char *msg, U8 **new_msg)
{
	size_t		len;
	U64	new_len;

	len = ft_strlen(msg);
	new_len = len * 8 + 1;
	while (new_len % 1024 != 896)
		new_len++;
	new_len /= 8;
	if (!((*new_msg) = ft_calloc(new_len + 128, 1)))
		return (0);
	ft_memcpy((*new_msg), msg, len);
	(*new_msg)[len] = 128;
	return (new_len);
}

U32	prepare_msg(char *msg, U8 **new_msg)
{
	size_t		len;
	int			new_len;

	len = ft_strlen(msg);
	new_len = len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	if (!((*new_msg) = ft_calloc(new_len + 64, 1)))
		return (0);
	ft_memcpy((*new_msg), msg, len);
	(*new_msg)[len] = 128;
	return (new_len);
}

void		init_flags(t_flags *flags)
{
	flags->r = 0;
	flags->p = 0;
	flags->s = 0;
	flags->q = 0;
	flags->str = NULL;
}

int			flags_check(char **argv, int argc, t_flags *flags, int start)
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

void		(*cmd_check(char *cmd))(char*, t_flags, char*)
{
	t_hash_functions hash[NB_FUNCTIONS];

	hash[0].name = "md5";
	hash[1].name = "sha256";
	hash[3].name = "sha512";
	hash[2].name = "sha224";
	hash[4].name = "sha384";
	hash[0].f = &md5;
	hash[1].f = &sha256;
	hash[2].f = &sha224;
	hash[3].f = &sha512;
	hash[4].f = &sha384;
	if (ft_strcmp(cmd, "md5") == 0)
		return (&md5);
	if (ft_strcmp(cmd, "sha256") == 0)
		return (&sha256);
	if (ft_strcmp(cmd, "sha512") == 0)
		return (&sha512);
	if (ft_strcmp(cmd, "sha224") == 0)
		return (&sha224);
	if (ft_strcmp(cmd, "sha384") == 0)
		return (&sha384);
	cmd_error(hash, cmd);
	return (NULL);
}

char		*file_check(char *arg, char *cmd)
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
