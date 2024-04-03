/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:43:18 by lbapart           #+#    #+#             */
/*   Updated: 2024/04/03 12:00:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//functions for testing
#include "libft.h"

static char	*ft_temp_realloc(char *old_buf, char c)
{
	int		len;
	char	*res;
	int		i;

	len = ft_strlen(old_buf);
	res = (char *)malloc(len + 2);
	if (!res)
		return (free(old_buf), NULL);
	i = 0;
	while (old_buf[i])
	{
		res[i] = old_buf[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	free(old_buf);
	return (res);
}

static char	*finish_get_next_line(char *buffer, int i, int read_bytes)
{
	buffer[i] = '\0';
	if (i == 0 || (!buffer[i - 1] && !read_bytes))
		return (free(buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	int		read_bytes;
	char	c;
	char	*buffer;

	buffer = (char *)malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, &c, 1);
		if (read_bytes == -1)
			return (free(buffer), NULL);
		else if (read_bytes == 0)
			break ;
		buffer = ft_temp_realloc(buffer, c);
		if (!buffer)
			return (NULL);
		if (c == '\n')
			break ;
	}
	return (finish_get_next_line(buffer, ft_strlen(buffer), read_bytes));
}
