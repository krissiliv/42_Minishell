/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:05:03 by pgober            #+#    #+#             */
/*   Updated: 2024/04/04 11:09:12 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_input_parser_helper(char *input_str, bool *singlequote_open, \
	bool *doublequote_open, t_input_parsing *in_pars)
{
	while (*input_str)
	{
		if (*input_str == '\"' && *singlequote_open == false)
			*doublequote_open = !(*doublequote_open);
		if (*input_str == '\'' && *doublequote_open == false)
			*singlequote_open = !(*singlequote_open);
		if (*input_str == '|' && *singlequote_open == false && \
			*doublequote_open == false)
			in_pars->pipenum++;
		input_str++;
	}
	in_pars->m_argc = 0;
	in_pars->m_argv = NULL;
	in_pars->cmd_table = \
		(char ***)malloc((in_pars->pipenum + 1) * 5 * sizeof(char *));
	if (in_pars->cmd_table == NULL)
		return (1);
	in_pars->doublequote_open = false;
	in_pars->singlequote_open = false;
	return (0);
}

int	init_input_parser(t_input_parsing *in_pars, char *input_str)
{
	int		i;
	int		j;
	bool	singlequote_open;
	bool	doublequote_open;

	singlequote_open = false;
	doublequote_open = false;
	in_pars->pipenum = 0;
	if (init_input_parser_helper(input_str, &singlequote_open, \
		&doublequote_open, in_pars))
		return (1);
	i = -1;
	while (++i <= in_pars->pipenum)
	{
		in_pars->cmd_table[i] = (char **)malloc(5 * sizeof(char *));
		if (in_pars->cmd_table[i] == NULL)
			return (1);
		j = 0;
		while (j <= 4)
			in_pars->cmd_table[i][j++] = NULL;
	}
	in_pars->cmd_table[i] = NULL;
	return (0);
}

static int	lk_fr_fr_sp_in_cmdtbl_helper1(t_input_parsing *in_pars, \
	int curr_cmdnum, int *i)
{
	char	*temp;

	in_pars->cmd_table[curr_cmdnum][0] = ft_strdup(in_pars->m_argv[*i]);
	if (!in_pars->cmd_table[curr_cmdnum][0])
		return (free_strstr(in_pars->m_argv), free_cmd_table(in_pars), -1);
	if (in_pars->m_argv[*i + 1] && in_pars->m_argv[*i + 1][0] == '-' && \
		ft_strlen(in_pars->m_argv[*i]) > 1)
	{
		temp = ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], " ");
		if (!temp)
			return (-1);
		in_pars->cmd_table[curr_cmdnum][0] = \
			ft_strjoin_w_free(temp, in_pars->m_argv[++(*i)]);
		if (!in_pars->cmd_table[curr_cmdnum][0])
			return (-1);
	}
	return (0);
}

static int	lk_fr_fr_sp_in_cmdtbl_helper2(t_input_parsing *in_pars, \
	int curr_cmdnum, int *i)
{
	char	*temp;

	while (in_pars->m_argv[*i] && special_operator(in_pars->m_argv[*i]) == -1)
	{
		temp = ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], " ");
		if (!temp)
			return (-1);
		in_pars->cmd_table[curr_cmdnum][0] = \
			ft_strjoin_w_free(temp, in_pars->m_argv[(*i)++]);
		if (!in_pars->cmd_table[curr_cmdnum][0])
			return (-1);
	}
	(*i)--;
	return (0);
}

int	look_for_free_spot_in_cmdtable(t_input_parsing *in_pars, int curr_cmdnum, \
	int i)
{
	if (in_pars->cmd_table[curr_cmdnum][0] == NULL)
	{
		if (lk_fr_fr_sp_in_cmdtbl_helper1(in_pars, curr_cmdnum, &i) == -1)
			return (-1);
	}
	else if (in_pars->m_argv[i] && special_operator(in_pars->m_argv[i]) == -1)
	{
		if (lk_fr_fr_sp_in_cmdtbl_helper2(in_pars, curr_cmdnum, &i) == -1)
			return (-1);
	}
	else if (in_pars->cmd_table[curr_cmdnum][1] == NULL)
	{
		in_pars->cmd_table[curr_cmdnum][1] = ft_strdup(in_pars->m_argv[i]);
		if (!in_pars->cmd_table[curr_cmdnum][1])
			return (-1);
	}
	else if (in_pars->cmd_table[curr_cmdnum][2] == NULL)
	{
		in_pars->cmd_table[curr_cmdnum][1] = ft_strdup(in_pars->m_argv[i]);
		if (!in_pars->cmd_table[curr_cmdnum][1])
			return (-1);
	}
	else
		return (ft_putstr_fd("Error: too many arguments\n", 2), -1);
	return (i);
}
