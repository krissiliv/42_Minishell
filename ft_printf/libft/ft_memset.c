/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:03:07 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:50:27 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}

/*int main(void)
{
	char str[] = "Welcome to our world";
	size_t n = 10;
	int c = '.';
	
	printf("BEFORE: %s \n", str);
	ft_memset(str, c, n);
	printf("AFTER: %s \n", str);
	
	printf("\n");

	char str2[] = "Welcome to our world";

    printf("BEFORE: %s \n", str2);
    memset(str2, c, n);
    printf("AFTER: %s", str2);

	return (0);
}*/
