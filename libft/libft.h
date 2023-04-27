/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:24:34 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/21 17:12:02 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H 1

# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define DECIMAL	"0123456789"
# define U_HEXDECIMAL "0123456789ABCDEF"
# define L_HEXDECIMAL "0123456789abcdef"

char		*get_next_line(int fd);
int			ft_printf(const char *format, ...);

int			ft_strcmp(char *a, char *b);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *s, int c);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *str1, const void *str2, size_t n);
void		*ft_memset(void *str, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_atoi(const char *nptr);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_iswhitespace(char c);
int			ft_toupper(int ch);
int			ft_tolower(int ch);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoinf(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		**ft_protectmatrix(char **matrix, size_t j);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
// t_list		*ft_lstlast(t_list *lst);
// void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
