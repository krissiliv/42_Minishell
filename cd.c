/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:40 by apashkov          #+#    #+#             */
/*   Updated: 2024/03/01 16:07:33 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error_handler(t_alloc *mllcd, char *str)
{
	mllcd->exit_status = 1;
	ft_putendl_fd(str, 2);
}

static int	update_pwds(t_env **env_list, char *pwd_var, t_alloc *mllcd)
{
	t_env	*temp;
	char	*cur_cwd;
	
	temp = *env_list;
	while (*env_list)
	{
		if (!ft_strncmp((*env_list)->env_var, pwd_var, ft_strlen(pwd_var)))
		{
			if (!ft_strcmp(pwd_var, "OLDPWD"))
			{
				cur_cwd = find_envvar_value("PWD", mllcd);
				(*env_list)->env_var = ft_strjoin("OLDPWD=", cur_cwd);
				free(cur_cwd);
				if (!(*env_list)->env_var)
					return (1);
				(*env_list)->malloced = true;
			}
			else if (!ft_strcmp(pwd_var, "PWD"))
			{
				cur_cwd = getcwd(NULL, 1024);
				(*env_list)->env_var = ft_strjoin("PWD=", cur_cwd);
				free(cur_cwd);
				if (!(*env_list)->env_var)
					return (1);
				(*env_list)->malloced = true;
			}
		}
		*env_list = (*env_list)->next;
	}
	*env_list = temp;
	return (0);
}

int cd(char *path, int argc, t_alloc *mllcd)
{
    if (argc > 2)
		return (cd_error_handler(mllcd, "cd: too many arguments"), 1);
    else if (argc == 1)
    {
        if (chdir(find_envvar_value("HOME", mllcd)) == -1)
			return (cd_error_handler(mllcd, "chdir failed"), 1);
    }
    else
    {
		if (!ft_strcmp(path, "-"))
		{
			path = find_envvar_value("OLDPWD", mllcd);
			pwd();
		}
        if (chdir(path) == -1)
			return (cd_error_handler(mllcd, "chdir failed"), 1);
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
