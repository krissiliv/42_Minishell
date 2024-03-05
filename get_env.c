/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:04:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/24 15:28:13 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	adapt_shlvl(t_alloc *mllcd)
{
	t_env	*temp;
	char 	*temp2;

	temp = mllcd->env_list;
	while (temp)
	{
		temp = temp->next;
		if (ft_strncmp(temp->env_var, "SHLVL=", 6) == 0)
		{
			// if (ft_atoi(temp->env_var + 6) > 1000)  can save the plase bc we will never get to that level
			// {
			// 	ft_putstr_fd("Error: Recursion level too deep.\n", 2);
			// 	return (1);
			// }
			// printf("SHLVL: %s\n", temp->env_var);
			temp2 = ft_itoa(ft_atoi(temp->env_var + 6) + 1);
			temp->env_var = ft_strjoin("SHLVL=", temp2);
			temp->malloced = true;
			free(temp2);
			// printf("new SHLVL: %s\n", temp->env_var);
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

int	get_env(char **envv, t_env **head)
{
	int		i;
	t_env	*temp;

	i = 0;
	if (!envv[i] && *head)
		free(*head);
	*head = (t_env *)malloc(sizeof(t_env));
	temp = *head;
	while (envv[i])
	{
		(*head)->env_var = envv[i];
		(*head)->malloced = false;
		if (envv[i + 1])
		{
			(*head)->next = (t_env *)malloc(sizeof(t_env));
			if ((*head)->next == NULL)
				return (1);
			(*head) = (*head)->next;
			(*head)->env_var = NULL;
			(*head)->next = NULL;
		}
		i++;
	}
	*head = temp;
	return (0);
}

void	ft_lstclear(t_env **env_list)
{
	t_env	*temp;

	if (!(*env_list))
		return ;
	while (*env_list)
	{
		temp = (*env_list)->next;
		if ((*env_list)->malloced == true)
			free_and_null((*env_list)->env_var);
		free_and_null(*env_list);
		*env_list = temp;
	}
	*env_list = NULL;
}

char	**convert_linkedlst_to_table(t_alloc *mllcd)
{
	char	**env_table;
	int		i;
	t_env	*pos;

    pos = mllcd->env_list;
	i = 0;
    while (pos != NULL)
    {
		pos = pos->next;
		i++;
	}
	env_table = (char **)malloc((i + 1) * sizeof(char *));
	// printf("%d\n", i);
    pos = mllcd->env_list;
	i = 0;
    while (pos != NULL)
    {
		env_table[i] = ft_strdup(pos->env_var);
		pos = pos->next;
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}

void	free_env_table(char **envv_table)
{
	int		i;

	i = 0;
    while (envv_table[i] != NULL)
		free_and_null(envv_table[i++]);
	free_and_null(envv_table);
}