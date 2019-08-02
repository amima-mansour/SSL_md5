/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:57:33 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:37:20 by amansour         ###   ########.fr       */
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

# define NB_FUNCTIONS	7
# define BUF			10000
# define WORD			4
# define WORD_64		8
# define WORD_64_BITS	64
# define WORD_BITS		32

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

# define SHR(x, n)		(x >> n)
# define ROTR(x, n)		(SHR(x, n) | (x << (64 - n)))
# define S0(x)			(ROTR(x, 1) ^ ROTR(x, 8) ^ SHR(x, 7))
# define S1(x)			(ROTR(x, 19) ^ ROTR(x, 61) ^ SHR(x, 6))
# define SIGMA0(x)		(ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
# define SIGMA1(x)		(ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
# define HEXBASE		"0123456789abcdef"

typedef uint8_t			t_u8;
typedef uint32_t		t_u32;
typedef uint64_t		t_u64;

typedef struct			s_md5_context
{
	uint32_t			state[4];
	uint64_t			len;
	uint32_t			var[4];
	uint32_t			i;
}						t_md5_context;

typedef struct			s_sha256_context
{
	uint32_t			state[8];
	uint64_t			len;
	uint32_t			var[8];
	uint32_t			t1;
	uint32_t			t2;
}						t_sha256_context;

typedef struct			s_sha512_context
{
	uint64_t			state[8];
	uint64_t			len;
	uint64_t			var[8];
	uint64_t			t1;
	uint64_t			t2;
}						t_sha512_context;

typedef struct			s_flags
{
	char				r;
	char				q;
	char				s;
	char				p;
	char				*str;
}						t_flags;

typedef struct			s_hash_functions
{
	char				*name;
}						t_hash_functions;

int						ft_strcmp(char const *str1, char const *str2);
void					*ft_memcpy_64(void *dest, const void *src, t_u64 len);
void					*ft_calloc(t_u64 nmemb, size_t size);
void					convert_to_hex(unsigned char nb, char *s);
char					*ft_strjoin_s(char const *s1, char const *s2, t_u64 l);
void                    ft_putstr_size(char *s, size_t size);

void					md5(char *msg, t_flags flags, char *f, t_u64 l);
void					print_md5(t_md5_context c, t_flags flags, char *f);

void					sha256(char *msg, t_flags flags, char *f, t_u64 l);
void					print_sha256(t_sha256_context c, t_flags fl, char *f,
						char *s);
void					sha224(char *msg, t_flags flags, char *f, t_u64 l);

void					sha512(char *msg, t_flags flags, char *f, t_u64 l);
void					print_sha512(t_sha512_context c, t_flags fl, char *f,
						char *s);
void					sha384(char *msg, t_flags flags, char *f, t_u64 l);
void					sha512256(char *msg, t_flags flags, char *f, t_u64 l);
void					sha512224(char *msg, t_flags flags, char *f, t_u64 l);

char					*str_msg_md5(t_md5_context c);
char					*str_msg_sha(t_sha256_context *c1, t_sha512_context *c2,
						int d, int w);
void					print_hash(char *s, t_flags flags, char *f, char *cmd);

t_u64					prepare_msg(char *msg, t_u8 **new_msg, t_u64 l);
t_u64					prepare_msg_sha512(char *msg, t_u8 **new_msg, t_u64 l);

void					init_flags(t_flags *flags);
int						flags_check(char **argv, int argc, t_flags *fl, int s);
void					cmd_check(char *s, void (**cmd)(char*, t_flags, char*,
						t_u64 l));
t_u64					file_check(char *arg, char *cmd, char **s);

t_u64					read_stdin(char **str);

void					usage(void);
void					file_error(char *cmd, char *str);
void					cmd_error(t_hash_functions hash[], char *cmd);
void					s_error(char *cmd);
void					flag_error(char c, char *cmd);

void					hash_sha_256(t_sha256_context *c, uint8_t **m,
						t_u64 l);
void					hash_sha_512(t_sha512_context *c, uint8_t **m,
						t_u64 l);
#endif
