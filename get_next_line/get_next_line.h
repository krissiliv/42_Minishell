/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:36:29 by pgober            #+#    #+#             */
/*   Updated: 2023/10/09 18:21:23 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

size_t	cut(char *line, int buf_size);
char	*gnl_substr(char *s, unsigned int start, size_t len);
size_t	slen(char *s);
char	*gnl_strjoin(char *s1, char *s2, int i);
char	*gnl_strdup(char *s);

char	*use_read(char **line, char **buffer, int len);
char	*fill_line(char **line, int fd, char **exc_chs, size_t bufsz);
char	*fill_line_excess(char **excess_chars, char *exc_chs, int end);
char	*get_next_line(int fd);

#endif
