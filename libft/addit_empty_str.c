/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_empty_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:59:01 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 11:59:20 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_is_empty(char *str)
{
	int	i;
	int	check_only_spaces;

	if (!str || ft_strlen(str) == 0)
		return (1);
	i = 0;
	check_only_spaces = 1;
	while (str[i])
	{
		if (!is_space(str[i++]))
			check_only_spaces = 0;
	}
	if (check_only_spaces)
		return (1);
	return (0);
}
