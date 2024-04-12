/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:53:42 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 17:10:23 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	repl_dsign_h(char **input_str, int dsign, char **new_str, int *i)
{
	if ((*input_str)[dsign + 1] == '\"' || (*input_str)[dsign + 1] == '\'')
	{
		(*new_str) = ft_substr((*input_str), 0, dsign);
		if (!(*new_str))
			return (free((*input_str)), -1);
		(*new_str) = ft_strjoin_w_free((*new_str), (*input_str) + dsign + 1);
		free((*input_str));
		if (!(*new_str))
			return (-1);
		*input_str = (*new_str);
		return (1);
	}
	(*new_str) = ft_substr((*input_str), 0, dsign);
	if (!(*new_str))
		return (free(*input_str), -1);
	*i = dsign + 1;
	while ((*input_str)[*i] && (ft_isalnum((*input_str)[*i]) || \
		(*input_str)[*i] == '_' || (*input_str)[*i] == '?'))
		(*i)++;
	return (0);
}

static int	repl_dsign_h2(char **envvar_value, char *envvar, t_alloc *mllcd,
	char **new_str)
{
	(*envvar_value) = find_envvar_value(envvar, mllcd);
	free(envvar);
	if (!(*envvar_value))
		return (free(*new_str), -1);
	*new_str = ft_strjoin_w_free(*new_str, (*envvar_value));
	if (!new_str)
		return (free((*envvar_value)), -1);
	return (0);
}

static int	replace_dollar_sign(char **input_str, int dsign, t_alloc *mllcd)
{
	char	*new_str;
	char	*envvar;
	char	*envvar_value;
	int		i;
	int		ret;

	i = 0;
	ret = repl_dsign_h(input_str, dsign, &new_str, &i);
	if (ret != 0)
		return (ret);
	envvar = ft_substr((*input_str), dsign + 1, i - dsign - 1);
	if (!envvar || ft_strlen(envvar) == 0)
		return (free(new_str), -1);
	if (repl_dsign_h2(&envvar_value, envvar, mllcd, &new_str))
		return (free(*input_str), -1);
	new_str = ft_strjoin_w_free(new_str, \
		(*input_str) + dsign + 1 + i - dsign - 1);
	free(*input_str);
	if (!new_str)
		return (free(envvar_value), -1);
	*input_str = new_str;
	i = ft_strlen(envvar_value);
	return (free(envvar_value), i);
}

int	expander(char **input_str, t_alloc *mllcd)
{
	int	dsign;
	int	i;
	int	j;

	if (expand_tilde(input_str, mllcd))
		return (1);
	dsign = 0;
	i = 0;
	while (*input_str && dsign != -1 && (*input_str)[i])
	{
		dsign = find_dollar_sign((*input_str), i);
		j = 0;
		if (dsign != -1)
		{
			j = replace_dollar_sign(input_str, dsign, mllcd);
			if (j == -1)
				return (1);
			i += j;
		}
		else
			i++;
	}
	return (0);
}
