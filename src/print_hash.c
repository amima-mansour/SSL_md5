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

static	char	*str_msg_sha224(t_sha256_context c)
{
	char	hash[29];
	char	*s;
	int		i;

	i = -1;
	while (++i < 28)
		hash[i] = (c.state[i / 4] >> (( 3 - (i % 4)) * 8)) & 0xFF;
	hash[i] = '\0';
	if (!(s = (char*)malloc(57)))
		return (NULL);
	s[56] = '\0';
	i = -1;
	while (++i < 28)
		convert_to_hex(hash[i], s + 2 * i);
	return (s);
}

static	char	*str_msg_sha256(t_sha256_context c)
{
	char	hash[33];
	char	*s;
	int		i;

	i = -1;
	while (++i < 4)
	{
		hash[i] = (c.state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (c.state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (c.state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (c.state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (c.state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (c.state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (c.state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (c.state[7] >> (24 - i * 8)) & 0x000000ff;
	}
	hash[32] = '\0';
	if (!(s = (char*)malloc(65)))
		return (NULL);
	s[64] = '\0';
	i = -1;
	while (++i < 32)
		convert_to_hex(hash[i], s + 2 * i);
	return (s);
}

static	char	*str_msg_sha512(t_sha512_context c)
{
	char	hash[65];
	char	*s;
	int		i;

	i = -1;
	/* copy output */
    // for (i = 0; i < DIGEST_SIZE; i++)
    //     hash[i] = (hs->state[i / WORD_SIZE] >> 
    //                ((WORD_SIZE - 1 - (i % WORD_SIZE)) * 8)) & 0xFF;
	while (++i  < 64)
		hash[i] = (c.state[i / 8] >> ((7 - (i % 8)) * 8)) & 0xFF;
	hash[64] = '\0';
	i = -1;
	if (!(s = (char*)malloc(129)))
		return (NULL);
	s[128] = '\0';
	i = -1;
	while (++i < 64)
		convert_to_hex(hash[i], s + 2 * i);
	return (s);
}

static	char	*str_msg_sha384(t_sha512_context c)
{
	char	hash[49];
	char	*s;
	int		i;

	i = -1;
  	while (++i  < 48)
		hash[i] = (c.state[i / 8] >> ((7 - (i % 8)) * 8)) & 0xFF;
	hash[48] = '\0';
	if (!(s = (char*)malloc(97)))
		return (NULL);
	s[98] = '\0';
	i = -1;
	while (++i < 48)
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
		s = str_msg_sha256(c);
	else
		s = str_msg_sha224(c);
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
		s = str_msg_sha512(c);
	else
		s = str_msg_sha384(c);
	if (s)
	{
		print_hash(s, flags, f, str);
		free(s);
	}
}
