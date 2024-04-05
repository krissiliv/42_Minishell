/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:47 by pgober            #+#    #+#             */
/*   Updated: 2024/04/05 19:24:32 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PARSER_H
# define INPUT_PARSER_H

typedef struct s_input_parsing
{
	char	**m_argv;
	int		m_argc;
	int		pipenum;
	char	***cmd_table;
	bool	doublequote_open;
	bool	singlequote_open;
	char	*input_str;
}	t_input_parsing;

// input parser 2
int		init_input_parser(t_input_parsing *in_pars, char *input_str);
int		look_for_free_spot_in_cmdtable(t_input_parsing *in_pars, \
	int curr_cmdnum, int i);

// input parser 3
int		remove_quotes_from_cmd_table(t_input_parsing *in_pars);
int		processing_read_heredocs(t_input_parsing *in_pars, int *i, \
		int curr_cmdnum);

// ft_split w quotes
typedef struct s_quotes
{
	bool	single_quotes_open;
	bool	double_quotes_open;
}	t_quotes;

int		count_words(char *str, char c);
char	**ft_split_w_quotes(char const *s, char c, t_input_parsing *in_pars);

//input parser utils
char	*ft_remove_quotes(char *str);
int		special_operator(char *str);
char	*ft_strjoin_w_free(char *s1, char *s2);
int		quotes_check(char *input);

// syntax check
int		syntax_checker(char **m_argv, int m_argc);
int		pre_check_input(char *input_str);

#endif
