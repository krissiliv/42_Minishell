/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 11:27:14 by apashkov         ###   ########.fr       */
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
	int		exit_status; //put it in a global struct
}	t_alloc;

// cmd finder
char	**get_paths(char **envv);
char	*find_path(char *cmd, char **envv, t_alloc *mallcd);

// error
int		error_handling(int *pipe_ends, int err_code, t_alloc *mallcd, bool pp);

//input check

//finish
void	free_strstr(char **str);
void	free_everything(t_alloc *mallcd);

//pipex
int	pipex(int *pipe_ends, char **argv, char **envv, t_alloc *mallcd);

#endif
