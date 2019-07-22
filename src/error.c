/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:49:44 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 18:50:56 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

void	usage(void)
{
	ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	exit(-1);
}

void	file_error(char *cmd, char *file)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(cmd);
	ft_putstr(": ");
	ft_putstr(file);
	ft_putstr(": No such file or directory\n");
}

void	cmd_error(t_hash_functions hash[], char *cmd)
{
	int i;

	ft_putstr("ft_ssl: Error: ");
	ft_putstr(cmd);
	ft_putstr(" is an invalid command.\n\n");
	ft_putstr("Standard commands:\n");
	ft_putstr("\nMessage Digest commands:\n");
	i = -1;
	while (++i < NB_FUNCTIONS)
		ft_putendl(hash[i].name);
	ft_putstr("\nCipher commands:\n");
	exit(-1);
}

void	s_error(char *cmd)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(cmd);
	ft_putstr(": option requires an argument -- s\nusage: ft_ssl ");
	ft_putstr(cmd);
	ft_putstr(" [-pqr] [-s string] [files ...]\n");
	exit(-1);
}

void	flag_error(char c, char *cmd)
{
	ft_putstr("ft_ssl: ");
	ft_putstr(cmd);
	ft_putstr(": illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ssl ");
	ft_putstr(cmd);
	ft_putstr(" [-pqr] [-s string] [files ...]\n");
	exit(-1);
}
