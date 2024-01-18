/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:22:39 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 17:22:15 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void prntlist(t_env *head)
{
    t_env *pos;

    pos = head;
    while (pos != NULL)
    {
        printf("%s\n", pos->env_var);
        pos = pos->next;
    }
}

int	env(t_alloc *mllcd)
{
	prntlist(&mllcd->env_list);
	mllcd->exit_status = 0;
	return (0);
}