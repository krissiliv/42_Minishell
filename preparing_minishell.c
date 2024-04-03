/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:32:57 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 13:25:32 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_parsed_input(t_alloc *mllcd)
{
	int	i;
	int	j;

	i = 0;
	while (i <= mllcd->in_pars.pipenum)
	{
		j = 0;
		while (j <= 4)
		{
			if (mllcd->in_pars.cmd_table[i][j])
			{
				if (expander(&(mllcd->in_pars.cmd_table[i][j]), mllcd))
					exit_mllcfail(mllcd);
			}
			j++;
		}
		i++;
	}
}

static int	preparing_minishell_helper(char *input_str, t_alloc *mllcd)
{
	mllcd->saved_stdin = dup(0);
	if (mllcd->saved_stdin == -1)
	{
		free(input_str);
		exit_mllcfail(mllcd);
	}
	if (!input_str)
		return (ft_putstr_fd("Error: Input is invalid.\n", 2), 1);
	if (pre_check_input(input_str) || ft_strlen(input_str) == 0 || \
		input_check_adapt(input_str))
		return (ft_putstr_fd("Error: Input is invalid.\n", 2), \
			free(input_str), 1);
	return (0);
}

int	preparing_minishell(t_alloc *mllcd, char *input_str)
{
	int	exit_status;
	int	temp;

	exit_status = 0;
	if (preparing_minishell_helper(input_str, mllcd))
		return (1);
	temp = put_space_before_special_operator(&input_str);
	if (temp == -1)
	{
		free(input_str);
		exit_mllcfail(mllcd);
	}
	temp = cmdline_input_parser(&mllcd->in_pars, input_str);
	free(input_str);
	if (temp == 1)
		exit_mllcfail(mllcd);
	else
		exit_status = temp;
	if (exit_status == 2)
		mllcd->exit_status = 2;
	if (exit_status)
		return (1);
	expand_parsed_input(mllcd);
	return (0);
}
