/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_ft_split_w_quotes.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:12:30 by pgober            #+#    #+#             */
/*   Updated: 2024/04/12 22:04:10 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	quote_checker(char c, t_quotes *quotes, char quote_type)
{
	if ((quote_type == 's' || quote_type == 'x') && c == '\'')
		quotes->single_quotes_open = !quotes->single_quotes_open;
	if ((quote_type == 'd' || quote_type == 'x') && c == '\"')
		quotes->double_quotes_open = !quotes->double_quotes_open;
}

static void	split_helper(char const **s, char c, t_mystruct **hst, \
	t_quotes quotes)
{
	while (((*s)[(*hst)->j] == '\t' || (*s)[(*hst)->j] == c) && \
		(*s)[(*hst)->j] != '\0')
		(*hst)->j++;
	(*hst)->k = (*hst)->j;
	quote_checker((*s)[(*hst)->j++], &quotes, 'x');
	while ((*s)[(*hst)->j] != '\0' && ((*s)[(*hst)->j] != c || \
		(((*s)[(*hst)->j] == '\t' || (*s)[(*hst)->j] == c) && \
			(quotes.single_quotes_open || \
			quotes.double_quotes_open))))
	{
		quote_checker((*s)[(*hst)->j], &quotes, 'x');
		if (((*s)[(*hst)->j] == '\t' || (*s)[(*hst)->j] == c) && \
			!quotes.single_quotes_open && \
			!quotes.double_quotes_open)
			break ;
		(*hst)->j++;
	}
}

char	**ft_split_w_quotes(char const *s, char c, t_input_parsing *in_pars)
{
	char		**words;
	t_mystruct	*hst;
	t_quotes	quotes;

	quotes.single_quotes_open = false;
	quotes.double_quotes_open = false;
	hst = (t_mystruct *)malloc(sizeof(t_mystruct));
	if (!hst)
		return (free_cmd_table(in_pars), NULL);
	words = (char **)malloc((cnt_wrds_mini((char *)s, c) + 1) * sizeof(char *));
	if (freeing_choice_struct(words, hst) == NULL)
		return (free_cmd_table(in_pars), NULL);
	hst->j = 0;
	hst->wct = 0;
	while (hst->wct < cnt_wrds_mini((char *)s, c))
	{
		split_helper(&s, c, &hst, quotes);
		words[hst->wct] = (char *)malloc((hst->j - hst->k + 1) * sizeof(char));
		if (freeing_choice_word(words, hst) == NULL)
			return (free_cmd_table(in_pars), NULL);
		ft_strlcpy(words[hst->wct], &s[hst->k], hst->j - hst->k + 1);
		words[hst->wct++][hst->j - hst->k] = '\0';
	}
	words[hst->wct] = NULL;
	return (free(hst), words);
}
