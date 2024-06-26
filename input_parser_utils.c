/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:18:42 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:08:06 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove_quotes_common(char *str, int i)
{
	char	*new;
	char	*tmp;

	tmp = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (!tmp)
		return (free(str), NULL);
	new = ft_strjoin_w_free(ft_substr(str, 0, i), tmp);
	free(str);
	free(tmp);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	bool	single_quotes_open;
	bool	double_quotes_open;

	single_quotes_open = false;
	double_quotes_open = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && (!single_quotes_open || double_quotes_open))
		{
			str = ft_remove_quotes_common(str, i);
			double_quotes_open = !double_quotes_open;
		}
		else if (str[i] == '\'' && (!double_quotes_open || single_quotes_open))
		{
			str = ft_remove_quotes_common(str, i);
			single_quotes_open = !single_quotes_open;
		}
		else
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

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (free(s1), NULL);
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

int	quotes_check(char *input)
{
	int		i;
	bool	single_quotes_open;
	bool	double_quotes_open;

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
