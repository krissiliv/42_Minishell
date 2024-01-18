/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_creater.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:26:22 by pgober            #+#    #+#             */
/*   Updated: 2024/01/05 12:41:04 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_REMOVE_IF_H
#define FT_LIST_REMOVE_IF_H

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
# include "../minishell.h"

typedef struct	s_ast
{
	struct s_ast	*next;
	char			*data;
	struct s_ast	*branch;
	struct s_ast	*first_branch; // exactly like branch but contains the very first command [cmd -option, file]
	char			**bdata;
}	t_ast;

// ast utils
void    free_ast(t_ast *head);
void	prnt_ast(t_ast *head);

#endif