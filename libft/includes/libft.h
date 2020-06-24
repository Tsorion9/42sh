/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:39:14 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/21 22:06:02 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "ft_ptree.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					get_next_line_wrapper(const int fd, char **line);
size_t				ft_strlen(const char *s);
int					ft_tolower(int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s1);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_toupper(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_atoi(const char *str);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strnstr(const char *hay, const char *need, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
int					ft_putendl_fd(const char *s, int fd);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				**ft_strsplit(const char *s, int c);
void				ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_freestrsplit(char **str);

void				ft_strrev(char *s);
char				*ft_itoa_base(long long value, char *base, int sgn);
char				*ftoa(long double x, int precision);
int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);

int					ft_lstadd_data(t_list **lst, void *content,\
		size_t content_size);
t_list				*ft_lstnew_inplace(void const *content,\
		size_t content_size);
char				*ft_straddchar(char *s, char c);

int					ft_lstlen(t_list *l);
char				*ft_path_append(char *path, char *name);
/*
** ft_ptree.g
*/

# define N_CHILDREN 256

/*
** Prefix tree data structure
** key - value pairs, keys are strings, values - *void
** value must be freeable (TODO: arbitrary)
**
** NULL value means lack of value
** If no children and no value, we can delete a node and check parent
** (not really needed)
*/

typedef struct		s_ptree
{
	struct s_ptree	*child[N_CHILDREN];
	void			*value;
}					t_ptree;

t_ptree				*new_tree(void);

/*
** Return value of key if it exists
*/

void				*search_key(t_ptree *tree, char *key);

/*
** Return nonzero on success
** Remove old entry properly if needed
** If NULL is provided instead of tree, create a new tree
*/

int					insert_value(t_ptree *tree, char *key, void *value);
void				del_key(t_ptree *tree, char *key);
void				del_tree(t_ptree **tree);

/*
** Copy tree with all contents.
** Modification of copy never affects original tree
*/

t_ptree				*copy_ptree(t_ptree *tree);

typedef	struct		s_key_value
{
	char			*key;
	void			*value;
}					t_key_value;

/*
** Convert ptree to list of  key-value pairs
**
** If no values are present on the tree and some keys (yes, this is possible),
** return single node of list with empty content.
**
** Return 0 in case of malloc errors.
*/

t_list				*ptree_to_kvpairs(t_ptree *tree);

void				*xmalloc(size_t n);

#endif
