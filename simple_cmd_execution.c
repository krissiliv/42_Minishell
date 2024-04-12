/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:33:51 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 13:58:56 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*choose_message(int m)
{
	if (m == 1)
		return ("Simplecmd-Error: \
		Could not convert env_list to env_table.\n");
	if (m == 2)
		return ("Simplecmd-Error: cmd not found.\n");
	if (m == 3)
		return ("Simplecmd-Error: Access to cmdpath denied\n");
	return ("Simplecmd-Error: Unknown error.\n");
}

static int	simple_execute(t_alloc *mllcd, char **cmd)
{
	char	*cmdpath;
	char	**envv;
	int		res;

	res = builtins_2(cmd, mllcd);
	if (res != -1)
		return (res);
	envv = convert_linkedlst_to_table(mllcd);
	if (!envv)
		return (ft_putstr_fd(choose_message(1), 2), 127);
	cmdpath = find_cmd_path(cmd[0], envv, &mllcd->simple_cmd);
	if (cmdpath == NULL)
		return (free_env_table(envv), ft_putstr_fd(choose_message(2), 2), 127);
	if (access(cmdpath, F_OK) != 0 || !ft_strcmp(cmd[0], ".") || \
		!ft_strcmp(cmd[0], ".."))
		return (free_env_table(envv), ft_putstr_fd(choose_message(2), 2), 127);
	if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) != 0)
		return (free_env_table(envv), ft_putstr_fd(choose_message(3), 2), \
			126);
	if (execve(cmdpath, cmd, envv) == -1)
		return (free_env_table(envv),
			ft_putstr_fd("Simplecmd-Error: Is a directory\n", 2), 126);
	return (ft_putstr_fd(cmd[0], 2),
		ft_putstr_fd("\nSimplecmd-Error: cmd not found.\n", 2), 127);
}

static void	run_simple_cmd_get_cmd(t_alloc *mllcd, char ***cmd)
{
	int		c;

	*cmd = ft_split_w_quotes(mllcd->in_pars.cmd_table[0][0], ' ', \
		&mllcd->in_pars);
	if (!(*cmd))
		exit_mllcfail(mllcd);
	c = 0;
	while ((*cmd)[c] && c < 6)
	{
		(*cmd)[c] = ft_remove_quotes((*cmd)[c]);
		if (!(*cmd)[c])
		{
			free_strstr((*cmd));
			exit_mllcfail(mllcd);
		}
		c++;
	}
}

static void	run_simple_cmd_helper(t_alloc *mllcd, char **cmd)
{
	signals(2);
	if (simple_execute_interpreter(mllcd))
	{
		if (cmd)
			free_strstr(cmd);
		free_before_exit(mllcd, true);
		exit(1);
	}
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free_strstr(cmd);
		free_before_exit(mllcd, true);
		exit(mllcd->exit_status);
	}
	mllcd->exit_status = simple_execute(mllcd, cmd);
	free_strstr(cmd);
	free_before_exit(mllcd, true);
}

int	run_simple_cmd(t_alloc *mllcd)
{
	int		pid;
	char	**cmd;
	int		res;

	init_simple_cmd(&mllcd->simple_cmd);
	run_simple_cmd_get_cmd(mllcd, &cmd);
	res = builtins_1(cmd, mllcd);
	if (res != -1)
		return (free_strstr(cmd), res);
	pid = fork();
	if (pid < 0)
		return (ft_lstclear(&mllcd->env_list), free_strstr(cmd),
			ft_putstr_fd("Simplecmd-Error: forking process failed.\n", 2), 6);
	else if (pid == 0)
	{
		run_simple_cmd_helper(mllcd, cmd);
		exit(mllcd->exit_status);
	}
	if (waitpid(pid, &mllcd->simple_cmd.compil_res, 0) == -1)
	{
		free_strstr(cmd);
		exit_mllcfail(mllcd);
	}
	mllcd->exit_status = WEXITSTATUS(mllcd->simple_cmd.compil_res);
	return (free_strstr(cmd), mllcd->exit_status);
}
