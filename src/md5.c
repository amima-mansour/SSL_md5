#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

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

static void    init_md5(t_md5_context *context)
{
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
    context->initial_state[0] = 0x67452301;
    context->initial_state[1] = 0xefcdab89;
    context->initial_state[2] = 0x98badcfe;
    context->initial_state[3] = 0x10325476;
}

static uint8_t    *prepare_msg(char *msg, t_md5_context *c)
{
    size_t      len;
    int         new_len;
    uint8_t     *new_msg;
    uint32_t    len_bits;

    len = ft_strlen(msg);
    len_bits = len * 8;
    new_len = len_bits + 1;
    while(new_len % 512 != 448)
        new_len++;
    new_len /= 8;
    c->len = new_len;
    if (!(new_msg = ft_calloc(new_len + 64, 1)))
        return(NULL);
    ft_memcpy(new_msg, msg, len);
    new_msg[len] = 128;
    ft_memcpy(new_msg + new_len, &len_bits, 4);
    return(new_msg);
}

static void        put_in_variable(t_md5_context *c, uint32_t f, uint32_t w, uint32_t offset)
{
    uint32_t temp;

    temp = c->state[3];
    c->state[3] = c->state[2];
    c->state[2] = c->state[1];
    c->state[1] += ROTLEFT((c->state[0] + f + g_t[offset] + w), g_s[offset]);
    c->state[0] = temp;
}

static void        subtreat_md5(t_md5_context *c, uint32_t *w)
{
    uint32_t i;
    uint32_t g;

    i = -1;
    while(++i < 16)
        put_in_variable(c, F(c->state[1], c->state[2], c->state[3]), w[i], i);
    while(i < 32)
    {
        g = (5 * i + 1) % 16;
        put_in_variable(c, G(c->state[1], c->state[2], c->state[3]), w[g], i++);
    }
    while(i < 48)
    {
        g = (3 * i + 5) % 16;
        put_in_variable(c, H(c->state[1], c->state[2], c->state[3]), w[g], i++);
    }
    while(i < 64)
    {
        g = (7 * i) % 16;
        put_in_variable(c, I(c->state[1], c->state[2], c->state[3]), w[g], i++);
    }
}

void                md5(char *msg, t_flags flags, char *filename)
{
    uint32_t        offset;
    t_md5_context   c;
    uint32_t        *w;
    uint8_t         *new_msg;

    init_md5(&c);
    if (!(new_msg =  prepare_msg(msg, &c)))
        return;
    offset = 0;
    while(offset < c.len)
    {   
        w = (uint32_t *)(new_msg + offset);
        c.state[0] = c.initial_state[0]; 
        c.state[1] = c.initial_state[1];
        c.state[2] = c.initial_state[2];
        c.state[3] = c.initial_state[3];
        subtreat_md5(&c, w);
        offset += 64;
        c.initial_state[0] += c.state[0];
        c.initial_state[1] += c.state[1];
        c.initial_state[2] += c.state[2];
        c.initial_state[3] += c.state[3];
    }
    free(new_msg);
    print_md5(c, flags, filename);
}