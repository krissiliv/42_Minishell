/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:52:29 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/25 16:53:04 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_node(char *input)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_var = input;
	new_node->malloced = false;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_front(t_env **env_list, t_env *new_node)
{
	if (env_list)
	{
		if (*env_list)
			new_node->next = *env_list;
		*env_list = new_node;
	}
}