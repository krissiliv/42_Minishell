/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_free_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:55:26 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 16:05:27 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strstr(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free_and_null((void *)str);
	}
}

void	free_intarr(int **arr, int number)
{
	int	i;

	i = 0;
	while (i < number)
		free(arr[i++]);
	free_and_null((void *)arr);
}
