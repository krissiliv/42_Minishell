/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:34 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:48:35 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strstr(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_everything(t_alloc *mallcd)
{
	if (!mallcd)
		return ;
	if (mallcd->cmd)
	{
		free_strstr(mallcd->cmd);
		mallcd->cmd = NULL;
	}
	if (mallcd->poss_paths)
	{
		free_strstr(mallcd->poss_paths);
		mallcd->poss_paths = NULL;
	}
	if (mallcd->cmdpath)
	{
		free(mallcd->cmdpath);
		mallcd->cmdpath = NULL;
	}
	if (mallcd->poss_path)
	{
		free(mallcd->poss_path);
		mallcd->poss_path = NULL;
	}
}

char	**get_paths(char **envv)
{
	int		i;
	char	**paths;

	i = 0;
	while (envv[i] && ft_strncmp(envv[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envv[i] + 5, ':');
	return (paths);
}

char	*find_path(char *cmd, char **envv, t_alloc *mallcd)
{
	int		i;

	i = 0;
	mallcd->poss_paths = get_paths(envv);
	if (!mallcd->poss_paths)
		return (free_everything(mallcd), NULL);
	while (mallcd->poss_paths[i])
	{
		mallcd->poss_path = ft_strjoin(mallcd->poss_paths[i++], "/");
		if (!mallcd->poss_path)
			return (free_everything(mallcd), NULL);
		mallcd->cmdpath = ft_strjoin(mallcd->poss_path, cmd);
		if (!mallcd->cmdpath)
			return (free_everything(mallcd), NULL);
		if (access(mallcd->cmdpath, F_OK | X_OK) == 0)
			return (mallcd->cmdpath);
		free(mallcd->poss_path);
		mallcd->poss_path = NULL;
		free(mallcd->cmdpath);
		mallcd->cmdpath = NULL;
	}
	return (free_everything(mallcd), NULL);
}

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
