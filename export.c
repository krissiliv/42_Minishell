/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:03:21 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/26 12:38:44 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_nodes_begin(t_env **env_list)
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

void	swap_nodes_mid(t_env **env_list)
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

static int	compare_env_var(char *env_var1, char *env_var2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var1[i] != '=' && env_var2[j] != '=' && env_var1[i] == env_var2[j])
	{
		if (env_var1[i + 1] == '=' && env_var2[j + 1] == '=')
			return (0);
		i++;
		j++;
	}
	return (1);
}

static int	check_exist_var(t_alloc *mllcd, char *input)
{
	t_env	*temp;
	int		flag;

	flag = 0;
	temp = mllcd->env_list;
	while (temp)
	{
		if (!compare_env_var(temp->env_var, input))
		{
			flag = 1;
			mllcd->exit_status = 0;
			temp->env_var = input;
		}
		temp = temp->next;
	}
	if (flag == 0)
	{
		mllcd->exit_status = 1;
		return (1);
	}
	else
		return (0);
}

static int	export_one(char *input, t_alloc *mllcd)
{
	if (ft_strchr(input, '=') != NULL)
	{
		if (input[0] == '=')
		{
			mllcd->exit_status = 1;
			return (1);
		}
		else if (check_exist_var(mllcd, input) == 1)
			ft_lstadd_front(&mllcd->env_list, ft_new_node(input));
	}
	else
		printf("\n");
	mllcd->exit_status = 0;
	return (0);
}

int	exporting(char **cmd, t_alloc *mllcd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		prnt_sortedlist(sort_list(mllcd->env_list));
	while (cmd[++i]) // ++ to jump over first one (which is "export")
	{
		if (export_one(cmd[i], mllcd))
			return (1);
	}
	return (0);
}

/* int	main(int argc, char *argv[], char **envv)
{
	t_env	*env_list;

	if (argv && argc)
	{
		env_list = (t_env *)malloc(sizeof(t_env));
		get_env(envv, &env_list);
		prnt_sortedlist(sort_list(env_list));
	}
} */