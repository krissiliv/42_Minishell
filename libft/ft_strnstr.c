/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:37:20 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:43:28 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i - j);
			j++;
		}
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	str[] = "Hello world";
	char	to_find[] = "lo";
	size_t	len = 30;

	printf("%s \n", ft_strnstr(str, to_find, len));

	printf("%s", strnstr(str, to_find, len));
}*/
