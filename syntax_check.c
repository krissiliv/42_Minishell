/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:24:51 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 14:09:58 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int syntax_checker(char **m_argv, int m_argc) // syntax errror is always bash(2)
{
	int i;

	i = 0;
	while (i < m_argc)
	{
        if ((ft_strcmp(m_argv[i], "<") == 0) && (!m_argv[++i] || special_operator(m_argv[i]) != -1))
            return (ft_putstr_fd("minishell: syntax error near unexpected token.\n", 2), 2);
		else if (ft_strcmp(m_argv[i], ">") == 0 && (!m_argv[++i] || special_operator(m_argv[i]) != -1))
            return (ft_putstr_fd("minishell: syntax error near unexpected token.\n", 2), 2);
		else if (ft_strncmp(m_argv[i], "<<", 2) == 0 && ft_strlen(m_argv[i]) == 2 && (!m_argv[++i] || special_operator(m_argv[i]) != -1)) // next one should be a file
				return (ft_putstr_fd("minishell: syntax error near unexpected token.\n", 2), 2);
		else if (ft_strcmp(m_argv[i], ">>") == 0 && (!m_argv[++i] || special_operator(m_argv[i]) != -1))
            return (ft_putstr_fd("minishell: syntax error near unexpected token.\n", 2), 2);
        else if (ft_strcmp(m_argv[i], "|") == 0 && (!m_argv[i + 1] || i == 0))
            return (ft_putstr_fd("minishell: syntax error near unexpected token.\n", 2), 2);
		i++;
	}
	return (0);  // next step: 
}


int  pre_check_input(char *input_str)
{
	int i;
	int check_only_spaces;

	// printf("input_str: %s has length %zu\n", input_str, ft_strlen(input_str));
	if (!input_str || ft_strlen(input_str) == 0)
	{
		printf("\n");
		return (1);
	}
	i = 0;
	check_only_spaces = 1;
	while (input_str[i])
	{
		if (!is_space(input_str[i++]))
			check_only_spaces = 0;
	}
	if (check_only_spaces)
		return (1);
	return (0);
}