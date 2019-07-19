#include "../inc/ft_ssl.h"

void    sha256(char *msg, t_flags flags, char *filename)
{
    printf("P => %d\nR => %d\nQ => %d\n S => %d\n", flags.p, flags.r, flags.q, flags.s);
    printf("filename = %s msg = %s", filename, msg);
    return;
}