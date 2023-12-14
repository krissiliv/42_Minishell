/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_search_and_replace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:20:32 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 13:25:30 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_cmp(char *str, char *str2)
{
	while (*str2)
	{
		if (*str++ != *str2++)
			return (0);
	}
	return (1);
}

static int	str_included(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str_cmp(str + i, str2) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	search_and_replace(char *str, char *a, char *o)
{
	int	i;
	int	j;

	i = 0;
	if (a[1] && str_included(str, a) == 0)
		return ;
	while (str[i])
	{
		if (str_cmp(str + i, a))
		{
			j = 0;
			while (a[j])
			{
				write(1, &o[j++], 1);
				i++;
			}
		}
		write(1, &str[i], 1);
		i++;
	}
}

// int main(int argc, char **argv)
// {
//     if (argc == 4)
//         search_and_replace(argv[argc-3], argv[argc-2], argv[argc-1]);
//     write(1, "\n", 1);
//     //printf("%d\n", str_cmp("He", "Helloh"));
// }