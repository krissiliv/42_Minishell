/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_execution2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:25:06 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 20:35:36 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_simple_cmd(t_pipex_m *simple_cmd)
{
	simple_cmd->cmd = NULL;
	simple_cmd->poss_paths = NULL;
	simple_cmd->cmdpath = NULL;
	simple_cmd->poss_path = NULL;
	simple_cmd->compil_res = 0;
	simple_cmd->status = 0;
}

static int	simple_execute_interpreter_input_redir(t_alloc *mllcd, int *in)
{
	*in = open(mllcd->in_pars.cmd_table[0][1], O_RDONLY);
	if (*in == -1 && mllcd->in_pars.cmd_table[0][1] != NULL)
		return (perror("minishell"), 1);
	if (*in != -1 && dup2(*in, 0) == -1)
	{
		close(*in);
		return (ft_putstr_fd("Simplecmd-Error: Interrupted system call. \
			Permission for input-file denied.\n", 2), 4);
	}
	close(*in);
	return (-1);
}

static int	simple_exec_interpt_output_redir(t_alloc *mllcd, int *out, int in)
{
	char	*temp;
	char	*temp2;

	temp2 = ft_strdup(mllcd->in_pars.cmd_table[0][2]);
	if (!temp2)
		return (1);
	temp = ft_strtrim(temp2, " ");
	if (!temp)
		return (free(temp2), 1);
	temp2 = ft_strchr(temp, ' ');
	free(temp);
	if (temp2)
		return (ft_putendl_fd("minishell: ambiguous redirect", 2), 1);
	*out = open(mllcd->in_pars.cmd_table[0][2], \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*out == -1 && mllcd->in_pars.cmd_table[0][2] != NULL)
		return (perror("minishell"), 1);
	if (*out != -1 && dup2(*out, 1) == -1)
	{
		if (in != -1)
			close(in);
		return (perror("minishell"), close(*out), 4);
	}
	return (close(*out), -1);
}

int	simple_execute_interpreter(t_alloc *mllcd)
{
	int	out;
	int	in;
	int	res;

	if (mllcd->in_pars.cmd_table[0][1])
	{
		res = simple_execute_interpreter_input_redir(mllcd, &in);
		if (res != -1)
			return (res);
	}
	if (mllcd->in_pars.cmd_table[0][4])
	{
		if (outredir_appendmode(mllcd, 0))
			return (perror("Simplecmd-Error: Access to outfile denied\n"), 1);
	}
	if (mllcd->in_pars.cmd_table[0][2])
	{
		if (mllcd->in_pars.cmd_table[0][2][0] == '\0')
			return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), 1);
		res = simple_exec_interpt_output_redir(mllcd, &out, in);
		if (res != -1)
			return (res);
	}
	return (0);
}
