/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:57:39 by pgober            #+#    #+#             */
/*   Updated: 2024/02/05 16:03:44 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_input_parsing *in_pars) //parsing
{
	int	i;
	int	j;

	i = 0;
	if (in_pars->cmd_table)
	{
		while (i <= in_pars->pipenum)
		{
			if (in_pars->cmd_table[i])
			{
				j = 0;
				// printf("freeing cmd_table[%d]: [%s, %s, %s, %s, %s] \n", i, in_pars->cmd_table[i][0], in_pars->cmd_table[i][1], in_pars->cmd_table[i][2], in_pars->cmd_table[i][3], in_pars->cmd_table[i][4]);
				while (j <= 4)
				{	
					if (in_pars->cmd_table[i][j])
						free_and_null((void *)in_pars->cmd_table[i][j]);
					j++;
				}
				free_and_null((void *)in_pars->cmd_table[i]);
			}
			i++;
		}
		free_and_null((void *)in_pars->cmd_table);
		in_pars->cmd_table = NULL;
	}
}

void	pipex_free_all(t_pipex_m *pipex_m, int **pipe_ends) //pipex
{
	int	i;
	
	if (!pipex_m)
		return ;
	i = 0;
	if (pipe_ends)
	{
		while (i < pipex_m->cmdnum)
		{
			close (pipe_ends[i][0]);
			close (pipe_ends[i][1]);
			i++;
		}
		i = 0;
		free_intarr(pipe_ends, pipex_m->pipenum);
		pipe_ends = NULL;
	}
	if (pipex_m->cmd)
	{
		free_strstr(pipex_m->cmd);
		pipex_m->cmd = NULL;
	}
	if (pipex_m->poss_paths)
	{
		free_strstr(pipex_m->poss_paths);
		pipex_m->poss_paths = NULL;
	}
	if (pipex_m->cmdpath)
		free_and_null((void *)pipex_m->cmdpath);
	if (pipex_m->poss_path)
		free_and_null((void *)pipex_m->poss_path);
}

void	free_before_exit(t_alloc *mllcd, bool end)
{
	if (mllcd->in_pars.m_argv)
	{
		free_strstr(mllcd->in_pars.m_argv);
		mllcd->in_pars.m_argv = NULL;
	}
	if (mllcd->in_pars.cmd_table)
	{
		free_cmd_table(&mllcd->in_pars);
		mllcd->in_pars.cmd_table = NULL;
	}
	if (mllcd->saved_stdin != -1)
		close(mllcd->saved_stdin);
	if (end == false)
		return ;
	if (mllcd->env_list && end)
	{
		ft_lstclear(&mllcd->env_list);
		mllcd->env_list = NULL;
	}
	rl_clear_history();
}

void	exit_mllcfail(t_alloc *mllcd)
{
	int i;
	t_env *temp;

	i = mllcd->exit_status;
	free_before_exit(mllcd, true);
	temp = mllcd->env_list;
	while (temp)
	{
		if (temp->malloced == true)
			free(temp->env_var);
		temp = temp->next;
	}
	exit(i);
}