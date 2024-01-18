/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:08:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 14:06:57 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_program(t_alloc *mallcd)
{
	// close all fds;
	//free_everything(mallcd);
	exit(mallcd->exit_status);
}

static int	validate_input(char *input)
{
	int	i;

	i = 0;
	if (is_pm(input[0]) == 1 || is_num(input[0]) == 1)
		i++;
	else
		return (1);
	while (input[i])
	{
		if (is_num(input[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

int	exiting(t_alloc *mllcd, char *input, int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("exit: too many arguments", 2);
		mllcd->exit_status = 1;
	}
	if (validate_input(input) == 1)
	{
		ft_putstr_fd("exit: numeric argument required", 2);
		mllcd->exit_status = 2;
	}
	if (input)
		mllcd->exit_status = ft_atoi_minishell(input);
	exit_program(mllcd);
	return (0);
}