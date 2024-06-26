/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_ft_split_w_quotes2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:02:23 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:08:00 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_wrds_mini(char *str, char c)
{
	int		i;
	int		wcnt;
	bool	single_quotes_open;
	bool	double_quotes_open;

	single_quotes_open = false;
	double_quotes_open = false;
	if (!str || str[0] == '\0')
		return (0);
	wcnt = 0;
	if (str[0] != c && str[0] != '\t')
		wcnt++;
	i = -1;
	while (str[++i + 1])
	{
		if (str[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
		if (str[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		if ((str[i] == c || str[i] == '\t') && \
			(str[i + 1] != c && str[i + 1] != '\t') && \
			(single_quotes_open == false && double_quotes_open == false))
			wcnt++;
	}
	return (wcnt);
}
