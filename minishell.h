/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 12:48:16 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // fork
# include <sys/wait.h> // wait
# include "libft/libft.h"
# include <stdbool.h> // bool

typedef struct s_alloc
{
	char	**cmd;
	char	*cmdpath;
	int		cmdnum;
	char	*poss_path;
	char	**poss_paths;
	int		compil_res;
	pid_t	pid1;
	pid_t	pid2;
	int		status;
}	t_alloc;

void	free_strstr(char **str);
void	free_everything(t_alloc *mallcd);
char	**get_paths(char **envv);
char	*find_path(char *cmd, char **envv, t_alloc *mallcd);
int		error_handling(int *pipe_ends, int err_code, t_alloc *mallcd, bool pp);

#endif
