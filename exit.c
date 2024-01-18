/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:08:48 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 11:02:28 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	exit_program(t_alloc *mallcd)
{
	// close all fds;
	free_everything(mallcd);
	exit(mallcd->exit_status);
}

static int	validate_input(char *input)
{
	int	i;

	i = 0;
	if (is_pm(input[0]) == 1 || is_num(input[0]) == 1)
		i++;
	else
		return (1);
	while (input[i])
	{
		if (is_num(input[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

int	exit(t_alloc mallcd, char *input)
{
	if (validate_input(input) == 1)
	{
		ft_putstr_fd("exit: numeric argument required", 2);
		mallcd.exit_status = 2;
	}
	if (input)
		mallcd.exit_status = ft_atoi_minishell(input);
	exit_program(mallcd);
	return (0);
}