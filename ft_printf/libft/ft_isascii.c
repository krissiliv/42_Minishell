/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:48:56 by pgober            #+#    #+#             */
/*   Updated: 2023/09/06 19:46:06 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (1);
	return (0);
}

/*int main(void)
{
	int i = 0;
	
	while (i < 130)
	{
		printf("%d -- ", ft_isascii(i));
		printf("%d \n", isascii(i));
		i++;
	}
	return (0);
}*/
