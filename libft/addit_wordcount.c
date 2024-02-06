/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_wordcount.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:58:54 by pgober            #+#    #+#             */
/*   Updated: 2024/02/06 19:17:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wordcount(char *str)
{
	int	i;
	int	count;

	count = 0;
	if (is_space(str[0]) == 0 && str[0] != '\0')
		count = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == 1 && is_space(str[i + 1]) == 0 && \
			str[i + 1] != '\0')
			count = count + 1;
		i++;
	}
	return (count);
}

// #include <stdio.h>
// int     main(int argc, char *argv[])
// {
//	 //char    *str = "Hello , world abcde";
//	 if (argc == 2)
//		 printf("%d", wordcount(argv[argc - 1]));
//	 else
//		 printf("0");
// }
