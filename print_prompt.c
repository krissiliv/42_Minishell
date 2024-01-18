/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:07:06 by pgober            #+#    #+#             */
/*   Updated: 2024/01/03 15:48:56 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_input_print_prompt(void) 
{
    char    *line;
    
    ft_putstr_fd("~/minishell> ", 1);
    line = readline(NULL);
    add_history(line);
    return (line);
}

/*
Normally, a prompt is printed to stderr rather than stdout. 
This has the advantage, that the prompt appears before a newline is written, 
as stderr is unbuffered (and in combination with piping and redirection
it seems reasonable that this stuff doesn’t go to the same stream as the actual output).


*/