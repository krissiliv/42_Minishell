/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:12:30 by pgober            #+#    #+#             */
/*   Updated: 2024/01/03 15:29:10 by pgober           ###   ########.fr       */
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
	bool		word_found;

	quotes.single_quotes_open = false;
	quotes.double_quotes_open = false;
	word_found = false;
	hst = (t_mystruct *)malloc(sizeof(t_mystruct));
	words = (char **)malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (freeing_choice_struct(words, hst) == NULL)
		return (NULL);
	hst->j = 0;
	hst->wct = 0;
	while (hst->wct < count_words((char *)s, c))
	{
		word_found = false;
		while (s[hst->j] == c && s[hst->j] != '\0') // jump over c ->should not be quotes
			hst->j++;
		hst->k = hst->j; // fix this spot
		quote_checker(s[hst->j++], &quotes, 'x');
		while (s[hst->j] != c && s[hst->j] != '\0' && (quotes.single_quotes_open == false && quotes.double_quotes_open == false))
			quote_checker(s[hst->j++], &quotes, 'x'); //check for any quote findin
		if (hst->k != hst->j && (quotes.single_quotes_open == false && quotes.double_quotes_open == false))
			word_found = true;
		while (word_found == false && quotes.single_quotes_open == true && quotes.double_quotes_open == false)
			quote_checker(s[hst->j++], &quotes, 's'); //check for new single quote finding
		if (hst->k != hst->j && (quotes.single_quotes_open == false && quotes.double_quotes_open == false))
			word_found = true;
		while (word_found == false && quotes.single_quotes_open == false && quotes.double_quotes_open == true)
			quote_checker(s[hst->j++], &quotes, 'd'); //check for new double finding
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

//cc -Wall -Wextra -Werror -g input_parser_ft_split_w_quotes.c libft/ft_strlen.c libft/ft_strlcpy.c
// int	main(void)
// {
//     char	*str = " \"< infile\" \"cat\"";
//     int	wcnt;
//     char	**words;
// 	char	c = ' ';

//     words = ft_split_w_quotes(str, c);
//     wcnt = 0;
// 	printf("%d words:\n", count_words(str, c));
//     while (wcnt < count_words(str, c))
// 	{
// 		printf("%s\n", words[wcnt]);
//         free(words[wcnt++]);
// 	}
// 	free(words);
//     return (0);
// }
