/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:18:42 by pgober            #+#    #+#             */
/*   Updated: 2024/02/06 17:38:42 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_remove_quotes(char *str)
{
	int i;
	bool single_quotes_open;
	bool double_quotes_open;
	
	single_quotes_open = false;
	double_quotes_open = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && (!single_quotes_open || double_quotes_open))
		{
			str = ft_strjoin_w_free(ft_substr(str, 0, i), ft_substr(str, i + 1, ft_strlen(str) - i - 1));
			double_quotes_open = !double_quotes_open;
		}
		if (str[i] == '\'' && (!double_quotes_open || single_quotes_open))
		{
			str = ft_strjoin_w_free(ft_substr(str, 0, i), ft_substr(str, i + 1, ft_strlen(str) - i - 1));
			single_quotes_open = !single_quotes_open;
		}
		i++;
	}
	return (str);
}

int	special_operator(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (-1);
}

char	*ft_strjoin_w_free(char *s1, char *s2)
{
	char	*new;
	int		k;
	int		s;

	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	k = 0;
	while (s1[k])
	{
		new[k] = s1[k];
		k++;
	}
    free(s1);
	s = 0;
	while (s2[s])
		new[k++] = s2[s++];
	new[k] = '\0';
	return (new);
}

static int	quotes_check(char *input)
{
	int i;
	bool single_quotes_open;
	bool double_quotes_open;

	single_quotes_open = false;
	double_quotes_open = false;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\"' && single_quotes_open == false)
			double_quotes_open = !double_quotes_open;
		if (input[i] == '\'' && double_quotes_open == false)
			single_quotes_open = !single_quotes_open;
		i++;
	}
	if (single_quotes_open == true || double_quotes_open == true)
		return (ft_putstr_fd("Error: Quotes not closed.\n", 2), 1);	
	return (0);
}

int	input_check_adapt(char *input)
{
	if (quotes_check(input))
		return (1);
	return (0);
}