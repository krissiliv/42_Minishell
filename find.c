/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:00:01 by pgober            #+#    #+#             */
/*   Updated: 2024/04/17 12:04:21 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char *str, int i, bool *single_quotes_open, \
	bool *double_quotes_open)
{
	if (str[i] == '\'' && !(*double_quotes_open))
		(*single_quotes_open) = !(*single_quotes_open);
	else if (str[i] == '\"' && !(*single_quotes_open))
		(*double_quotes_open) = !(*double_quotes_open);
}

int	find_dollar_sign(char *str, int starting_pt)
{
	int		i;
	bool	single_quotes_open;
	bool	double_quotes_open;

	i = -1;
	single_quotes_open = false;
	double_quotes_open = false;
	while (++i < starting_pt)
	{
		if (str[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		else if (str[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
	}
	i = starting_pt - 1;
	while (str[++i])
	{
		check_quotes(str, i, &single_quotes_open, &double_quotes_open);
		if (single_quotes_open == false && str[i + 1] && str[i] == '$'
			&& (ft_isalpha(str[i + 1]) != 0 || str[i + 1] == '?' || \
				(str[i + 1] == '\"' && double_quotes_open == false) || \
			str[i + 1] == '\''))
			return (i);
	}
	return (-1);
}

char	*find_envvar_value(char *envvar, t_alloc *mllcd)
{
	t_env	*pos;
	int		len;
	char	*envvar_w_equalsign;
	char	*return_value;

	if (!envvar || ft_strlen(envvar) == 0)
		return (NULL);
	if (ft_strcmp(envvar, "?") == 0)
	{
		return_value = ft_itoa(mllcd->exit_status);
		if (!return_value)
			return (NULL);
		return (return_value);
	}
	pos = mllcd->env_list;
	envvar_w_equalsign = ft_strjoin(envvar, "=");
	if (!envvar_w_equalsign)
		return (NULL);
	len = ft_strlen(envvar_w_equalsign);
	while (pos != NULL && ft_strncmp(pos->env_var, envvar_w_equalsign, len))
		pos = pos->next;
	if (pos != NULL && ft_strncmp(pos->env_var, envvar_w_equalsign, len) == 0)
		return (free(envvar_w_equalsign), ft_strdup(pos->env_var + len));
	return (free(envvar_w_equalsign), ft_strdup(""));
}
