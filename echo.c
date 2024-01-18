/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:28 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 11:26:41 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO:

static int	check_minus_pos(char *cmd[])
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ()
		i++;
	}
}

int echo(char *cmd[], t_alloc *mllcd)
{
    int i;

    i = 2;
    if (argc < 3)
        write(1, "\n", 1);
    while (i < argc)
    {
        ft_putstr_fd(argv[i++], 1);
        ft_putchar_fd(' ', 1);
		i = 0;
		while (cmd[i] && ft_strncmp("-", cmd[1], 2))
			i
        if ( != 0)
            write(1, "\n", 1);
    }
    return (0);
}

/*int main(int argc, char *argv[])
{
    echo(argv[1], argv, argc);
    return (0);
}*/