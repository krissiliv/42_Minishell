/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:03:21 by apashkov          #+#    #+#             */
/*   Updated: 2024/02/07 19:17:25 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_node(char *input)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_var = ft_strdup(input);
	if (!new_node->env_var)
	{
		free(new_node);
		return (NULL);
	}
	new_node->malloced = true;
	new_node->next = NULL;
	return (new_node);
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
			if (temp->malloced)
				free(temp->env_var);
			temp->env_var = ft_strdup(input);
			temp->malloced = true;
		}
		temp = temp->next;
	}
	if (flag == 0)
		return (1);
	else
		return (0);
}

static int	export_one(char *input, t_alloc *mllcd)
{
	int	i;
	int	err_flag;

	i = -1;
	err_flag = 0;
	if (!validate_input(input) || input[0] == '=' || (!ft_isalpha(input[0]) && input[0] != '_'))
		err_flag = 1;
	if (ft_strchr(input, '=') != NULL)
	{
		while (input[++i] && input[i] != '=')
		{
			if (!ft_isalpha(input[i]) && input[i] != '_' && !ft_isdigit(input[i]))
				err_flag = 1;
		}
		if (check_exist_var(mllcd, input) == 1)
			ft_lstadd_front(&mllcd->env_list, ft_new_node(input));
	}
	if (err_flag == 1)
		return (ft_putstr_fd("export: not a valid identifier\n", 2), 1);
	else
		return (0);
}

int	exporting(char **cmd, t_alloc *mllcd)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		mllcd->exit_status = 0;
		return (prnt_sortedlist(sort_list(mllcd->env_list)), 0);
	}
	if (cmd[1][0] == '-')
	{
		mllcd->exit_status = 2;
		return (ft_putstr_fd("export: invalid option\n", 2), 2);
	}
	while (cmd[++i])
	{
		if (export_one(cmd[i], mllcd))
		{
			mllcd->exit_status = 1;
			return (1);
		}
	}
	mllcd->exit_status = 0;
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