/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsdec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:25:03 by pgober            #+#    #+#             */
/*   Updated: 2023/09/15 16:55:22 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_unsdec(unsigned int n)
{
	if (n > 9)
	{
		ft_printf_unsdec(n / 10);
		ft_printf_unsdec(n % 10);
	}
	else
		ft_putchar_fd(n + 48, 1);
}
