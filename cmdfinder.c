/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:34 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:58:38 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
