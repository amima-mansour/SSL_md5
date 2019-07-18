#include "../inc/ft_ssl.h"

static const uint32_t g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t g_t[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void    init_md5(t_md5_context *context, uint8_t *str)
{
    context->state[0] = 0x67452301; 
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
    context->len = ft_strlen(str);
}

char    *prepare_msg(unit8_t *msg)
{
    size_t      len;
    size_t      new_len;
    char        *new_msg;
    size_t      len_bits;     

    len = ft_strlen(msg);
    len_bits = len * 8;
    new_len =  len_bits + 1;
    if (len % 512 < 448)
        new_len += 448 - len % 512;
    else
        new_len += 448 + (512 -  len % 512);   
    if (!(new_msg = (char*)ft_calloc(new_len + 64, 1)))
        return(NULL);
    ft_memcpy(new_msg, msg, len);
    new_msg[len] = 128;
    ft_memcpy(str + new_len, &len_bits, 4);
    return(new_msg);
}

void        put_in_variable(t_md5_context *c, unit32_t a, unit32_t offset)
{
    uint32_t temp;

    temp = c->state[3];
    c->state[3] = c->state[2];
    c->state[2] = c->state[1];
    c->state[1] += LEFTROTATE(( c->state[0]+ a + g_t[offset]), g_s[offset]);
    c->state[0] = temp;

}

void        subtreat_md5(t_md5_context *c, uint32_t *w, uint32_t offset)
{
    uint32_t i;
    uint32_t g;
    
    i = -1;
    while(++i < 16)
        put_in_variable(c, F(b, c, d) + w[i], offset);
    while(++i < 32)
    {
        g = (5 × i + 1) % 16;
        put_in_variable(c, G(b, c, d) + w[g], offset);
    }
    while(++i < 48)
    {
        g = (3 × i + 5) % 16;
        put_in_variable(c, H(b, c, d) + w[g], offset);
    }
    while(++i < 64)
    {
        g = (7 × i) % 16;
        put_in_variable(c, I(b, c, d)+ w[g], offset);
    }
}

void    print_md5(t_md5_context *c)
{
    uint8_t *p;
    int     i;

    i = -1;
    while(++i < 4)
    {
        p = (uint8_t *)&(c->initial_state[i]);
        printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], c->initial_state[i]);
    }
}
void    md5(uint8_t *msg)
{
    int             offset;
    int             temp;
    t_md5_context   *c;

    if (!(msg =  prepare_msg(msg)))
        return;
    init_md5(c, msg);
    offset = 0;
    while(offset < c->len)
    {   
        w = (uint32_t *) (msg + offset);
        c->state[0] = c->initial_state[0]; 
        c->state[1] = c->initial_state[1];
        c->state[2] = c->initial_state[2];
        c->state[3] = c->initial_state[3];
        subtreat_md5(c, w)
        offset += 64
        c->initial_state[0] += c->state[0];
        c->initial_state[1] += c->state[1];
        c->initial_state[2] += c->state[2];
        c->initial_state[3] += c->state[3];
    }
    // A coder le print final
    print_md5(c);
}