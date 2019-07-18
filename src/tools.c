#include "../inc/ft_ssl.h"

int         ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return(i);
}

int	        ft_strcmp(char const *str1, char const *str2)
{
	unsigned char	*s2;
	unsigned char	*s1;
	size_t			i;

	i = 0;
	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

// long long convert_to_little(long long nb)
// {
//     unsigned char   tab[8];
//     long long       result;

//     tab[0] = nb & 255;
//     tab[1] = (nb >> 8) & 255;
//     tab[2] = (nb >> 16) & 255;
//     tab[3] = (nb >> 24) & 255;
//     tab[4] = (nb >> 32) & 255;
//     tab[5] = (nb >> 40) & 255;
//     tab[6] = (nb >> 48) & 255;
//     tab[7] = (nb >> 56) & 255;
//     result = (int)tab[0] << 56) + ((int)tab[1] << 48) + ((int)tab[2] << 40);
//     result += ((int)tab[3] << 32) + ((int)tab[4] << 24) + ((int)tab[5] << 16);
//     result += ((int)tab[6] << 8) +tab[7] 
//     return(result)
// }

void	    *ft_memccpy(void *dst, void const *src, int c, size_t size)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			i;

	i = 0;
	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	while (i < size)
	{
		dst1[i] = src1[i];
		if (src1[i] == (unsigned char)c)
			return ((void*)(dst1 + i + 1));
		i++;
	}
	return (NULL);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
	{
		*s2 = 0;
		s2++;
	}
}

void	    *ft_calloc(size_t nmemb, size_t size)
{
	void	*block;

	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	if ((block = malloc(nmemb * size)))
		ft_bzero(block, nmemb * size);
	return (block);
}