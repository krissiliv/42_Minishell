/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:28 by apashkov          #+#    #+#             */
/*   Updated: 2024/02/27 15:18:44 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_n_flag(char *flag)
{
	int	i;

	i = 1;
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

int	echo(char *cmd[])
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		return (write(1, "\n", 1), 0);
	}
	while (!validate_n_flag(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (validate_n_flag(cmd[1]) == 1)
		write(1, "\n", 1);
	return (0);
}

/* int main(int argc, char *argv[])
{
	t_alloc	*mllcd;
	mllcd = (t_alloc *)malloc(sizeof(t_alloc));
	mllcd->exit_status = 0;
	argc = 0;
	char	*cmd[5];
	cmd[0] = argv[1];
	cmd[1] = argv[2];
	cmd[2] = argv[3];
	cmd[3] = argv[4];
	cmd[4] = NULL;
 	
    echo(cmd, mllcd);
    return (0);
} */