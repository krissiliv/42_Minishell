/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outredir_appendmode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:28 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:10:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outredir_appendmode(t_alloc *mllcd, int cmdnum)
{
	int	fd;

	fd = open(mllcd->in_pars.cmd_table[cmdnum][4], \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		mllcd->exit_status = 1;
		return (1);
	}
	if (dup2(fd, 1) == -1)
		return (mllcd->exit_status = 1, close(fd), 1);
	close(fd);
	return (0);
}
