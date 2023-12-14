/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexlu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:44:15 by pgober            #+#    #+#             */
/*   Updated: 2023/09/19 19:35:40 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_hex_lu(unsigned int ptr, char lu)
{
	t_hexsize	*bytes;
	int			j;

	bytes = (t_hexsize *)malloc(sizeof(t_hexsize));
	if (!bytes)
		return (0);
	bytes->i = 0;
	if (lu == 'x')
		ft_putnbr_base(ptr, "0123456789abcdef", bytes);
	if (lu == 'X')
		ft_putnbr_base(ptr, "0123456789ABCDEF", bytes);
	j = bytes->i;
	free(bytes);
	return (j);
}
