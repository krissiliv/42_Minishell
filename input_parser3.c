/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:05:03 by pgober            #+#    #+#             */
/*   Updated: 2024/04/04 11:09:12 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes_from_cmd_table(t_input_parsing *in_pars)
{
	int	i;
	int	j;

	i = 0;
	while (i <= in_pars->pipenum)
	{
		j = 1;
		while (j <= 4)
		{
			if (in_pars->cmd_table[i][j])
			{
				in_pars->cmd_table[i][j] = \
					ft_remove_quotes(in_pars->cmd_table[i][j]);
				if (!in_pars->cmd_table[i][j])
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	processing_read_heredocs(t_input_parsing *in_pars, int *i, \
	int curr_cmdnum)
{
	char	*temp;

	if (ft_strlen(in_pars->m_argv[*i]) == 2)
	{
		in_pars->cmd_table[curr_cmdnum][3] = ft_strdup(in_pars->m_argv[++(*i)]);
		if (!in_pars->cmd_table[curr_cmdnum][3])
			return (1);
	}
	else
	{
		temp = ft_strdup(in_pars->m_argv[(*i)++] + 2);
		if (!temp)
			return (1);
		in_pars->cmd_table[curr_cmdnum][3] = ft_strtrim(temp, "\"\'");
		free(temp);
		if (!in_pars->cmd_table[curr_cmdnum][3])
			return (1);
	}
	return (0);
}