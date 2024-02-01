/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/31 11:47:08 by apashkov         ###   ########.fr       */
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

//NASTYA
// stored environment
typedef struct	s_env
{
	char			*env_var;
	bool			malloced;
	struct s_env	*next;
}	t_env;

typedef struct s_alloc
{
	t_pipex_m		simple_cmd;
	t_pipex_m		pipex_m;
	t_env			*env_list;
	t_input_parsing	in_pars;
	int				saved_stdin;
	int				exit_status; //put it in a global struct
}	t_alloc;

// PIA
// signals
void signals(void);

//print prompt
char	*read_input_print_prompt(void);

//finish
void	free_cmd_table(t_input_parsing *in_pars);
void	free_env_table(char **envv);
void	free_everything(t_alloc *mllcd, int **pipe_ends);
// void	general_free_all(char **m_argv);

// simple cmd execution
void    init_simple_cmd(t_pipex_m *simple_cmd);
int		run_simple_cmd(t_alloc *mllcd);

// expander
char	*find_envvar_value(char *envvar, t_alloc *mllcd);
int     expander(char **input_str, t_alloc *mllcd);

// heredocs
int		handle_heredocs(t_alloc *mllcd);

// outredir appendmode
void	outredir_appendmode(t_alloc *mllcd, int cmdnum);

//pipex multipipe
int		pipex(int **pipe_ends, t_alloc *mllcd);

// pipex multipipe interpreter
int		run_pipex_multipipe(t_alloc *mllcd, int argc, char **argv);

// bridge to builtins
int		builtins_1(char **cmd, t_alloc *mllcd);
int		builtins_2(char **cmd, t_alloc *mllcd);
int		builtins_all(char **cmd, t_alloc *mllcd);

// NASTYA
//store environment
char	**convert_linkedlst_to_table(t_alloc *mllcd);
int		get_env(char **envv, t_env **head);
void	ft_lstclear(t_env **env_list);
void 	prntlist(t_env *head);

//built-ins:
int		echo(char *cmd[]);
int		cd(char *path, int argc, t_alloc *mllcd);
int		pwd();
int		env(char **cmd, t_alloc mllcd);
int		exporting(char **cmd, t_alloc *mllcd);
int		unset(char **cmd, t_alloc *mllcd);
int		exiting(t_alloc *mllcd, char *input, int argc);

//atoi for exit builtin
int		is_num(char str);
int		is_pm(char str);
int		ft_atoi_minishell(const char *nptr);

//export utils
t_env	*ft_new_node(char *input);
void	ft_lstadd_front(t_env **env_list, t_env *new_node);
t_env	*sort_list(t_env *env_list);
void	prnt_sortedlist(t_env *head);

#endif