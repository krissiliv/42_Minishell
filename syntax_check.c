/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:58:53 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:11:19 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*syntax_check_message(int m)
{
	if (m == 1)
		return ("minishell: syntax error near unexpected token.\n");
	return (NULL);
}

int	syntax_checker(char **m_argv, int m_argc)
{
	int	i;

	i = 0;
	while (i < m_argc)
	{
		if ((ft_strcmp(m_argv[i], "<") == 0) && \
			(!m_argv[++i] || special_operator(m_argv[i]) != -1))
			return (ft_putstr_fd(syntax_check_message(1), 2), 2);
		else if (ft_strcmp(m_argv[i], ">") == 0 && (!m_argv[++i] || \
			special_operator(m_argv[i]) != -1))
			return (ft_putstr_fd(syntax_check_message(1), 2), 2);
		else if (ft_strncmp(m_argv[i], "<<", 2) == 0 && \
			ft_strlen(m_argv[i]) == 2 && (!m_argv[++i] || \
				special_operator(m_argv[i]) != -1))
			return (ft_putstr_fd(syntax_check_message(1), 2), 2);
		else if (ft_strcmp(m_argv[i], ">>") == 0 && (!m_argv[++i] || \
			special_operator(m_argv[i]) != -1))
			return (ft_putstr_fd(syntax_check_message(1), 2), 2);
		else if (ft_strcmp(m_argv[i], "|") == 0 && (!m_argv[i + 1] \
			|| i == 0))
			return (ft_putstr_fd(syntax_check_message(1), 2), 2);
		i++;
	}
	return (0);
}

int	pre_check_input(char *input_str)
{
	int		i;
	bool	check_only_spaces_ops;

	if (!input_str || ft_strlen(input_str) == 0)
	{
		if (!input_str)
			printf("\n");
		return (1);
	}
	i = 0;
	check_only_spaces_ops = true;
	while (input_str[i])
	{
		if (!is_space(input_str[i++]) || special_operator(input_str + i) == -1)
			check_only_spaces_ops = false;
	}
	if (check_only_spaces_ops)
		return (1);
	return (0);
}
