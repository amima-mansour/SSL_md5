#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static const uint32_t k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void    init_md5(t_sha256_context *c)
{
	c->len = 0;
	c->state[0] = 0x6a09e667;
	c->state[1] = 0xbb67ae85;
	c->state[2] = 0x3c6ef372;
	c->state[3] = 0xa54ff53a;
	c->state[4] = 0x510e527f;
	c->state[5] = 0x9b05688c;
	c->state[6] = 0x1f83d9ab;
	c->state[7] = 0x5be0cd19;
}

static uint8_t    *prepare_msg(char *msg, t_sha256_context *c)
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

static void        subtreat_sha256(t_sha256_context *ctx, uint32_t *w)
{
	uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (w[j] << 24) | (w[j + 1] << 16) | (w[j + 2] << 8) | (w[j + 3]);
	for ( ; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e,f,g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
    return;
}
static void convert_to_hex(unsigned char nb)
{
    char s[3];

    s[0] = HEXBASE[nb / 16];
    s[1] = HEXBASE[nb % 16];
    s[2] = '\0';
    printf("%s", s);
    return;
}

void    sha256(char *msg, t_flags flags, char *filename)
{
    uint32_t        offset;
    uint32_t        i;
    t_sha256_context   c;
    uint32_t        *w;
    uint8_t         *new_msg;
    uint8_t        *p;
    uint8_t        hash[32];

    init_md5(&c);
    if (!(new_msg =  prepare_msg(msg, &c)))
        return;
    offset = 0;
    while(offset < c.len)
    {
        w = (uint32_t *)(new_msg + offset);
        subtreat_sha256(&c, w);
        offset += 64;
    }
    free(new_msg);
    for (i = 0; i < 4; ++i) {
		hash[i]      = (c.state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (c.state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (c.state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (c.state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (c.state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (c.state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (c.state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (c.state[7] >> (24 - i * 8)) & 0x000000ff;
	}
    hash[i + 28] = '\0';
    i = -1;
    while(++i < 32)
        convert_to_hex(hash[i]);
    i = -1;
    printf("\n");
    while(++i < 8)
    {
        p=(uint8_t *)&(c.state[i]);
        p[0] = c.state[i] >> 24 & 0x000000ff;
        p[1] = c.state[i] >> 16 & 0x000000ff;
        p[2] = c.state[i] >> 8 & 0x000000ff;
        p[3] = c.state[i] & 0x000000ff;
        printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    }
    //print_md5(c, flags, filename);
    printf("\nfilename = %s, flags.s = %d\n", filename, flags.s);
}
