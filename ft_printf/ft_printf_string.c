/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:39:12 by pgober            #+#    #+#             */
/*   Updated: 2023/09/13 17:39:19 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_string(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	i = 0;
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
		i++;
	}
	return (i * sizeof(char));
}
