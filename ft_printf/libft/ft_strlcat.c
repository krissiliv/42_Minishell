/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:57:42 by pgober            #+#    #+#             */
/*   Updated: 2023/09/08 17:14:08 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (ft_strlen(src) + size);
	size = size - len_dst;
	i = 0;
	while (1 < size && src[i] != '\0')
	{
		dst[len_dst + i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dst[len_dst + i] = '\0';
	return (ft_strlen(src) + len_dst);
}

/*int	main(void)
{
	char	src[] = " world";
	char	dest[] = "Hello";
	size_t	n = 20;
	
	printf("Me: %zu \n", ft_strlcat(dest, src, n));
	char	dest2[] = "Hello";
	printf("Or: %zu \n", strlcat(dest2, src, n));
	
	return (0);
}*/
