/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:05:03 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 21:03:47 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	processing_read_helper(t_input_parsing *in_pars, int *i, int pos, \
	int curr_cmdnum)
{
	int	outfile;

	outfile = -1;
	if (in_pars->cmd_table[curr_cmdnum][pos])
	{
		if (pos == 2 || pos == 4)
		{
			outfile = open(in_pars->cmd_table[curr_cmdnum][pos], \
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (outfile == -1)
				return (0);
		}
		if (pos == 1)
		{
			if (prr_helper_mini(in_pars->cmd_table[curr_cmdnum][pos], \
				outfile, i) != -1)
				return (0);
		}
		close(outfile);
		free(in_pars->cmd_table[curr_cmdnum][pos]);
	}
	in_pars->cmd_table[curr_cmdnum][pos] = ft_strdup(in_pars->m_argv[++(*i)]);
	if (!in_pars->cmd_table[curr_cmdnum][pos])
		return (1);
	return (0);
}

static int	processing_read2(t_input_parsing *in_pars, int *i, int curr_cmdnum)
{
	if (*i != -2 && ft_strcmp(in_pars->m_argv[*i], "<") == 0)
	{
		if (processing_read_helper(in_pars, i, 1, curr_cmdnum))
			return (1);
	}
	else if (*i != -2 && ft_strcmp(in_pars->m_argv[*i], ">") == 0)
	{
		if (processing_read_helper(in_pars, i, 2, curr_cmdnum))
			return (1);
	}
	else if (*i != -2 && ft_strncmp(in_pars->m_argv[*i], "<<", 2) == 0)
	{
		if (processing_read_heredocs(in_pars, i, curr_cmdnum))
			return (1);
	}
	else if (*i != -2 && ft_strcmp(in_pars->m_argv[*i], ">>") == 0)
	{
		if (processing_read_helper(in_pars, i, 4, curr_cmdnum))
			return (1);
	}
	if (*i == -2)
		return (0);
	return (0);
}

static int	processing_read3(t_input_parsing *in_pars, int *i, int *curr_cmdnum)
{
	if (ft_strcmp(in_pars->m_argv[*i], "|") == 0 && \
		in_pars->m_argv[*i + 1])
	{
		if (in_pars->cmd_table[*curr_cmdnum][0] == 0)
			curr_cmdnum--;
	}
	else if (in_pars->m_argv[*i] != NULL)
	{
		*i = look_for_free_spot_in_cmdtable(in_pars, *curr_cmdnum, *i);
		if (*i == -1)
			return (1);
	}
	if (in_pars->m_argv[*i] && ft_strcmp(in_pars->m_argv[*i], "|") == 0)
		(*curr_cmdnum)++;
	return (0);
}

static int	processing_read(t_input_parsing *in_pars)
{
	int		i;
	int		curr_cmdnum;

	i = -1;
	curr_cmdnum = 0;
	while (++i < in_pars->m_argc)
	{
		if (i != -2 && (ft_strcmp(in_pars->m_argv[i], "<") == 0 || \
			ft_strcmp(in_pars->m_argv[i], ">") == 0 || \
			ft_strncmp(in_pars->m_argv[i], "<<", 2) == 0 || \
			ft_strcmp(in_pars->m_argv[i], ">>") == 0))
		{
			if (processing_read2(in_pars, &i, curr_cmdnum))
				return (1);
		}
		else if (i != -2 && ((ft_strcmp(in_pars->m_argv[i], "|") == 0 && \
			in_pars->m_argv[i + 1]) || in_pars->m_argv[i]))
		{
			if (processing_read3(in_pars, &i, &curr_cmdnum))
				return (1);
		}
		if (i == -2)
			return (-2);
	}
	return (0);
}

int	cmdline_input_parser(t_input_parsing *in_pars, char *input_str, \
	t_alloc *mllcd)
{
	int	exit_status;

	if (!input_str || ft_strlen(input_str) == 0)
		return (ft_putstr_fd("Error: \
			Input parser did not receive input.\n", 2), 1);
	in_pars->input_str = input_str;
	if (init_input_parser(in_pars, input_str))
		return (-1);
	in_pars->m_argc = cnt_wrds_mini(input_str, ' ');
	in_pars->m_argv = ft_split_w_quotes(input_str, ' ', in_pars);
	if (in_pars->m_argv == NULL)
		return (-1);
	exit_status = syntax_checker(in_pars->m_argv, in_pars->m_argc);
	if (exit_status != 0)
		return (exit_status);
	exit_status = processing_read(in_pars);
	if (exit_status == 1)
		return (1);
	else if (exit_status == -2)
		return (-2);
	if (remove_quotes_from_cmd_table(in_pars))
		return (1);
	if (adapt_cmd_tble_to_heredocs(in_pars, mllcd) == 1)
		return (1);
	return (0);
}
