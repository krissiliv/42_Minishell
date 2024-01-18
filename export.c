/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:03:21 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 11:02:53 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* export passes environment variables to other processes*/

#include "minishell.h"

static t_env	*ft_new_node(char *input)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_var = input;
	new_node->next = NULL;
	return (new_node);
}

static void	ft_lstadd_front(t_env **env_list, t_env *new_node)
{
	if (env_list)
	{
		if (*env_list)
			new_node->next = *env_list;
		*env_list = new_node;
	}
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

static int	check_exist_var(t_env *env_list, char *input)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (!compare_env_var(env_list->env_var, input))
		{
			env_list->env_var = input;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	export(t_env **env_list, char *input, t_alloc *mllcd)
{
	if (!input[0])
	{
		mllcd->exit_status = 1;
		return (ft_putstr_fd("No arguments\n", 2), 1);
	}
	if (ft_strchr(input, '=') != NULL)
	{
		if (input[0] == '=')
		{
			mllcd->exit_status = 1;
			return (1);
		}
		else if (check_exist_var(*env_list, input) == 1)
			ft_lstadd_front(env_list, ft_new_node(input));
	}
	else
		printf("\n");
	mllcd->exit_status = 0;
	return (0);
}