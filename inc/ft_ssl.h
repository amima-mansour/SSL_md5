#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
 * Transform functions
 */

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

/**
 * structure
 */
typedef struct      s_md5_context
{
    uint32_t        total[2];          /*!< number of bytes processed  */
    uint32_t        state[4];          /*!< intermediate digest state  */
    unsigned char   buffer[64];   /*!< data block being processed */
    uint32_t        len;
    unit32_t        initial_state[4;]
}
                    t_md5_context;

/**
 * tools
 */
int         ft_strlen(char *s)
void        ft_strcpy(char **s, char *s1)
long long   convert_to_little(long long nb)
void	    *ft_calloc(size_t nmemb, size_t size);
#endif
