/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 12:45:50 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

typedef struct s_input_parsing
{
	char	**m_argv;
	int		m_argc;
	int		pipenum;  //have to replace the one in minishell_pipex.h with this one later // If there is just "< infile" in front of the first pipe, then pipenum-- as the first pipe is not needed/counted
	char	***cmd_table;
	bool	doublequote_open;
	bool	singlequote_open;
	char	*input_str;
}	t_input_parsing;

// input parser
int	cmdline_input_parser(t_input_parsing *in_pars, char *input_str);

// ft_split w quotes
typedef struct s_quotes
{
	bool single_quotes_open;
	bool double_quotes_open;
}	t_quotes;

int		count_words(char *str, char c);
char	**ft_split_w_quotes(char const *s, char c, t_input_parsing *in_pars);

//input parser utils
char	*ft_remove_quotes(char *str);
int		special_operator(char *str);
char	*ft_strjoin_w_free(char *s1, char *s2);
int		input_check_adapt(char *input);

// syntax check
int		syntax_checker(char **m_argv, int m_argc);
int		pre_check_input(char *input_str);

#endif
