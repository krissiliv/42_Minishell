/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:34 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:04:18 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_cmd_paths(char **envv)
{
	int		i;
	char	**paths;

	i = 0;
	while (envv[i] && ft_strncmp(envv[i], "PATH=", 5) != 0)
		i++;
	if (!envv[i])
		return (NULL);
	paths = ft_split(envv[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	**translated_pathsign(char *cmd)
{
	char	**paths;

	if (cmd[0] == '.')
	{
		paths = (char **)malloc(1 * sizeof(char *));
		if (!paths)
			return (NULL);
		paths[0] = NULL;
	}
	else
	{
		paths = (char **)malloc(2 * sizeof(char *));
		if (!paths)
			return (NULL);
		paths[0] = ft_strdup("/");
		if (!paths[0])
			return (free(paths), NULL);
		paths[1] = NULL;
	}
	return (paths);
}

static void	find_poss_paths(char *cmd, char **envv, t_pipex_m *pipex_m)
{
	if (cmd[0] == '.' || cmd[0] == '/')
		pipex_m->poss_paths = translated_pathsign(cmd);
	else
		pipex_m->poss_paths = get_cmd_paths(envv);
	if (!pipex_m->poss_paths && access(cmd, F_OK | X_OK) == 0)
	{
		pipex_m->poss_paths = (char **)malloc(2 * sizeof(char *));
		pipex_m->poss_paths[0] = ft_strdup(cmd);
		pipex_m->poss_paths[1] = NULL;
	}
}

char	*find_cmd_path(char *cmd, char **envv, t_pipex_m *pipex_m)
{
	int		i;

	i = 0;
	find_poss_paths(cmd, envv, pipex_m);
	if (!pipex_m->poss_paths)
		return (pipex_free_all(pipex_m, NULL), NULL);
	while (pipex_m->poss_paths[i])
	{
		pipex_m->poss_path = ft_strjoin(pipex_m->poss_paths[i++], "/");
		if (!pipex_m->poss_path)
			return (pipex_free_all(pipex_m, NULL), NULL);
		pipex_m->cmdpath = ft_strjoin_w_free(pipex_m->poss_path, cmd);
		pipex_m->poss_path = NULL;
		if (!pipex_m->cmdpath)
			return (pipex_free_all(pipex_m, NULL), NULL);
		if (access(pipex_m->cmdpath, F_OK | X_OK) == 0)
			return (free_strstr(pipex_m->poss_paths), pipex_m->cmdpath);
		else if (access(pipex_m->cmdpath, F_OK) == 0)
			return (pipex_free_all(pipex_m, NULL), NULL);
		free(pipex_m->cmdpath);
		pipex_m->cmdpath = NULL;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (free_strstr(pipex_m->poss_paths), cmd);
	return (pipex_free_all(pipex_m, NULL), NULL);
}
