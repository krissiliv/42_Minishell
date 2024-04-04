/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_minishell2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:05:34 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 13:17:57 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_sp_bef_sp_op_helper(char *temp[2], char **input_str, int i)
{
	temp[0] = ft_substr((*input_str), i, ft_strlen((*input_str)) - i);
	if (!temp[0])
		return (free(*input_str), -1);
	temp[1] = ft_substr((*input_str), 0, i);
	free(*input_str);
	if (!temp[1])
		return (free(temp[0]), -1);
	(*input_str) = ft_strjoin_w_free(ft_strjoin_w_free(temp[1], " "), temp[0]);
	free(temp[0]);
	if (!(*input_str))
		return (-1);
	return (0);
}

static int	put_sp_bef_sp_op_helper2(char *temp[2], char **input_str, int i)
{
	temp[0] = ft_substr((*input_str), i + 1, ft_strlen((*input_str)) - i - 1);
	if (!temp[0])
		return (free(*input_str), -1);
	temp[1] = ft_substr((*input_str), 0, i + 1);
	free(*input_str);
	if (!temp[1])
		return (free(temp[0]), -1);
	(*input_str) = ft_strjoin_w_free(ft_strjoin_w_free(temp[1], " "), temp[0]);
	free(temp[0]);
	if (!(*input_str))
		return (-1);
	return (0);
}

static int	psp_b_sp_op_helper3(char *temp[2], char **input_str, int *i, int k)
{
	if (*i > 0 && !is_space((*input_str)[*i - 1]) && \
		put_sp_bef_sp_op_helper(temp, input_str, *i) == -1)
		return (-1);
	*i += k - 1;
	if ((*input_str)[*i + 1] && !is_space((*input_str)[*i + 1]) && \
		put_sp_bef_sp_op_helper2(temp, input_str, *i) == -1)
		return (-1);
	return (*i);
}

int	put_space_before_special_operator(char **input_str)
{
	int		i;
	int		k;
	bool	single_quotes_open;
	bool	double_quotes_open;
	char	*temp[2];

	i = -1;
	k = 0;
	single_quotes_open = false;
	double_quotes_open = false;
	while ((*input_str)[++i])
	{
		if ((*input_str)[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		if ((*input_str)[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
		k = special_operator((*input_str) + i);
		if (k != -1 && !single_quotes_open && !double_quotes_open)
		{
			if (psp_b_sp_op_helper3(temp, input_str, &i, k) == -1)
				return (-1);
			k = 0;
		}
	}
	return (0);
}
