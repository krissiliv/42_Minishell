/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:02:57 by apashkov          #+#    #+#             */
/*   Updated: 2024/04/03 17:14:30 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_one(t_env **env_list, char *input, t_alloc *mllcd)
{
	t_env	*head;
	t_env	*temp;

	head = *env_list;
	while (head && ft_strncmp(input, head->env_var, ft_strlen(input)))
	{
		temp = head;
		head = head->next;
	}
	if (head)
	{
		if (!ft_strncmp(input, (*env_list)->env_var, ft_strlen(input)))
		{
			temp = head->next;
			*env_list = temp;
		}
		else
			temp->next = head->next;
		if (head->malloced == true)
			free(head->env_var);
		free(head);
		mllcd->exit_status = 0;
	}
	return (0);
}

int	unset(char **cmd, t_alloc *mllcd)
{
	int	i;

	i = 0;
	if (!cmd[1])
	{
		mllcd->exit_status = 0;
		return (0);
	}
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("unset: ", 2);
		ft_putchar_fd(cmd[1][0], 2);
		ft_putchar_fd(cmd[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		mllcd->exit_status = 2;
		return (2);
	}
	while (cmd[++i])
		unset_one(&mllcd->env_list, cmd[i], mllcd);
	return (0);
}
