#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static	void				init_sha512(t_sha512_context *c)
{
	c->len = 0;
	c->state[0] = 0x6A09E667F3BCC908;
    c->state[1] = 0xBB67AE8584CAA73B;
    c->state[2] = 0x3C6EF372FE94F82B;
    c->state[3] = 0xA54FF53A5F1D36F1;
    c->state[4] = 0x510E527FADE682D1;
    c->state[5] = 0x9B05688C2B3E6C1F;
    c->state[6] = 0x1F83D9ABFB41BD6B;
    c->state[7] = 0x5BE0CD19137E2179;
}

void						sha512(char *msg, t_flags flags, char *filename)
{
	t_sha512_context		c;
	uint8_t				*new_msg;

	init_sha512(&c);
	if ((c.len = prepare_msg_sha512(msg, &new_msg)))
	{
        printf("msg = %s\nlen = %zu\n", msg, ft_strlen(msg));
		hash_sha_512(&c, &new_msg, ft_strlen(msg));
		free(new_msg);
		print_sha512(c, flags, filename, "SHA512");
	}
}