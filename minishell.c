/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:20 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:48:28 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(int *pipe_ends, char **argv, char **envv, t_alloc *mallcd)
{
	mallcd->cmd = ft_split(argv[mallcd->cmdnum], ' ');
	if (!mallcd->cmd)
		return (free_everything(mallcd), 0);
	mallcd->cmdpath = find_path(mallcd->cmd[0], envv, mallcd);
	if (mallcd->cmdpath == NULL)
		return (error_handling(pipe_ends, 127, mallcd, true));
	if (access(mallcd->cmdpath, F_OK) == 0 && \
		access(mallcd->cmdpath, X_OK) != 0)
		return (free_everything(mallcd), \
				error_handling(pipe_ends, 1, mallcd, true));
	if (execve(mallcd->cmdpath, mallcd->cmd, envv) == -1)
		return (error_handling(pipe_ends, 3, mallcd, true));
	ft_putstr_fd("Something went wrong", 2);
	return (free_everything(mallcd), 0);
}

int	child1(int *pipe_ends, char **argv, char **envv, t_alloc *mallcd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (error_handling(pipe_ends, 1, mallcd, true));
	if (dup2(infile, 0) == -1)
	{
		close(infile);
		return (error_handling(pipe_ends, 4, mallcd, true));
	}
	if (dup2(pipe_ends[1], 1) == -1)
		return (error_handling(pipe_ends, 1, mallcd, true));
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	close(infile);
	mallcd->cmdnum = 2;
	exit (execute(pipe_ends, argv, envv, mallcd));
}

int	child2(int *pipe_ends, char **argv, char **envv, t_alloc *mallcd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		return (error_handling(pipe_ends, 1, mallcd, true));
	if (dup2(outfile, 1) == -1)
	{
		close(outfile);
		return (error_handling(pipe_ends, 4, mallcd, true));
	}
	if (dup2(pipe_ends[0], 0) == -1)
		return (error_handling(pipe_ends, 1, mallcd, true));
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	close(outfile);
	mallcd->cmdnum = 3;
	exit (execute(pipe_ends, argv, envv, mallcd));
}

int	pipex(int *pipe_ends, char **argv, char **envv, t_alloc *mallcd)
{
	mallcd->status = 0;
	mallcd->pid1 = fork();
	if (mallcd->pid1 < 0)
		return (error_handling(pipe_ends, 6, mallcd, true));
	else if (mallcd->pid1 == 0)
	{
		mallcd->compil_res = child1(pipe_ends, argv, envv, mallcd);
		if (mallcd->compil_res != 0)
			return (free_everything(mallcd), mallcd->compil_res);
	}
	mallcd->pid2 = fork();
	if (mallcd->pid2 < 0)
		return (error_handling(pipe_ends, 6, mallcd, true));
	else if (mallcd->pid2 == 0)
	{
		mallcd->compil_res = child2(pipe_ends, argv, envv, mallcd);
		if (mallcd->compil_res != 0)
			return (free_everything(mallcd), mallcd->compil_res);
	}
	close (pipe_ends[0]);
	close (pipe_ends[1]);
	waitpid(mallcd->pid1, NULL, 0);
	waitpid(mallcd->pid2, &(mallcd->status), 0);
	return (free_everything(mallcd), WEXITSTATUS(mallcd->status));
}

int	main(int argc, char **argv, char **envv)
{
	int		pipe_ends[2];
	t_alloc	mallcd;

	if (argc != 5 || (argc == 5 && !(argv[1][0])))
		return (error_handling(pipe_ends, 8, NULL, false));
	mallcd.cmd = NULL;
	mallcd.poss_paths = NULL;
	mallcd.cmdpath = NULL;
	mallcd.poss_path = NULL;
	if (pipe(pipe_ends) == -1)
		return (error_handling(pipe_ends, 9, NULL, false));
	return (pipex(pipe_ends, argv, envv, &mallcd));
}
