/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe_interpreter.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:06:55 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 10:41:33 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipex_multipipe(t_alloc *mllcd, int argc, char **argv)
{
	int		**pipe_ends;
	int		i;

	if (argv[argc - 1] == NULL)
		return (1);
	mllcd->pipex_m.pipenum = mllcd->in_pars.pipenum;
	pipe_ends = (int **)malloc(2 * mllcd->pipex_m.pipenum * sizeof(int));
	if (!pipe_ends)
		return (pipex_error_handling(9, NULL));
	i = -1;
	while (++i < mllcd->pipex_m.pipenum)
	{
		pipe_ends[i] = (int *)malloc(2 * sizeof(int));
		if (!pipe_ends[i])
			return (pipex_error_handling(9, NULL));
	}
	i = -1;
	mllcd->pipex_m.cmd = NULL;
	mllcd->pipex_m.poss_paths = NULL;
	mllcd->pipex_m.cmdpath = NULL;
	mllcd->pipex_m.poss_path = NULL;
	while (++i < mllcd->pipex_m.pipenum)
	{
		if (pipe(pipe_ends[i]) == -1)
			return (pipex_error_handling(9, NULL));
	}
	return (pipex(pipe_ends, mllcd));
}
