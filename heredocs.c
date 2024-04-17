/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:53:30 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:04:52 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static char	*return_message(int i)
{
	if (i == 1)
		return ("Pipex-Error: Could not open file for heredoc.\n");
	return (NULL);
}

static int	handle_heredoc_helper(char *gnl, int fd_here_document, \
	t_alloc *mllcd)
{
	if (expander(&gnl, mllcd))
		return (close(fd_here_document), free(gnl),
			exit_mllcfail(mllcd), 1);
	ft_putstr_fd(gnl, fd_here_document);
	ft_putstr_fd("\n", fd_here_document);
	free(gnl);
	return (0);
}

static int	handle_heredocs(t_input_parsing *in_pars, int cmdnum, \
	t_alloc *mllcd)
{
	char	*gnl;
	int		fd_here_document;

	fd_here_document = open("heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_here_document == -1)
		return (ft_putstr_fd(return_message(1), 2), 1);
	signals(3);
	gnl = readline("> ");
	if (!gnl)
		gnl = ft_strdup(in_pars->cmd_table[cmdnum][3]);
	while ((ft_strcmp(gnl, in_pars->cmd_table[cmdnum][3]) != 0) && \
		g_sigint != SIGINT)
	{
		if (handle_heredoc_helper(gnl, fd_here_document, mllcd) == 1)
			return (1);
		gnl = readline("> ");
		if (!gnl)
			gnl = ft_strdup(in_pars->cmd_table[cmdnum][3]);
		if (g_sigint == SIGINT)
			break ;
	}
	return (close(fd_here_document), free(gnl), 0);
}

int	adapt_cmd_tble_to_heredocs(t_input_parsing *in_pars, t_alloc *mllcd)
{
	int	i;

	i = 0;
	while (i < in_pars->pipenum + 1)
	{
		if (in_pars->cmd_table[i][3])
		{
			if (in_pars->last_in[i] == 3)
			{
				free(in_pars->cmd_table[i][1]);
				in_pars->cmd_table[i][1] = ft_strdup("heredoc.tmp");
			}
			if (handle_heredocs(in_pars, i, mllcd) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
