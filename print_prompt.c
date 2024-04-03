/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:07:06 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 13:38:37 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input_print_prompt(t_env **env_list)
{
    char    *line;
    
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

/*
Normally, a prompt is printed to stderr rather than stdout. 
This has the advantage, that the prompt appears before a newline is written, 
as stderr is unbuffered (and in combination with piping and redirection
it seems reasonable that this stuff doesn’t go to the same stream as the actual output).


*/