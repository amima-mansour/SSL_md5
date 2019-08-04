/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:10:35 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:29:02 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/libft.h"

void	convert_to_hex(unsigned char nb, char *s)
{
	s[0] = HEXBASE[nb / 16];
	s[1] = HEXBASE[nb % 16];
}

char	*str_msg_md5(t_md5_context c)
{
	t_u8		*p;
	int			i;
	char		*str;
	int			j;

	i = -1;
	j = 0;
	if (!(str = (char*)malloc(33)))
		return (NULL);
	while (++i < 4)
	{
		p = (t_u8 *)&(c.state[i]);
		convert_to_hex((char)p[0], str + j);
		convert_to_hex((char)p[1], str + j + 2);
		convert_to_hex((char)p[2], str + j + 4);
		convert_to_hex((char)p[3], str + j + 6);
		j += 8;
	}
	str[32] = '\0';
	return (str);
}

char	*str_msg_sha(t_sha256_context *c1, t_sha512_context *c2, int d, int w)
{
	char	hash[d + 1];
	char	*s;
	int		i;

	i = -1;
	if (c1)
		while (++i < d)
			hash[i] = (c1->state[i / w] >> ((w - 1 - (i % w)) * 8)) & 0xFF;
	else
		while (++i < d)
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

void	print_hash(char *s, t_flags flags, char *filename, char *cmd)
{
	if ((flags.s || filename) && !flags.r && !flags.q)
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
		if (flags.s && flags.str)
			ft_putstr("\"");
		ft_putstr(filename);
		if (flags.s && flags.str)
			ft_putstr("\"");
	}
	ft_putstr("\n");
}
