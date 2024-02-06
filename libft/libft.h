/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:36:38 by pgober            #+#    #+#             */
/*   Updated: 2024/02/06 19:18:13 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int i);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		is_space(char str);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

typedef struct t_hstruct
{
	int		wct;
	int		j;
	int		k;
}	t_mystruct;

char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// additional

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}	t_list;

// from Piscine
int		ft_strcmp(char *s1, char *s2);
void	ft_print_program_name(int argc, char *argv[]);

// these were never checked
void	free_and_null(void *alloc);
int		abs(int i);
void	search_and_replace(char *str, char *a, char *o);
t_list	*create_linked_list(int listlen, int *elements);
void	prntlist_int(t_list *head);
void	free_listnode(t_list *pos);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
int		wordcount(char *str);

typedef struct s_charlist
{
	struct s_charlist	*next;
	char				*data;
}	t_charlist;

void	prntlist_char(t_charlist *head);
void	free_strstr(char **str);
void	free_intarr(int **arr, int number);

#endif
