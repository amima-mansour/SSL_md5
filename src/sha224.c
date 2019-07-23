#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static void sha224_init( t_sha224_context *context)
{
    context->state[0] = 0xC1059ED8;
    context->state[1] = 0x367CD507;
    context->state[2] = 0x3070DD17;
    context->state[3] = 0xF70E5939;
    context->state[4] = 0xFFC00B31;
    context->state[5] = 0x68581511;
    context->state[6] = 0x64F98FA7;
    context->state[7] = 0xBEFA4FA4;
}

