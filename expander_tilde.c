/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:08:56 by pgober            #+#    #+#             */
/*   Updated: 2024/04/08 15:24:42 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_tilde_helper(char **input_str, int i, t_alloc *mllcd, int k)
{
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*tmp5;

	tmp2 = ft_substr((*input_str), i + k, ft_strlen((*input_str)) - i - k);
	if (!tmp2)
		return (free(*input_str), 1);
	tmp3 = find_envvar_value("PWD", mllcd);
	if (!tmp3)
		return (free(*input_str), free(tmp2), 1);
	tmp4 = ft_substr((*input_str), 0, i);
	free(*input_str);
	if (!tmp4)
		return (free(tmp2), free(tmp3), 1);
	tmp5 = ft_strjoin_w_free(tmp4, tmp3);
	if (!tmp5)
		return (free(tmp2), free(tmp3), 1);
	*input_str = ft_strjoin_w_free(tmp5, tmp2);
	if (!(*input_str))
		return (free(tmp2), free(tmp3), 1);
	return (free(tmp2), free(tmp3), 0);
}

static int	exp_tilde_helper2(char **input_str, int i, t_alloc *mllcd, \
	char *tmp)
{
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*tmp5;

	tmp2 = ft_substr((*input_str), i + 1 + ft_strlen(tmp), \
		ft_strlen((*input_str)) - i - 1 - ft_strlen(tmp));
	if (!tmp2)
		return (free(*input_str), free(tmp), 1);
	tmp3 = find_envvar_value("HOME", mllcd);
	if (!tmp3)
		return (free(*input_str), free(tmp), free(tmp2), 1);
	tmp4 = ft_substr((*input_str), 0, i);
	free(*input_str);
	if (!tmp4)
		return (free(tmp), free(tmp2), free(tmp3), 1);
	tmp5 = ft_strjoin_w_free(tmp4, tmp3);
	if (!tmp5)
		return (free(tmp), free(tmp2), free(tmp3), 1);
	*input_str = ft_strjoin_w_free(tmp5, tmp2);
	if (!(*input_str))
		return (free(tmp), free(tmp2), free(tmp3), 1);
	i += ft_strlen(tmp3);
	return (free(tmp2), free(tmp3), free(tmp5), 0);
}

static int	exand_tilde_helper3(char **input_str, int i, t_alloc *mllcd)
{
	char	*tmp;

	tmp = find_envvar_value("USER", mllcd);
	if ((*input_str)[i + 1] == '\0' || \
		is_space((*input_str)[i + 1]) || (*input_str)[i + 1] == '/')
	{
		if (exp_tilde_helper(input_str, i, mllcd, 1))
			return (free(tmp), 1);
	}
	else if (((*input_str)[i + 1] == '+' || (*input_str)[i + 1] == '-'))
	{
		if (exp_tilde_helper(input_str, i, mllcd, 2))
			return (free(tmp), 1);
	}
	else if (ft_strncmp((*input_str) + i + 1, tmp, \
		ft_strlen(tmp) - 1) == 0)
	{
		if (exp_tilde_helper2(input_str, i, mllcd, tmp))
			return (free(tmp), 1);
	}
	return (free(tmp), 0);
}

int	expand_tilde(char **input_str, t_alloc *mllcd)
{
	int		i;
	bool	single_quotes_open;
	bool	double_quotes_open;

	single_quotes_open = false;
	double_quotes_open = false;
	i = 0;
	while ((*input_str)[i])
	{
		if ((*input_str)[i] == '~' && \
			!single_quotes_open && !double_quotes_open)
		{
			if (exand_tilde_helper3(input_str, i, mllcd))
				return (1);
		}
		i++;
	}
	return (0);
}
