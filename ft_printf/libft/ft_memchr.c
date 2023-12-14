/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:57:06 by pgober            #+#    #+#             */
/*   Updated: 2023/09/11 17:45:39 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (NULL);
}

/*int main(void)
{
	char str[] = "string";
	size_t n = 10;
	int c = '\0';

	printf("AFTER: %s \n", (char*)ft_memchr(str, c, n));

	printf("\n");

	printf("AFTER: %s \n", (char*)memchr(str, c, n));

	return (0);
}*/
