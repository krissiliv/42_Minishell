/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:41:32 by pgober            #+#    #+#             */
/*   Updated: 2023/09/07 10:46:36 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void f(unsigned int i, char *c)
{
	c[0] += i;
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		f(i, &(s[i]));
		i++;
	}
}

/*int main(void)
{
	char s[] = "AbCdEfGhIjK";

	ft_striteri(s, (*f));
	printf("%s", s);
}*/
