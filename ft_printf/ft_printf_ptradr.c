/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptradr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:25:29 by pgober            #+#    #+#             */
/*   Updated: 2023/09/14 13:25:46 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_put_basep(unsigned long nbrr, char *base, t_hexsize *bytes)
{
	unsigned long				basee;

	basee = 16;
	if (nbrr > basee - 1)
		ft_put_basep(nbrr / basee, base, bytes);
	if (nbrr < basee)
	{
		ft_putchar(base[nbrr]);
		bytes->i++;
		return ;
	}
	ft_put_basep(nbrr % basee, base, bytes);
}

int	ft_printf_ptradr(unsigned long ptr)
{
	t_hexsize	*bytes;
	int			j;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	bytes = (t_hexsize *)malloc(sizeof(t_hexsize));
	if (!bytes)
		return (0);
	bytes->i = 0;
	ft_putstr_fd("0x", 1);
	ft_put_basep(ptr, "0123456789abcdef", bytes);
	j = bytes->i;
	free(bytes);
	return (j + 2 * sizeof(char));
}
