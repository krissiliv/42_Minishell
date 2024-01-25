/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:03:21 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/25 12:38:57 by apashkov         ###   ########.fr       */
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

//I need to change the following function, bc it has to modify the linked list

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
	while (cmd[++i]) // ++ to jump over first one (which is "export")
	{
		if (export_one(cmd[i], mllcd))
			return (1);
	}
	return (0);
}