/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:24:59 by pgober            #+#    #+#             */
/*   Updated: 2024/01/05 12:40:58 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_ast_creater.h"

void    free_ast(t_ast *head)
{ 
    t_ast *pos;
    t_ast *next;
	int		j;

    pos = head;
	j = -1;
	while (++j < 2)
		free(pos->first_branch->bdata[j]);
	free(pos->first_branch->bdata); // this is the duplicate of cmd_table[i]
	free(pos->first_branch);
    while (pos != NULL)
    {
        next = pos->next;
        free(pos->data);
		j = -1;
		while (++j < 2)
        	free(pos->branch->bdata[j]);
		free(pos->branch->bdata); // this is the duplicate of cmd_table[i]
		free(pos->branch);
        free(pos);
        pos = next;
    }
}

void	prnt_ast(t_ast *head)
{
	t_ast	*pos;
	int		i;

	pos = head;
	while (pos != NULL)
	{
		ft_putstr_fd("node data: ", 1);
		ft_putstr_fd(pos->data, 1);
		if (pos == head)
		{
			ft_putstr_fd("\n	---> first node (first) branch data: ", 1);
			i = 0;
			while (i < 2)
			{
				ft_putstr_fd(pos->first_branch->bdata[i++], 1);
				if (i != 2)
					ft_putstr_fd(", ", 1);
			}
		}
		ft_putstr_fd("\n	---> node branch data: ", 1);
		i = 0;
		while (i < 2)
		{
			ft_putstr_fd(pos->branch->bdata[i++], 1);
			if (i != 2)
				ft_putstr_fd(", ", 1);
		}
		ft_putstr_fd("\n", 1);
		pos = pos->next;
	}
}