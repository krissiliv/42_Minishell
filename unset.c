/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:02:57 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/17 19:06:43 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_env **env_list, char *input, t_alloc *mllcd)
{
	t_env	*head;
	t_env	*temp;

	head = *env_list;
	while (head && ft_strncmp(input, head->env_var, ft_strlen(input)))
	{
		temp = head;
		head = head->next;
	}
	if (head == NULL)
	{
		ft_putstr_fd("No variable was found\n", 2);
		mllcd->exit_status = 1;
		return (1);
	}
	else
	{
		temp->next = head->next;
		free(head);
		mllcd->exit_status = 0;
		return (0);
	}
}