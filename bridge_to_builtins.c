/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:58:20 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 15:35:53 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  count_cmd_args(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    return (i);
}

int	builtins(char **cmd, t_alloc *mllcd) // this is actually like execute or execve
{
	if (!ft_strncmp("echo", cmd[0], 4))
		echo(cmd, mllcd);
	else if (!ft_strncmp("cd", cmd[0], 2))
		cd(cmd[1], count_cmd_args(cmd), mllcd);
	else if (!ft_strncmp("pwd", cmd[0], 3))
		pwd(mllcd);
	else if (!ft_strncmp("env", cmd[0], 3))
		env(mllcd); //works
	else if (!ft_strncmp("exporting", cmd[0], 6))
		exporting(cmd, mllcd); // should have no dollar signs
	else if (!ft_strncmp("unset", cmd[0], 5))
		unset(cmd, mllcd);
	else if (!ft_strncmp("exit", cmd[0], 4))
		exiting(mllcd, cmd[1], count_cmd_args(cmd));
	else 
		return (-1);
	return (0);
}
