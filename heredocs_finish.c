/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:27:07 by pgober            #+#    #+#             */
/*   Updated: 2024/04/05 18:28:38 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finish_heredocs_helper(t_alloc *mllcd)
{
	char	*cmdpath;
	char	**env_table;

	env_table = convert_linkedlst_to_table(mllcd);
	if (!env_table)
		exit_mllcfail(mllcd);
	cmdpath = find_cmd_path("rm", env_table, &mllcd->simple_cmd);
	if (!cmdpath)
		exit_mllcfail(mllcd);
	free_before_exit(mllcd, true);
	if (access("heredoc.tmp", F_OK) == 0)
		execve(cmdpath, (char *[]){"rm", "heredoc.tmp", NULL}, env_table);
	exit(0);
}

int	finish_heredocs(t_alloc *mllcd)
{
	bool	here_doc_exists;
	int		i;
	int		child_status;

	i = -1;
	here_doc_exists = false;
	while (++i < mllcd->in_pars.pipenum + 1)
	{
		if (mllcd->in_pars.cmd_table[i][3])
			here_doc_exists = true;
	}
	if (!here_doc_exists)
		return (0);
	i = fork();
	if (i == -1)
		return (ft_putstr_fd("Pipex-Error: \
            Could not fork for heredoc.\n", 2), 1);
	if (i == 0)
		finish_heredocs_helper(mllcd);
	if (waitpid(i, &child_status, 0) == -1)
		exit_mllcfail(mllcd);
	return (0);
}
