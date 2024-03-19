/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:52:29 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/29 11:35:00 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_nodes_begin(t_env **env_list)
{
	t_env	*swap1;
	t_env	*swap2;
	t_env	*swap3;

	swap1 = *env_list;
	swap2 = swap1->next;
	swap3 = swap2->next;
	*env_list = swap2;
	swap2->next = swap1;
	swap1->next = swap3;
}

static void	swap_nodes_mid(t_env **env_list)
{
	t_env	*prev_node;
	t_env	*swap1;
	t_env	*swap2;
	t_env	*swap3;

	prev_node = *env_list;
	swap1 = (*env_list)->next;
	swap2 = swap1->next;
	swap3 = swap2->next;
	prev_node->next = swap2;
	swap2->next = swap1;
	swap1->next = swap3;
	*env_list = prev_node;
}

void	prnt_sortedlist(t_env *head)
{
	t_env *pos;

    pos = head;
	if (pos == NULL)
		printf("NULL\n");
    while (pos != NULL)
    {
        printf("declare -x %s\n", pos->env_var);
        pos = pos->next;
    }
}

t_env	*sort_list(t_env *env_list)
{
	t_env	*head;

	head = env_list;
	while (env_list->next && env_list->next->next)
	{
		if (env_list == head)
		{
			if (ft_strcmp(env_list->env_var, env_list->next->env_var) > 0)
			{
				swap_nodes_begin(&env_list);
				head = env_list;
			}
		}
		if (ft_strcmp(env_list->next->env_var, env_list->next->next->env_var) > 0)
		{
			swap_nodes_mid(&env_list);
			env_list = head;
		}
		else
			env_list = env_list->next;
	}
	env_list = head;
	return (env_list);
}

void	ft_lstadd_front(t_env **env_list, t_env *new_node)
{
	if (env_list && new_node)
	{
		if (*env_list)
			new_node->next = *env_list;
		*env_list = new_node;
	}
}