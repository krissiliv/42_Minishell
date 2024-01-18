/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 12:35:20 by apashkov         ###   ########.fr       */
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


// stored environment
typedef struct	s_env
{
	char			*env_var;
	struct s_env	*next;
}	t_env;

//store environment
int	get_env(char **envv, t_env *head);

//built-ins:
int echo(char *cmd, char *argv[], int argc, t_alloc *mllcd);
int cd(char *path, int argc, t_env *env_list, t_alloc *mllcd);
int pwd(t_alloc *mllcd);
int	env(t_env *env_list, t_alloc *mllcd);
int	export(t_env **env_list, char *input, t_alloc *mllcd);
int	unset(t_env **env_list, char *input, t_alloc *mllcd);
int	exit(t_alloc mallcd, char *input);

//atoi for exit builtin
int	is_num(char str);
int	is_pm(char str);
int	ft_atoi_minishell(const char *nptr);

#endif
