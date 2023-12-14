/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:42:07 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:44:34 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (8);
	else if ('0' <= c && c <= '9')
		return (8);
	return (0);
}

/*int main(void)
{
	int i = 0;

	while (i < 127)
	{
		printf("%d -- ", ft_isalnum(i));
		printf("%d \n", isalnum(i));
		i++;
	}
	return (0);
}*/
