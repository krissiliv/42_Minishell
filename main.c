/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:15 by pgober            #+#    #+#             */
/*   Updated: 2024/04/13 12:56:50 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_minishell(t_alloc *mllcd, char **envv)
{
	mllcd->in_pars.m_argc = 0;
	mllcd->in_pars.m_argv = NULL;
	mllcd->in_pars.cmd_table = NULL;
	mllcd->saved_stdin = -1;
	mllcd->env_list = NULL;
	mllcd->exit_status = 0;
	if (!envv || !envv[0])
		return ;
	else if (get_env(envv, &mllcd->env_list) || adapt_shlvl(mllcd))
	{
		if (mllcd->env_list)
			ft_lstclear(&mllcd->env_list);
		exit(1);
	}
}

void	sigint_helper(t_alloc *mllcd)
{
	if (g_sigint == SIGINT)
	{
		mllcd->exit_status = 130;
		g_sigint = 0;
	}
}

static void	main_helper(t_alloc *mllcd, int argc, char **argv)
{
	if (mllcd->in_pars.pipenum > 0)
		run_pipex_multipipe(mllcd, argc, argv);
	else
		run_simple_cmd(mllcd);
	finish_heredocs(mllcd);
	sigint_helper(mllcd);
	free_before_exit(mllcd, false);
}

int	main(int argc, char **argv, char **envv)
{
	t_alloc	mllcd;
	char	*input_str;

	init_minishell(&mllcd, envv);
	while (1)
	{
		input_str = read_input_print_prompt(&mllcd.env_list);
		if (!input_str)
			return (printf("exit\n"), exit(mllcd.exit_status), 1);
		sigint_helper(&mllcd);
		if (preparing_minishell(&mllcd, input_str) || \
			g_sigint == SIGINT)
		{
			if (g_sigint == SIGINT)
			{
				finish_heredocs(&mllcd);
				sigint_helper(&mllcd);
			}
			free_before_exit(&mllcd, false);
			continue ;
		}
		main_helper(&mllcd, argc, argv);
	}
	return (free_before_exit(&mllcd, true), mllcd.exit_status);
}
