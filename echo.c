/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:28 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:11 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO:

static int	validate_n_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[0] == '-')
	{
		if (!flag[1])
			return (1);
		while (flag[i])
		{
			if (flag[i] == 'n')
				i++;
			else
				return (1);
		}
		return (0);
	}
	else
		return (1);
}

int echo(char *cmd[], t_alloc *mllcd)
{
    int i;

    i = 2;
    if (!cmd[2] && !cmd[2][0])
        write(1, "\n", 1);
	else
	{
		while (cmd[i])
		{
			if (!validate_n_flag(cmd[i]) && i == 1)
				i++;
			ft_putstr_fd(cmd[i++], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
		if (validate_n_flag(cmd[1]) == 1)
			write(1, "\n", 1);
	}
    return (0);
}

/*int main(int argc, char *argv[])
{
    echo(argv[1], argv, argc);
    return (0);
}*/