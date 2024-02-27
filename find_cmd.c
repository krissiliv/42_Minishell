/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:34 by pgober            #+#    #+#             */
/*   Updated: 2024/02/07 15:59:17 by apashkov         ###   ########.fr       */
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
	return (paths);
}

static char	**translated_pathsign(char *cmd)
{
	char	**paths;

	if (cmd[0] == '.')
	{
		paths = (char **)malloc(1 * sizeof(char *));
		paths[0] = NULL; //file is in current dir
	}
	else
	{
		paths = (char **)malloc(2 * sizeof(char *));
		paths[0] = ft_strdup("/");
		paths[1] = NULL;
	}
	return (paths);
}

char	*find_cmd_path(char *cmd, char **envv, t_pipex_m *pipex_m)
{
	int		i;

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		pipex_m->poss_paths = translated_pathsign(cmd);
	else
		pipex_m->poss_paths = get_cmd_paths(envv);
	if (!pipex_m->poss_paths)
		return (pipex_free_all(pipex_m, NULL), NULL);
	while (pipex_m->poss_paths[i])
	{
		pipex_m->poss_path = ft_strjoin(pipex_m->poss_paths[i++], "/");
		if (!pipex_m->poss_path)
			return (pipex_free_all(pipex_m, NULL), NULL);
		pipex_m->cmdpath = ft_strjoin(pipex_m->poss_path, cmd);
		if (!pipex_m->cmdpath)
			return (pipex_free_all(pipex_m, NULL), NULL);
		if (access(pipex_m->cmdpath, F_OK | X_OK) == 0)
			return (pipex_m->cmdpath);
		free(pipex_m->poss_path);
		pipex_m->poss_path = NULL;
		free(pipex_m->cmdpath);
		pipex_m->cmdpath = NULL;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (pipex_free_all(pipex_m, NULL), NULL);
}
