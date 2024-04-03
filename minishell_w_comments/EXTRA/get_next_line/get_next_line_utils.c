/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:17 by pgober            #+#    #+#             */
/*   Updated: 2023/10/09 18:21:30 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	cut(char *line, int buf_size)
{
	int	i;

	i = 0;
	while (i < buf_size)
	{
		if (line[i] == '\0' || line[i] == '\n')
			return (i);
		i++;
	}
	return (buf_size);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (slen(s) <= start)
		return (gnl_strdup(""));
	if (slen(s) - start < len)
		len = slen(s) - start;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && (s + start)[i])
	{
		new[i] = (s + start)[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	slen(char *s)
{
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strjoin(char *s1, char *s2, int i)
{
	char	*new;
	int		k;
	int		s;

	new = (char *)malloc((slen(s1) + i + 1) * sizeof(char));
	if (!new)
		return (free(s1), NULL);
	k = 0;
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
	s = 0;
	while (s2[s] && s < i)
		new[k++] = s2[s++];
	new[k] = '\0';
	free(s1);
	return (new);
}

char	*gnl_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((slen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
