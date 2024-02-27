/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:40 by apashkov          #+#    #+#             */
/*   Updated: 2024/02/27 15:41:33 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwds(t_env **env_list, char *pwd_var, t_alloc *mllcd)
{
	t_env	*temp;

	temp = *env_list;
	while (*env_list)
	{
		if (!ft_strcmp(pwd_var, "OLDPWD"))
		{
			(*env_list)->env_var = ft_strjoin("OLDPWD=",
					find_envvar_value("PWD", mllcd));
			if (!(*env_list)->env_var)
				return (1);
			(*env_list)->malloced = true;
		}
		else if (!ft_strcmp(pwd_var, "PWD"))
		{
			(*env_list)->env_var = ft_strjoin("PWD=", getcwd(NULL, 1024));
			if (!(*env_list)->env_var)
				return (1);
			(*env_list)->malloced = true;
		}
		*env_list = (*env_list)->next;
	}
	*env_list = temp;
	return (0);
}

static void	cd_error_handle(t_alloc *mllcd)
{
	mllcd->exit_status = 1;
	perror("cd");
}

int	cd(char *path, int argc, t_alloc *mllcd)
{
	if (argc > 2)
	{
		mllcd->exit_status = 1;
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	}
	else if (argc == 1)
	{
		if (chdir(find_envvar_value("HOME", mllcd)) == -1)
			return (cd_error_handle(mllcd), 1);
	}
	else
	{
		if (!ft_strcmp(path, "-"))
		{
			if (chdir(find_envvar_value("OLDPWD", mllcd)) == -1)
				return (cd_error_handle(mllcd), 1);
			pwd();
		}
		else if (chdir(path) == -1)
			return (cd_error_handle(mllcd), 1);
	}
	update_pwds(&mllcd->env_list, "OLDPWD", mllcd);
	update_pwds(&mllcd->env_list, "PWD", mllcd);
	mllcd->exit_status = 0;
	return (0);
}

/* int main(int argc, char *argv[])
{
    pwd();
    cd(argv[2], argc - 1);
    pwd();
    printf("DONE\n");
    return (0);
} */
