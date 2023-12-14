/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:06:03 by pgober            #+#    #+#             */
/*   Updated: 2023/09/12 15:35:32 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*srcptr;
	char		*destptr;

	if (dest == 0 && src == 0)
		return (NULL);
	srcptr = (char *)src;
	destptr = (char *)dest;
	if (destptr < srcptr)
		ft_memcpy(dest, src, n);
	else
	{
		while (n-- > 0)
			((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}

/*int	main(void)
{
	char	src[20] = "con\0sec\0\0te\0tur";
	char	*dest;
	int		i = 0;
	int		j = 0;
	
	//printf("src: %s\n", src);
	dest = ft_memmove(src + j, src + i, 10);
	printf("dest: %s\n", dest);


	char    src2[20] = "con\0sec\0\0te\0tur";
    char    *dest2;

	//printf("src: %s\n", src2);
    dest2 = memmove(src2 + j, src2 + i, 10);
    printf("dest: %s\n", dest2);
}*/
