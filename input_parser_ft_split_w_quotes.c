/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_ft_split_w_quotes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:12:30 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 10:41:05 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str, char c)
{
	int		i;
	int		wcnt;
	bool	single_quotes_open;
	bool	double_quotes_open;

	single_quotes_open = false;
	double_quotes_open = false;
	if (!str)
		return (0);
	wcnt = 0;
	if (str[0] != c)
		wcnt++;
	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
		if (str[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		if (str[i] == c && str[i + 1] != c && (single_quotes_open == false && double_quotes_open == false))
			wcnt++;
		i++;
	}
	return (wcnt);
}

static char	*freeing_choice_word(char **w, t_mystruct *hst)
{
	int	wcnt;

	wcnt = 0;
	if (!(w[hst->wct]))
	{
		while (w[wcnt] != NULL)
			free(w[wcnt++]);
		free(w);
		free(hst);
		return (NULL);
	}
	return ("OK");
}

static char	*freeing_choice_struct(char **w, t_mystruct *hst)
{
	if (!w || !hst)
	{
		free(hst);
		free(w);
		return (NULL);
	}
	return ("OK");
}

static void	quote_checker(char c, t_quotes *quotes, char quote_type) // if quote type == x both will be checked
{
	if ((quote_type == 's' || quote_type == 'x') && c == '\'')
		quotes->single_quotes_open = !quotes->single_quotes_open;
	if ((quote_type == 'd' || quote_type == 'x') && c == '\"')
		quotes->double_quotes_open = !quotes->double_quotes_open;
}

char	**ft_split_w_quotes(char const *s, char c)
{
	char		**words;
	t_mystruct	*hst;
	t_quotes	quotes; // single, double quotes open

	quotes.single_quotes_open = false;
	quotes.double_quotes_open = false;
	hst = (t_mystruct *)malloc(sizeof(t_mystruct));
	words = (char **)malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (freeing_choice_struct(words, hst) == NULL)
		return (NULL);
	hst->j = 0;
	hst->wct = 0;
	while (hst->wct < count_words((char *)s, c))
	{
		while (s[hst->j] == c && s[hst->j] != '\0') // jump over c ->should not be quotes
			hst->j++;
		hst->k = hst->j; // fix this spot
		quote_checker(s[hst->j++], &quotes, 'x');
		while (s[hst->j] != '\0' && (s[hst->j] != c || (s[hst->j] == c && (quotes.single_quotes_open || quotes.double_quotes_open))))
		{
			quote_checker(s[hst->j], &quotes, 'x');
			if (s[hst->j] == c && !quotes.single_quotes_open && !quotes.double_quotes_open)
				break ;
			hst->j++;
		}
		words[hst->wct] = (char *)malloc((hst->j - hst->k + 1) * sizeof(char));
		if (freeing_choice_word(words, hst) == NULL)
			return (NULL);
		ft_strlcpy(words[hst->wct], &s[hst->k], hst->j - hst->k + 1);
		words[hst->wct++][hst->j - hst->k] = '\0';
	}
	words[hst->wct] = NULL;
	free(hst);
	return (words);
}

//cc -Wall -Wextra -Werror -g input_parser_ft_split_w_quotes.c expander.c input_parser_utils.c get_env.c libft/*.c
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./a.out
// int	main(int argc, char **argv, char **envv)
// {
//     char	*input_str;
//     int	wcnt;
//     char	**words;
// 	char	c = ' ';
// 	t_alloc mllcd;

// 	if (!argc || !argv)
// 		return (1);
// 	input_str = ft_strdup("echo \'$SHELL\'$PWD"); //fill in stuff from EXTRA/input_parser_testing
//     mllcd.env_list = (t_env *)malloc(sizeof(t_env));
//     get_env(envv, &mllcd.env_list);
// 	if (expander(&input_str, &mllcd))
//         return (1);
//     if (!input_str || ft_strlen(input_str) == 0 || input_check_adapt(input_str))
// 		return (ft_putstr_fd("Error: Input is invalid.\n", 2), 1);
//     words = ft_split_w_quotes(input_str, c);
//     wcnt = 0;
// 	printf("%d words:\n", count_words(input_str, c));
//     while (wcnt < count_words(input_str, c))
// 	{
// 		printf("%s\n", words[wcnt]);
//         free(words[wcnt++]);
// 	}
// 	free(words);
// 	free(input_str);
// 	ft_lstclear(&mllcd.env_list);
//     return (0);
// }