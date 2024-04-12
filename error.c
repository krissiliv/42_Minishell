/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:58:26 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 19:12:46 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error_handler(t_alloc *mllcd, char *str)
{
	mllcd->exit_status = 1;
	ft_putendl_fd(str, 2);
}

void	case_with_minus(char **path, t_alloc *mllcd)
{
	free(*path);
	*path = find_envvar_value("OLDPWD", mllcd);
	pwd();
}

int	pipex_error_handling(int err_code, t_pipex_m *pipex_m)
{
	if (err_code == 127)
		ft_putstr_fd("Pipex-Error: command not found\n", 2);
	else if (err_code == 1)
		perror("minishell");
	else if (err_code == 2)
		ft_putstr_fd("Pipex-Error: Access to infile denied\n", 2);
	else if (err_code == 7)
		ft_putstr_fd("Pipex-Error: dup2 failed\n", 2);
	else if (err_code == 10)
		ft_putstr_fd("Pipex-Error: Access to outfile denied\n", 2);
	else if (err_code == 3)
		ft_putstr_fd("Pipex-Error: No such process!\n", 2);
	else if (err_code == 4)
		ft_putstr_fd("Pipex-Error: Interrupted system call. Permission denied.\n", 2);
	else if (err_code == 6)
		ft_putstr_fd("Pipex-Error: Forking process failed.\n", 2);
	else if (err_code == 8)
		ft_putstr_fd("Pipex-Error: Wrong number of arguments. Needed: 4\n", 2);
	else if (err_code == 9)
		ft_putstr_fd("Pipex-Error: Broken pipex. Pipex write error.\n", 2);
	pipex_free_all(pipex_m, NULL);
	return (err_code);
}
