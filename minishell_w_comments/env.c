/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:22:39 by apashkov          #+#    #+#             */
/*   Updated: 2024/02/08 12:09:26 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prntlist(t_env *head)
{
    t_env *pos;

    pos = head;
	if (pos == NULL)
		printf("NULL\n");
    while (pos != NULL)
    {
        printf("%s\n", pos->env_var);
        pos = pos->next;
    }
}

int	env(char **cmd, t_alloc mllcd)
{
	if (cmd[1])
		return (ft_putstr_fd("env: No such file or directory\n", 2), 127);
	else
		prntlist(mllcd.env_list);
	return (0);
}