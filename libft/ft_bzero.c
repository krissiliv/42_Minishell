/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:43:11 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:40:30 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

/*int	main(void)
{
	char	src[] = "!Hello worl0 d!!";
	size_t n = 6;

	ft_bzero(src, n);
	printf("My: %s\n", src);
	
	char    src2[] = "!Hello worl0 d!!";
	bzero(src2, n);
    printf("Orig: %s\n", src2);
}*/
