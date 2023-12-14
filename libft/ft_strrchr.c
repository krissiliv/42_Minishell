/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:16:51 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:39:51 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if ((char)c == '\0')
		return (&((char *)s)[ft_strlen(s)]);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (((char *)s)[i] == (char)c)
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}

/*int	main(void)
{
	char	str[] = "bonjour";
	char	to_find = '\0';

	printf("My: %s \n", ft_strrchr(str, to_find));

	printf("Orig: %s", strrchr(str, to_find));
}*/