/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:56:14 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 11:47:56 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_null(void *alloc)
{
	if (alloc)
	{
		free(alloc);
		alloc = NULL;
	}
}

int	abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
