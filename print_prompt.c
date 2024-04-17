/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:07:06 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:10:55 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input_print_prompt(t_env **env_list)
{
	char	*line;

	signals(1);
	line = readline("~/minishell> ");
	if (!line)
	{
		ft_lstclear(env_list);
		rl_clear_history();
		return (NULL);
	}
	signals(2);
	add_history(line);
	return (line);
}
