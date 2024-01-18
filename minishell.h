/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 14:06:40 by pgober           ###   ########.fr       */
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


// PIA
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


// NASTYA
typedef struct s_alloc
{
	int		exit_status; //put it in a global struct
}	t_alloc;


// stored environment
typedef struct	s_env
{
	char			*env_var;
	struct s_env	*next;
}	t_env;

//store environment
int		get_env(char **envv, t_env *head);

//built-ins:
int		echo(char **cmd, t_alloc *mllcd);
int		cd(char *path, int argc, t_env *env_list, t_alloc *mllcd);
int		pwd(t_alloc *mllcd);
int		env(t_env *env_list, t_alloc *mllcd);
int		exporting(t_env **env_list, char **cmd, t_alloc *mllcd);
int		unset(t_env **env_list, char **cmd, t_alloc *mllcd);
int		exiting(t_alloc *mllcd, char *input, int argc);

//atoi for exit builtin
int		is_num(char str);
int		is_pm(char str);
int		ft_atoi_minishell(const char *nptr);

#endif