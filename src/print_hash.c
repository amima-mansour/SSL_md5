/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:10:35 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 13:25:20 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	char	*str_msg_md5(t_md5_context c)
{
	uint8_t		*p;
	int			i;
	char		*str;
	int			j;

	i = -1;
	j = 0;
	if (!(str = (char*)malloc(32)))
		return (NULL);
	while (++i < 4)
	{
		p = (uint8_t *)&(c.state[i]);
		convert_to_hex((char)p[0], str + j);
		convert_to_hex((char)p[1], str + j + 2);
		convert_to_hex((char)p[2], str + j + 4);
		convert_to_hex((char)p[3], str + j + 6);
		j += 8;
	}
	str[j] = '\0';
	return (str);
}

static	char	*str_msg_sha(t_sha256_context *c1, t_sha512_context *c2, int d, int w)
{
	char	hash[d + 1];
	char	*s;
	int		i;

	i = -1;
	if (c1)
		while (++i  < d)
			hash[i] = (c1->state[i / w] >> ((w - 1 - (i % w)) * 8)) & 0xFF;
	else
		while (++i  < d)
			hash[i] = (c2->state[i / w] >> ((w - 1 - (i % w)) * 8)) & 0xFF;
	hash[d] = '\0';
	i = -1;
	if (!(s = (char*)malloc(2 * d + 1)))
		return (NULL);
	s[2 * d] = '\0';
	i = -1;
	while (++i < d)
		convert_to_hex(hash[i], s + 2 * i);
	return (s);
}

void			print_hash(char *s, t_flags flags, char *filename, char *cmd)
{
	if ((filename || (flags.s && filename)) && !flags.r && !flags.q)
	{
		ft_putstr(cmd);
		ft_putstr(" (");
		if (flags.s && flags.str)
			ft_putstr("\"");
		ft_putstr(filename);
		if (flags.s && flags.str)
			ft_putstr("\"");
		ft_putstr(") = ");
	}
	ft_putstr(s);
	if (filename && !flags.q && flags.r)
	{
		ft_putstr(" ");
		ft_putstr(filename);
	}
	ft_putstr("\n");
}

void			print_sha256(t_sha256_context c, t_flags flags, char *f, char *str)
{
	char *s;

	if (ft_strcmp(str, "SHA256") == 0)
		s = str_msg_sha(&c, NULL, 32, WORD);
	else
		s = str_msg_sha(&c, NULL, 28, WORD);
	if (s)
	{
		print_hash(s, flags, f, str);
		free(s);
	}
}

void			print_md5(t_md5_context c, t_flags flags, char *f)
{
	char *s;

	s = str_msg_md5(c);
	if (s)
	{
		print_hash(s, flags, f, "MD5");
		free(s);
	}
}

void			print_sha512(t_sha512_context c, t_flags flags, char *f, char *str)
{
	char *s;

	if (ft_strcmp(str, "SHA512") == 0)
		s = str_msg_sha(NULL, &c, 64, WORD_64);
	else
		s = str_msg_sha(NULL, &c, 48, WORD_64);
	if (s)
	{
		print_hash(s, flags, f, str);
		free(s);
	}
}
