/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/05 15:21:13 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // fork
# include <sys/wait.h> // wait
# include <stdbool.h> // bool
# include "readline/readline.h" //readline
# include "readline/history.h" //readline

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# include "input_parser.h"
# include "pipex_multipipe.h"

//print prompt
char	*read_input_print_prompt(void);

//finish
void	free_cmd_table(t_input_parsing *in_pars);
void	general_free_all(char **m_argv);

// simple cmd execution
void    init_simple_cmd(t_pipex_m *simple_cmd);
int	    run_simple_cmd(t_input_parsing *in_pars, t_pipex_m *simple_cmd, char **envv);

// expander
int     expander(char **input_str, char **envv);

// heredocs
int    handle_heredocs(char **envv, t_input_parsing *in_pars, t_pipex_m *simple_cmd);

// filefinder
// char	*get_curr_dir(char **envv);

#endif