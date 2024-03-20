/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:04:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/03/20 16:19:40 by pgober           ###   ########.fr       */
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
		if (ft_strncmp(temp->env_var, "SHLVL=", 6) == 0)
		{
			// if (ft_atoi(temp->env_var + 6) > 1000)  can save the plase bc we will never get to that level
			// {
			// 	ft_putstr_fd("Error: Recursion level too deep.\n", 2);
			// 	return (1);
			// }
			// printf("SHLVL: %s\n", temp->env_var);
			temp2 = ft_itoa(ft_atoi(temp->env_var + 6) + 1);
			if (temp2 == NULL)
				return (1);
			temp->env_var = ft_strjoin("SHLVL=", temp2);
			free(temp2);
			temp->malloced = true;
			if (temp->env_var == NULL)
				return (1);
			// printf("new SHLVL: %s\n", temp->env_var);
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

void	ft_lstclear(t_env **env_list)
{
	t_env	*temp;

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

int	get_env(char **envv, t_env **head)
{
	int		i;
	t_env	*temp;

	i = 0;
	if (!envv[i] && *head)
		free(*head);
	*head = (t_env *)malloc(sizeof(t_env));
	if (*head == NULL)
		return (1);
	temp = *head;
	while (envv[i])
	{
		temp->env_var = envv[i];
		temp->malloced = false;
		if (envv[i + 1])
		{
			temp->next = (t_env *)malloc(sizeof(t_env));
			if (temp->next == NULL)
				return (ft_lstclear(head), 1);
			temp = temp->next;
			temp->env_var = NULL;
			temp->next = NULL;
		}
		i++;
	}
	return (0);
}

void	free_env_table(char **envv_table)
{
	int		i;

	i = 0;
	if (envv_table == NULL)
		return ;
    while (envv_table[i] != NULL)
		free_and_null(envv_table[i++]);
	free_and_null(envv_table);
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
	if (env_table == NULL)
		return (NULL);
	// printf("%d\n", i);
    pos = mllcd->env_list;
	i = 0;
    while (pos != NULL)
    {
		env_table[i] = ft_strdup(pos->env_var);
		if (!env_table[i])
		{
			free_env_table(env_table);
			return (NULL);
		}
		pos = pos->next;
		i++;
	}
	env_table[i] = NULL;
	return (env_table);
}
