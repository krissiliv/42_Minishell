/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:06:18 by pgober            #+#    #+#             */
/*   Updated: 2023/09/11 16:54:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char f(unsigned int i, char c)
{
	return (c + i - i);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new;

	new = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*int main(void)
{
	char s[] = "LoReM iPsUm";

	printf("%s", ft_strmapi(s, (*f)));
}*/
