#include "../inc/ft_ssl.h"
#include "../libft/libft.h"

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
    str[j] = '\0';
    return(str);
}

void    print_md5(t_md5_context c, t_flags flags, char *filename)
{
    char    *s;

    s = str_msg(c);

    if ((filename || (flags.s && filename)) && !flags.r && !flags.q)
    {
        ft_putstr("MD5 (");
        if (flags.s && flags.str)
            ft_putstr("\"");
        ft_putstr(filename);
        if (flags.s && flags.str)
            ft_putstr("\"");
        ft_putstr(") = ");
    }
    ft_putstr(s);
    if (filename && !flags.q && flags.r)
    {
        ft_putstr(" ");    
        ft_putstr(filename);
    }
    ft_putstr("\n");
    free(s);
    return;
}