/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:58:26 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:58:45 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handling(int *pipe_ends, int err_code, t_alloc *mallcd, bool pp)
{
	if (pp)
	{
		close (pipe_ends[0]);
		close (pipe_ends[1]);
	}
	if (err_code == 127)
		ft_putstr_fd("Pipex-Error: command not found\n", 2);
	if (err_code == 1)
		perror("Pipex-Error");
	if (err_code == 3)
		perror("Pipex-Error: No such process!\n");
	if (err_code == 4)
		perror("Pipex-Error: Interrupted system call. Permission denied.\n");
	if (err_code == 6)
		perror("Pipex-Error: Forking process failed.\n");
	if (err_code == 8)
		perror("Pipex-Error: Wrong number of arguments. Needed: 4\n");
	if (err_code == 9)
		perror("Pipex-Error: Broken pipe. Pipe write error.\n");
	free_everything(mallcd);
	return (err_code);
}
