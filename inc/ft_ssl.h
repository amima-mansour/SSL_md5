/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:57:33 by amansour          #+#    #+#             */
/*   Updated: 2019/07/22 19:15:06 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define NB_FUNCTIONS	3
# define BUF			10000

# define F(x, y, z)		(((x) & (y)) | ((~x) & (z)))
# define G(x, y, z)		(((x) & (z)) | ((y) & (~z)))
# define H(x, y, z)		((x) ^ (y) ^ (z))
# define I(x, y, z)		((y) ^ ((x) | (~z)))
# define ROTLEFT(x, c)	(((x) << (c)) | ((x) >> (32 - (c))))
# define ROTRIGHT(a,b)	(((a) >> (b)) | ((a) << (32 - (b))))

# define CH(x,y,z)		(((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z)		(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x)			(ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
# define EP1(x)			(ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
# define SIG0(x)		(ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
# define SIG1(x)		(ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

#define SHR(x, n)		(x >> n)
#define ROTR(x, n)		(SHR(x, n) | (x << (64 - n)))
#define S0(x) 			(ROTR(x, 1) ^ ROTR(x, 8) ^ SHR(x, 7))
#define S1(x) 			(ROTR(x, 19) ^ ROTR(x, 61) ^ SHR(x, 6))
#define SIGMA0(x) 		(ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
#define SIGMA1(x) 		(ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
#define BYTESWAP(x) 	((ROTRIGHT((x), 8) & 0xff00ff00L) | \
						(ROTLEFT((x), 8) & 0x00ff00ffL))
# define HEXBASE		"0123456789abcdef"

typedef t_sha256_context t_sha224_context;

typedef struct		s_md5_context
{
	uint32_t		state[4];
	uint32_t		len;
	uint32_t		var[4];
	uint32_t		i;
}					t_md5_context;

typedef struct		s_sha256_context
{
	uint32_t		state[8];
	uint32_t		len;
	uint32_t		var[8];
	uint32_t		t1;
	uint32_t		t2;
}					t_sha256_context;

typedef struct		s_sha512_context
{
	uint64_t		state[8];
	uint64_t		len;
	uint64_t		var[8];
	uint64_t		t1;
	uint64_t		t2;
}					t_sha512_context;

typedef struct		s_flags
{
	char			r;
	char			q;
	char			s;
	char			p;
	char			*str;
}					t_flags;

typedef struct		s_hash_functions
{
	char			*name;
	void			(*f)(char*, t_flags, char*);
}					t_hash_functions;

int					ft_strcmp(char const *str1, char const *str2);
void				*ft_memcpy (void *dest, const void *src, size_t len);
void				*ft_calloc(size_t nmemb, size_t size);
void				convert_to_hex(unsigned char nb, char *s);

void				md5(char *msg, t_flags flags, char *filename);
void				print_md5(t_md5_context c, t_flags flags, char *filename);

void				sha256(char *msg, t_flags flags, char *filename);
void				print_sha256(t_sha256_context c, t_flags fl, char *f);

void				sha512(char *msg, t_flags flags, char *filename);
void				print_sha512(t_sha512_context c, t_flags flags, char *f);

uint32_t			prepare_msg(char *msg, uint8_t **new_msg);
uint64_t			prepare_msg_sha512(char *msg, uint8_t **new_msg);
void				init_flags(t_flags *flags);
int					flags_check(char **argv, int argc, t_flags *flags, int s);
void				(*cmd_check(char *cmd))(char*, t_flags, char*);
char				*file_check(char *arg, char *cmd);

void				read_stdin(char **str);
void				usage(void);
void				file_error(char *cmd, char *str);
void				cmd_error(t_hash_functions hash[], char *cmd);
void				s_error(char *cmd);
void				flag_error(char c, char *cmd);
#endif
