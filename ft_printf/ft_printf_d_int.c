/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:37:50 by pgober            #+#    #+#             */
/*   Updated: 2023/09/14 18:15:30 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	numsize(int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		while (nbr <= -10)
		{
			nbr /= 10;
			i++;
		}
		i++;
	}
	else
	{
		while (nbr >= 10)
		{
			nbr /= 10;
			i++;
		}
	}
	return (i);
}

int	ft_printf_d_int(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (numsize(nbr) * sizeof(char));
}
