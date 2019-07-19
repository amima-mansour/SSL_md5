#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

static void print_msg(t_md5_context c)
{
    uint8_t *p;
    int     i;

    i = -1;
    while(++i < 4)
    {
        p = (uint8_t *)&(c.initial_state[i]);
        printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    }
    printf("\n");
    return;
}

static void convert_to_hex(unsigned char nb, char *s)
{
    s[0] = HEXBASE[nb / 16];
    s[1] = HEXBASE[nb % 16];
    return;
}

static  char *str_msg(t_md5_context c)
{
    uint8_t *p;
    int     i;
    char    *str;
    int     j;

    i = -1;
    j = 0;
    if (!(str = (char*)malloc(32)))
        return(NULL);
    while(++i < 4)
    {
        p = (uint8_t *)&(c.initial_state[i]);
        convert_to_hex((char)p[0], str + j);
        convert_to_hex((char)p[1], str + j + 2);
        convert_to_hex((char)p[2], str + j + 4);
        convert_to_hex((char)p[3], str + j + 6);
        j += 8;
    }
    return(str);
}

void    print_md5(t_md5_context c, t_flags flags, char *filename)
{

    printf("%s\n", str_msg(c));
    if (!filename || flags.q || (!flags.r && !flags.s))
    {
        /**
         * forget other flags and print normally the output
         */
        print_msg(c);
        return;
    }
    if (flags.r)
    {
        /**
         * check if it's a file, if it is print hash + name of file
         */
        print_msg(c);
        write(1, " ", 1);    
        ft_putendl(filename);
        return;
    }
    ft_putstr("MD5 (");
    ft_putstr(filename);
    ft_putstr(") = ");
    print_msg(c);
    /**
     * print normally the output
     */
    return;
}