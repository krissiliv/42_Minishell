/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:04:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 17:20:55 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env(char **envv, t_env *head)
{
	int		i;
	t_env	*temp;

	temp = head;
	i = 0;
	if (!envv[i])
		free(head);
	while (envv[i])
	{
		head->env_var = envv[i];
		head->malloced = false;
		if (envv[i + 1])
		{
			head->next = (t_env *)malloc(sizeof(t_env));
			if (head->next == NULL)
				return (1);
			head = head->next;
			head->env_var = NULL;
			head->next = NULL;
		}
		i++;
	}
	head = temp;
	return (0);
}