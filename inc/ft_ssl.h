#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * Transform functions
 */

#define F(x, y, z)          (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z)          (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z)          ((x) ^ (y) ^ (z))
#define I(x, y, z)          ((y) ^ ((x) | (~z)))
#define ROTLEFT(x, c)       (((x) << (c)) | ((x) >> (32 - (c))))
#define ROTRIGHT(a,b)       (((a) >> (b)) | ((a) << (32 - (b))))

#define CH(x,y,z)           (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)          (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x)              (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x)              (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x)             (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x)             (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

#define HEXBASE             "0123456789abcdef"
/**
 * structure
 */
typedef struct      s_md5_context
{
    uint32_t        state[4];          /*!< intermediate digest state  */
    unsigned char   buffer[64];   /*!< data block being processed */
    uint32_t        len;
    uint32_t        initial_state[4];
}                   t_md5_context;

typedef struct      s_sha256_context
{
    uint32_t        state[8];          /*!< intermediate digest state  */
    unsigned char   buffer[64];   /*!< data block being processed */
    uint32_t        len;
    uint32_t        initial_state[8];
}                   t_sha256_context;

typedef struct      s_flags
{
    char            r;
    char            q;
    char            s;
    char            p;
    char            *str;
}                   t_flags;

/**
 * tools
 */
int	        ft_strcmp(char const *str1, char const *str2);
void		*ft_memcpy (void *dest, const void *src, size_t len);
void	    *ft_calloc(size_t nmemb, size_t size);

/**
 * md5
 */
void                md5(char *msg, t_flags flags, char *filename);
void                print_md5(t_md5_context c, t_flags flags, char *filename);

/**
 * sha256
 */
void                sha256(char *msg, t_flags flags, char *filename);

#endif
