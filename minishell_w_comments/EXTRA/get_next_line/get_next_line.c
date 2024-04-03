/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:07 by pgober            #+#    #+#             */
/*   Updated: 2023/10/09 18:21:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*use_read(char **line, char **buffer, int len)
{
	(*buffer)[len] = '\0';
	if (!(*line))
		return (gnl_substr(*buffer, 0, cut(*buffer, slen(*buffer)) + 1));
	else
	{
		if ((*buffer)[cut(*buffer, len)] == '\0')
			return (gnl_strjoin(*line, *buffer, cut(*buffer, len)));
		return (gnl_strjoin(*line, *buffer, cut(*buffer, len) + 1));
	}
}

char	*fill_line(char **line, int fd, char **exc_chs, size_t bufsz)
{
	char		*buf;
	int			len;

	buf = (char *)malloc((bufsz + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	len = read(fd, buf, bufsz);
	if (*line && (len == 0 && cut(*line, slen(*line)) == slen(*line)))
		return (free(buf), *line);
	if (len <= 0)
		return (free(buf), free(*line), NULL);
	while (len > 0)
	{
		*line = use_read(line, &buf, len);
		if (!(*line))
			return (free(buf), NULL);
		if (cut(buf, bufsz) < bufsz)
			break ;
		len = read(fd, buf, bufsz);
	}
	if (buf[cut(buf, bufsz)] && buf[cut(buf, bufsz) + 1])
		*exc_chs = gnl_strdup(buf + cut(buf, len) + 1);
	if (slen(*line) == 0 || !(*line))
		return (free(buf), NULL);
	return (free(buf), *line);
}

char	*fill_line_excess(char **excess_chars, char *exc_chs, int end)
{
	char		*tmp;

	free(*excess_chars);
	if (!exc_chs)
		return (NULL);
	tmp = NULL;
	if (slen(exc_chs + cut(exc_chs, slen(exc_chs))) > 1)
	{
		tmp = gnl_strdup(exc_chs + cut(exc_chs, slen(exc_chs)) + end);
		if (!tmp)
			return (NULL);
		free(exc_chs);
		exc_chs = gnl_strdup(tmp);
		free(tmp);
		if (!exc_chs)
			return (NULL);
	}
	else
	{
		free(exc_chs);
		exc_chs = NULL;
	}
	return (exc_chs);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*exc_chs;
	char		*temp;
	int			nl;

	line = NULL;
	temp = NULL;
	nl = 1;
	if (exc_chs)
	{
		if (exc_chs[cut(exc_chs, slen(exc_chs))] == '\0')
			nl = 0;
		line = gnl_substr(exc_chs, 0, cut(exc_chs, slen(exc_chs)) + nl);
		if (!line)
			return (NULL);
		temp = gnl_strdup(exc_chs);
		exc_chs = fill_line_excess(&exc_chs, temp, nl);
		if (cut(line, slen(line)) == slen(line) - 1 && slen(line) != 0)
			return (line);
	}
	return (fill_line(&line, fd, &exc_chs, BUFFER_SIZE));
}

/*#include <stdio.h>
int	main(void)
{
	char	path[] = "FirstTry.txt";
	int		fd;
	int		i;
	char	*text;

	i = 0;
	fd = open(path, O_RDONLY);
	while (i < 2)
	{
		text = get_next_line(fd);
		printf("%d:%s", i++, text);
		free(text);
	}
	close(fd);
	return (0);
}*/
/*
A file descriptor is an integer number in its most basic form.
Each file that is opened receives its number. We call it a file 
descriptor.
In a normal program the file descriptor 
0 is stdin, 1 is stdout and 2 is stderr. 
stdin is where you should read your input, 
1 is where you should write your output and 
2 is where you should write your error messages.
A file descriptor is what is returned by the open() function 
after it has been used to open a file. Once that is done, 
we may utilize this file descriptor to carry out more actions on that file.

For instance, if we wish to read data from the opened file, 
we provide the file descriptor as input to the function that reads data.
*/
