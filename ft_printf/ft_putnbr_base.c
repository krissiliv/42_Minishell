/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:24:27 by pgober            #+#    #+#             */
/*   Updated: 2023/09/14 13:26:19 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static long long int	base_type(char *base)
{
	int	basee;

	basee = 0;
	while (*base != '\0')
	{
		basee++;
		base++;
	}
	return (basee);
}

static long long int	check_base(char *base)
{
	int	i;
	int	j;

	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(long long int nbr, char *base, t_hexsize *bytes)
{
	int				basee;
	long long int	nbrr;

	nbrr = (long long)nbr;
	basee = base_type(base);
	if (check_base(base) == 0)
		return ;
	if (nbrr < 0)
	{
		ft_putchar('-');
		bytes->i++;
		nbrr = -nbrr;
	}
	if (nbrr > basee - 1)
		ft_putnbr_base(nbrr / basee, base, bytes);
	if (nbrr < basee)
	{
		ft_putchar(base[nbrr]);
		bytes->i++;
		return ;
	}
	ft_putnbr_base(nbrr % basee, base, bytes);
}

/*int	main(void)
{
	ft_putnbr_base(103934852195, "0123456789ABCDEF");
}*/
