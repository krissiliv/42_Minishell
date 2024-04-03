/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 13:49:35 by pgober           ###   ########.fr       */
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
# include <signal.h>
 #include <sys/ioctl.h>

# include "libft/libft.h"

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

// signals
void 		signals(int mode);
extern int	g_sigint;

// PIA

// main
void	sigint_helper(t_alloc *mllcd);

// preparing minishell 2
int		put_space_before_special_operator(char **input_str);

//preparing minishell
int		preparing_minishell(t_alloc *mllcd, char *input_str);


//print prompt
char	*read_input_print_prompt(t_env **env_list);

//finish
void	free_cmd_table(t_input_parsing *in_pars);
void	free_before_exit(t_alloc *mllcd, bool end);
void	exit_mllcfail(t_alloc *mllcd);

// simple cmd execution
void    init_simple_cmd(t_pipex_m *simple_cmd);
int		run_simple_cmd(t_alloc *mllcd);

// expander
char	*find_envvar_value(char *envvar, t_alloc *mllcd);
int     expander(char **input_str, t_alloc *mllcd);

// heredocs
int		adapt_cmd_tble_to_heredocs(t_input_parsing *in_pars);
int		finish_heredocs(t_alloc *mllcd);

// outredir appendmode
int		outredir_appendmode(t_alloc *mllcd, int cmdnum);

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
int		adapt_shlvl(t_alloc *mllcd);
int		get_env(char **envv, t_env **head);
void	ft_lstclear(t_env **env_list);
char	**convert_linkedlst_to_table(t_alloc *mllcd);
void	free_env_table(char **envv);

//built-ins:
int		echo(char *cmd[]);
int		cd(char **cmd, int argc, t_alloc *mllcd);
int		pwd();
int		env(char **cmd, t_alloc mllcd);
int		exporting(char **cmd, t_alloc *mllcd);
int		unset(char **cmd, t_alloc *mllcd);
int		exiting(t_alloc *mllcd, char **cmd, int argc);

//atoi for exit builtin
int		is_num(char str);
int		is_pm(char str);
int		ft_atoi_minishell(const char *nptr, int *error);
int		validate_input(char *input);

//export utils
t_env	*ft_new_node(char *input);
void	ft_lstadd_front(t_env **env_list, t_env *new_node);
t_env	*sort_list(t_env **list);
void	prnt_sortedlist(t_env *head);

#endif