/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:58:26 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 13:50:04 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_error_handling(int err_code, t_pipex_m *pipex_m)
{
	if (err_code == 127)
		perror("Pipex-Error: command not found\n");
	else if (err_code == 1)
		perror("minishell");
	else if (err_code == 2)
		perror("Pipex-Error: Access to infile denied\n");
	else if (err_code == 7)
		perror("Pipex-Error: dup2 failed\n");
	else if (err_code == 10)
		perror("Pipex-Error: Access to outfile denied\n");
	else if (err_code == 3)
		perror("Pipex-Error: No such process!\n");
	else if (err_code == 4)
		perror("Pipex-Error: Interrupted system call. Permission denied.\n");
	else if (err_code == 6)
		perror("Pipex-Error: Forking process failed.\n");
	else if (err_code == 8)
		perror("Pipex-Error: Wrong number of arguments. Needed: 4\n");
	else if (err_code == 9)
		perror("Pipex-Error: Broken pipex. Pipex write error.\n");
	pipex_free_all(pipex_m, NULL);
	return (err_code);
}
