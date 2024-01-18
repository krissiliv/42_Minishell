/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:47:28 by pgober            #+#    #+#             */
/*   Updated: 2023/09/12 15:06:15 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strst(char *str, char const *set)
{
	size_t	j;
	size_t	i;

	i = 0;
	if (!set || set[0] == '\0')
		return (i);
	while (str[i] != '\0')
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
			{
				while (str[i] == set[j])
					i++;
				j = 0;
			}
			else
				j++;
			if (j == ft_strlen(set))
				return (i);
		}
		i++;
	}
	return ((int)i);
}

static int	stren(char *str, char const *set)
{
	int	j;
	int	i;

	i = (int)ft_strlen(str) - 1;
	if (!set || set[0] == '\0')
		return (i);
	while (str[i] != '\0')
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
			{
				while (str[i] == set[j])
					i--;
				j = 0;
			}
			else
				j++;
			if (j == (int)ft_strlen(set))
				return (i + 1);
		}
		i--;
	}
	return (i + 1);
}

static int	stren_decision(char const *s1, char const *set)
{
	if (s1[0] == '\0')
		return (0);
	return (stren((char *)s1, set));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trstr;
	int		i;
	int		strstart;
	int		strend;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || set[0] == '\0')
		return (ft_strdup(s1));
	strstart = strst((char *)s1, set);
	strend = stren_decision(s1, set);
	if (strend <= strstart)
		return (ft_strdup(""));
	trstr = (char *)malloc((strend - strstart + 1) * sizeof(char));
	if (!trstr)
		return (NULL);
	i = strstart;
	while (i < strend)
	{
		trstr[i - strstart] = ((char *)s1)[i];
		i++;
	}
	trstr[i - strstart] = '\0';
	return (free((char *)s1), trstr);
}

/*int main(void)
{
	char str[] = "";
	char *res;
	char set[] = "ss";

	res = ft_strtrim(str, set);
	printf("%s", res);
	free(res);
}*/
