/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:12:30 by pgober            #+#    #+#             */
/*   Updated: 2023/09/13 11:59:02 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	wcnt;

	wcnt = 1;
	if (str[0] == c)
		wcnt = 0;
	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i - 1] != c && str[i] == c)
			wcnt++;
		i++;
	}
	if (str[i - 1] == c)
		wcnt--;
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

char	**ft_split(char const *s, char c)
{
	char				**words;
	t_mystruct			*hst;

	hst = (t_mystruct *)malloc(sizeof(t_mystruct));
	words = (char **)malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (freeing_choice_struct(words, hst) == NULL)
		return (NULL);
	hst->j = 0;
	hst->wct = 0;
	while (hst->wct < count_words((char *)s, c))
	{
		while (s[hst->j] == c && s[hst->j] != '\0')
			hst->j++;
		hst->k = hst->j;
		while (s[hst->j] != c && s[hst->j] != '\0')
			hst->j++;
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

/*int	main(void)
{
    char	*str = "  hello wordl helllow";
    int	wcnt;
    char	**words;
	char	c = ' ';

    words = ft_split(str, c);
    wcnt = 0;
	//printf("%d", count_words(str, c));
    while (wcnt < count_words(str, c))
	{
		printf("%s\n", words[wcnt++]);
        free(words[wcnt++]);
	}
	free(words);
    return (0);
}*/
