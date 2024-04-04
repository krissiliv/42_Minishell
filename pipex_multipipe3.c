/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:15 by pgober            #+#    #+#             */
/*   Updated: 2024/04/04 11:03:47 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_multipipe.h"
#include "minishell.h"

static int	child_helper(t_alloc *mllcd, int cmd_file, int **pipe_ends)
{
	if (mllcd->pipex_m.cmdnum == 0 && \
		mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL)
	{
		if (dup2(cmd_file, 0) == -1)
		{
			close(cmd_file);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
	}
	else if (mllcd->pipex_m.cmdnum != 0)
	{
		if (dup2(pipe_ends[mllcd->pipex_m.cmdnum - 1][0], 0) == -1)
		{
			close(cmd_file);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
	}
	if (dup2(pipe_ends[mllcd->pipex_m.cmdnum][1], 1) == -1)
		return (pipex_error_handling(1, &mllcd->pipex_m));
	return (-1);
}

int	child(int **pipe_ends, t_alloc *mllcd, int *pid)
{
	int	cmd_file;
	int	i;

	cmd_file = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL)
		cmd_file = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1], \
		O_RDONLY);
	if (cmd_file == -1 && \
		mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL)
		return (pipex_error_handling(1, &mllcd->pipex_m));
	i = child_helper(mllcd, cmd_file, pipe_ends);
	if (i != -1)
		return (pipex_error_handling(1, &mllcd->pipex_m));
	close_pipes(mllcd->pipex_m.pipenum, pipe_ends, mllcd->pipex_m.pipenum);
	if (cmd_file != -1)
		close(cmd_file);
	i = execute(pipe_ends, mllcd);
	free_before_exit(mllcd, true);
	free(pid);
	exit(i);
}
