/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:20 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 18:13:02 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_multipipe.h"
#include "minishell.h"

static int	last_child_outredir(t_alloc *mllcd, int *outfile)
{
	*outfile = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2], \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*outfile == -1 && \
		mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2] != NULL)
		return (pipex_error_handling(10, &mllcd->pipex_m));
	if (*outfile != -1 && dup2(*outfile, 1) == -1)
	{
		close(*outfile);
		return (pipex_error_handling(4, &mllcd->pipex_m));
	}
	return (-1);
}

int	last_child(int **pipe_ends, t_alloc *mllcd, int *pid)
{
	int	outfile;
	int	i;

	outfile = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2])
	{
		i = last_child_outredir(mllcd, &outfile);
		if (i != -1)
			return (i);
	}
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][4])
	{
		if (outredir_appendmode(mllcd, mllcd->pipex_m.cmdnum))
			return (pipex_error_handling(10, &mllcd->pipex_m));
	}
	if (dup2(pipe_ends[mllcd->pipex_m.cmdnum - 1][0], 0) == -1)
		return (pipex_error_handling(1, &mllcd->pipex_m));
	close_pipes(mllcd->pipex_m.pipenum, pipe_ends, mllcd->pipex_m.pipenum);
	if (outfile != -1)
		close(outfile);
	i = execute(mllcd);
	free_before_exit(mllcd, true);
	free(pid);
	exit(i);
}

static int	pipex_helper(int *i, int **pid, int **pipe_ends, t_alloc *mllcd)
{
	while (*i < mllcd->pipex_m.pipenum)
	{
		mllcd->pipex_m.cmdnum = *i;
		(*pid)[*i] = fork();
		if ((*pid)[*i] < 0)
			return (pipex_error_handling(6, &mllcd->pipex_m));
		else if ((*pid)[*i] == 0)
		{
			signals(4);
			mllcd->pipex_m.compil_res = child(pipe_ends, mllcd, *pid);
			if (mllcd->pipex_m.compil_res != 0)
				return (pipex_free_all(&mllcd->pipex_m, pipe_ends), \
					mllcd->pipex_m.compil_res);
			break ;
		}
		(*i)++;
	}
	mllcd->pipex_m.cmdnum = *i;
	return (-1);
}

static void	pipex_helper2(int **pid, int **pipe_ends, t_alloc *mllcd)
{
	int	i;

	close_pipes(mllcd->pipex_m.pipenum, pipe_ends, mllcd->pipex_m.pipenum);
	i = -1;
	while (++i < mllcd->pipex_m.pipenum)
		waitpid((*pid)[i], NULL, 0);
	waitpid((*pid)[i], &(mllcd->pipex_m.status), 0);
	mllcd->exit_status = WEXITSTATUS(mllcd->pipex_m.status);
}

int	pipex(int **pipe_ends, t_alloc *mllcd)
{
	int	i;
	int	j;
	int	*pid;

	pid = malloc(sizeof(int) * (mllcd->pipex_m.pipenum + 1));
	if (!pid)
		return (pipex_error_handling(1, &mllcd->pipex_m));
	mllcd->pipex_m.status = 0;
	i = 0;
	j = pipex_helper(&i, &pid, pipe_ends, mllcd);
	if (j != -1)
		return (free(pid), j);
	pid[i] = fork();
	if (pid[i] < 0)
		return (free(pid), pipex_error_handling(6, &mllcd->pipex_m));
	else if (pid[i] == 0)
	{
		signals(4);
		mllcd->pipex_m.compil_res = last_child(pipe_ends, mllcd, pid);
		if (mllcd->pipex_m.compil_res != 0)
			return (free(pid), pipex_free_all(&mllcd->pipex_m, pipe_ends), \
				mllcd->pipex_m.compil_res);
	}
	return (pipex_helper2(&pid, pipe_ends, mllcd), free(pid),
		pipex_free_all(&mllcd->pipex_m, NULL), mllcd->exit_status);
}
