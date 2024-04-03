/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:58:20 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 17:12:09 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmd_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	builtins_1(char **cmd, t_alloc *mllcd)
{
	if (!ft_strcmp("cd", cmd[0]))
		cd(cmd, count_cmd_args(cmd), mllcd);
	else if (!ft_strcmp("export", cmd[0]))
		exporting(cmd, mllcd);
	else if (!ft_strcmp("unset", cmd[0]))
		unset(cmd, mllcd);
	else if (!ft_strcmp("exit", cmd[0]))
		exiting(mllcd, cmd, count_cmd_args(cmd));
	else
		return (-1);
	return (0);
}

int	builtins_2(char **cmd, t_alloc *mllcd)
{
	if (!ft_strcmp("echo", cmd[0]))
		return (echo(cmd));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (pwd());
	else if (!ft_strcmp("env", cmd[0]))
		return (env(cmd, *mllcd));
	else
		return (-1);
	return (0);
}

int	builtins_all(char **cmd, t_alloc *mllcd)
{
	if (!ft_strcmp("echo", cmd[0]))
		return (echo(cmd));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (pwd());
	else if (!ft_strcmp("env", cmd[0]))
		return (env(cmd, *mllcd));
	else if (!ft_strcmp("export", cmd[0]))
		return (exporting(cmd, mllcd));
	else if (!ft_strcmp("unset", cmd[0]))
		return (unset(cmd, mllcd));
	else if (!ft_strcmp("exit", cmd[0]))
		return (exiting(mllcd, cmd, count_cmd_args(cmd)));
	else if (!ft_strcmp("cd", cmd[0]))
		return (cd(cmd, count_cmd_args(cmd), mllcd));
	else
		return (-1);
	return (0);
}
