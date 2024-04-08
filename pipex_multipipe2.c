/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:43:26 by pgober            #+#    #+#             */
/*   Updated: 2024/04/08 16:13:40 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_multipipe.h"
#include "minishell.h"

static int	multi_execute_interpreter_input_redir(t_alloc *mllcd, int *in)
{
	*in = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1], O_RDONLY);
	if (*in == -1 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL)
		return (pipex_error_handling(2, &mllcd->pipex_m));
	if (*in != -1 && dup2(*in, 0) == -1)
	{
		close(*in);
		return (pipex_error_handling(4, &mllcd->pipex_m));
	}
	return (-1);
}

static int	multi_execute_interpreter_output_redir(t_alloc *mllcd)
{
	int	out;

	out = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2], \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1 && \
		mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2] != NULL)
		return (pipex_error_handling(10, &mllcd->pipex_m));
	if (out != -1 && dup2(out, 1) == -1)
	{
		close(out);
		return (pipex_error_handling(4, &mllcd->pipex_m));
	}
	return (-1);
}

int	multi_execute_interpreter(t_alloc *mllcd)
{
	int	c;
	int	in;

	mllcd->pipex_m.cmd = ft_split_w_quotes(mllcd->\
		in_pars.cmd_table[mllcd->pipex_m.cmdnum][0], ' ', &mllcd->in_pars);
	if (!(mllcd->pipex_m.cmd) || !(mllcd->pipex_m.cmd[0]) || \
		!(mllcd->pipex_m.cmd[0][0]))
		return (1);
	c = -1;
	while (mllcd->pipex_m.cmd[++c] && c < 6)
		mllcd->pipex_m.cmd[c] = ft_remove_quotes(mllcd->pipex_m.cmd[c]);
	in = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1])
	{
		c = multi_execute_interpreter_input_redir(mllcd, &in);
		if (c != -1)
			return (c);
	}
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2])
	{
		c = multi_execute_interpreter_output_redir(mllcd);
		if (c != -1)
			return (c);
	}
	return (0);
}

static int	execute_helper(t_alloc *mllcd, char **envv)
{
	if (access(mllcd->pipex_m.cmdpath, F_OK) != 0)
		return (free_env_table(envv),
			pipex_error_handling(127, &mllcd->pipex_m));
	if (access(mllcd->pipex_m.cmdpath, F_OK) == 0 && \
		access(mllcd->pipex_m.cmdpath, X_OK) != 0)
		return (free_env_table(envv),
			pipex_error_handling(126, &mllcd->pipex_m));
	if (execve(mllcd->pipex_m.cmdpath, mllcd->pipex_m.cmd, envv) == -1)
		return (free_env_table(envv),
			pipex_error_handling(3, &mllcd->pipex_m));
	return (-1);
}

int	execute(t_alloc *mllcd)
{
	char	**envv;
	int		res;

	if (multi_execute_interpreter(mllcd) || \
		str_is_empty(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][0]))
		return (pipex_free_all(&mllcd->pipex_m, NULL), 1);
	if (!ft_strcmp(mllcd->pipex_m.cmd[0], "exit") || \
		!ft_strcmp(mllcd->pipex_m.cmd[0], "cd") || \
		!ft_strcmp(mllcd->pipex_m.cmd[0], "export") || \
		!ft_strcmp(mllcd->pipex_m.cmd[0], "unset"))
		return (pipex_free_all(&mllcd->pipex_m, NULL), 0);
	res = builtins_2(mllcd->pipex_m.cmd, mllcd);
	if (res != -1)
		return (pipex_free_all(&mllcd->pipex_m, NULL), res);
	envv = convert_linkedlst_to_table(mllcd);
	mllcd->pipex_m.cmdpath = find_cmd_path(mllcd->pipex_m.cmd[0], envv, \
		&mllcd->pipex_m);
	if (mllcd->pipex_m.cmdpath == NULL)
		return (free_env_table(envv),
			pipex_error_handling(127, &mllcd->pipex_m));
	res = execute_helper(mllcd, envv);
	if (res != -1)
		return (res);
	return (free_env_table(envv), ft_putstr_fd("Something went wrong", 2),
		pipex_free_all(&mllcd->pipex_m, NULL), 0);
}
