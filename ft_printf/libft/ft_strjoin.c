/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:33:02 by pgober            #+#    #+#             */
/*   Updated: 2023/09/12 15:59:17 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		k;
	int		s;

	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	k = 0;
	while (s1[k] != '\0')
	{
		new[k] = s1[k];
		k++;
	}
	s = 0;
	while (s2[s] != '\0')
		new[k++] = s2[s++];
	new[k] = '\0';
	return (new);
}

/*int	main(void)
{
	char	a[] = "Hello";
	char	b[] = "to all the";
	char	*h;
	
	//printf("%lu", (ft_strlen(a) + ft_strlen(b) + 1));
	h = ft_strjoin(a, b);	
	printf("%s", h);
	free(h);
}*/
