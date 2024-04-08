/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:15 by pgober            #+#    #+#             */
/*   Updated: 2024/04/08 15:25:36 by apashkov         ###   ########.fr       */
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
	if (get_env(envv, &mllcd->env_list) || adapt_shlvl(mllcd))
	{
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

int	main(int argc, char **argv, char **envv)
{
	t_alloc	mllcd;
	char	*input_str;

	init_minishell(&mllcd, envv);
	while (1)
	{
		if (isatty(fileno(stdin)))
			input_str = read_input_print_prompt(&mllcd.env_list);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			if (!line)
				exit_mllcfail(&mllcd);
			input_str = ft_strtrim(line, "\n");
			if (!input_str)
				exit_mllcfail(&mllcd);
		}
		if (!input_str)
			exit(mllcd.exit_status);
		sigint_helper(&mllcd);
		if (preparing_minishell(&mllcd, input_str) || \
			str_is_empty(mllcd.in_pars.cmd_table[0][0])
			|| g_sigint == SIGINT)
		{
			if (g_sigint == SIGINT)
			{
				finish_heredocs(&mllcd);
				sigint_helper(&mllcd);
			}
			free_before_exit(&mllcd, false);
			continue ;
		}
		if (mllcd.in_pars.pipenum > 0)
			run_pipex_multipipe(&mllcd, argc, argv);
		else
			run_simple_cmd(&mllcd);
		finish_heredocs(&mllcd);
		sigint_helper(&mllcd);
		free_before_exit(&mllcd, false);
	}
	return (free_before_exit(&mllcd, true), mllcd.exit_status);
}
