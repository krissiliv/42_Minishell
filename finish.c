/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:57:39 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:57:56 by pgober           ###   ########.fr       */
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
