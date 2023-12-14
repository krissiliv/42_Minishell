/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:05:03 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 13:27:46 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_check(char **argv)
{
	int	ch;
	int	arg;

	arg = 0;
	while (argv[arg++])
	{
		ch = 0;
		while (argv[arg++][ch])
		{
			
		}
	}
	return (0);
}
