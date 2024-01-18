/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 15:19:29 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_MULTIPIPE_H
# define PIPEX_MULTIPIPE_H

#include "minishell.h"
typedef struct s_pipex_m
{
	char	**cmd;
	char	*cmdpath;
	int		cmdnum;
	char	*poss_path;
	char	**poss_paths;
	int		compil_res;
	int		status;
	int		pipenum; // later this should come from s_input_parsing
	int		*pipe_ends;
}	t_pipex_m;

// cmd finder
char	**get_cmd_paths(char **envv);
char	*pipex_find_cmd_path(char *cmd, char **envv, t_pipex_m *pipex_m);

// error
int		pipex_error_handling(int *pipe_ends[], int pipenum, int err_code, t_pipex_m *pipex_m, bool pp);

//finish
void	pipex_free_all(t_pipex_m *pipex_m, int **pipe_ends);

//pipex multipipe
int		pipex_init(int *pipe_ends, int argc, char **argv, t_pipex_m *pipex_m);
int		pipex(int **pipe_ends, t_alloc *mllcd, char **envv);

// pipex multipipe interpreter
int		run_pipex_multipipe(t_alloc *mllcd, int argc, char **argv, char **envv)

#endif
