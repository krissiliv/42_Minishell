/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:45:51 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:54:23 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*int	main(void)
{
	const char	src[] = "!Hello worl0 d!!";
	char	dest[5];
	size_t	ans;
	size_t len = 6;
	
	ans = ft_strlcpy(dest, src, len);
	printf("src %s\n", src);
	printf("dest %s\n", dest);
	printf("ft_strlcpy output: %zu \n", ans);


    char    dest2[5];
    size_t ans2;

    ans2 = strlcpy(dest2, src, len);
    //printf("src %s\n", src);
    printf("dest %s\n", dest2);
    printf("strlcpy output: %zu \n", ans2);
}*/
