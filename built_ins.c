/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:50:43 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 10:28:28 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	builtins(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 4))
		echo();
	if (!ft_strncmp("cd", cmd, 2))
		cd();
	if (!ft_strncmp("pwd", cmd, 3))
		pwd();
	if (!ft_strncmp("env", cmd, 3))
		env();
	if (!ft_strncmp("export", cmd, 6))
		export();
	if (!ft_strncmp("unset", cmd, 5))
		unset();
	if (!ft_strncmp("exit", cmd, 4))
		exit();
}