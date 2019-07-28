/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 12:42:37 by amansour          #+#    #+#             */
/*   Updated: 2017/05/03 14:06:30 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define BUFF_SIZE 200

typedef struct		s_r
{
	int				fd;
	char			*s;
	struct s_r		*nxt;
}					t_r;

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memmove(void *dst, void const *s, size_t size);
void				*ft_memcpy(void *dst, void const *s, size_t size);
void				*ft_memccpy(void *dst, void const *s, int c, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *list);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
char				*ft_strnew(size_t n);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t len);
void				*ft_remalloc(void *ptr, size_t size);
void				ft_inverse(void *buff1, void *buff2, size_t size);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_atoi(char const *str);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
int					ft_strcmp(char const *str1, char const *str2);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strncmp(char const *str1, char const *str2, size_t n);
int					ft_isspace(char c);
int					ft_sqrt(int nb);
int					ft_convert(char *str, int base_size);
int					ft_abs(int nb);
size_t				ft_strlen(char const *str);
size_t				ft_strlcat(char *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strstr(char const *s, char const *s2);
char				*ft_strnstr(char const *s, char const *s2, size_t len);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t len);
char				*ft_strnew(size_t n);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s1, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1);
char				**ft_strsplit(char const *str, char c);
char				*ft_itoa(int n);
char				*ft_strdup(char const *s1);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s, char const *s2, size_t n);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *element));
int					get_next_line(const int fd, char **line);
#endif
