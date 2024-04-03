/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pia___ft_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:46 by pgober            #+#    #+#             */
/*   Updated: 2024/03/29 12:09:51 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_checker(int res, int c, int sign)
{
	if (sign > 0 && res > (2147483647 - (c - '0')) / 10)
		return (0);
	if (sign < 0 && -(res) < (-2147483648 + (c - '0')) / 10)
		return (0);
	return (1);
}

int	is_num(char str)
{
	if ('0' <= str && str <= '9')
		return (1);
	return (0);
}

int	is_pm(char str)
{
	if (str == '+' || str == '-')
		return (1);
	return (0);
}

int	is_valid(char str)
{
	if (is_space(str) == 1 || is_num(str) == 1 || is_pm(str) == 1)
		return (1);
	return (0);
}

int	ft_atoi_minishell(const char *nptr, int *error)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while (*nptr != '\0' && is_valid(*nptr) == 1)
	{
		while (is_space(*nptr) == 1 && is_space(*(nptr + 1)) == 1)
			nptr++;
		if (is_pm(*nptr) == 1 && is_num(*(nptr + 1)) == 0)
			return (0);
		else if (*nptr == '-')
			sign = sign * (-1);
		while (is_num(*nptr) == 1)
		{
			if (!ft_atoi_checker(res, *nptr, sign))
				return (*error = 1, 0);
			res = res * 10 + *nptr - '0';
			if (is_num(*(nptr + 1)) == 0)
				return ((sign * res) % 256);
			nptr++;
		}
		nptr++;
	}
	return ((sign * res) % 256);
}