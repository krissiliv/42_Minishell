/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:08:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/02/05 09:20:52 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_program(t_alloc *mllcd)
{
	// printf("exit\n");
	// close all fds;
	free_before_exit(mllcd);
	exit(mllcd->exit_status);
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

int	exiting(t_alloc *mllcd, char **cmd, int argc)
{
	if (cmd[1])
	{
		if (validate_input(cmd[1]) == 1)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			mllcd->exit_status = 2;
			return (2);
		}
		else if (argc > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			mllcd->exit_status = 1;
			return (1);
		}
		else
			mllcd->exit_status = ft_atoi_minishell(cmd[1]);
	}
	free_strstr(cmd);
	exit_program(mllcd);
	return (0);
}