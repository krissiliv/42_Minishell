/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:40 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 10:59:29 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwds(t_env *env_list, char *pwd_var)
{
	t_env	*temp;
	
	temp = env_list;
	while (env_list)
	{
		if (!ft_strncmp(env_list->env_var, pwd_var, ft_strlen(pwd_var)))
		{
			if (!ft_strcmp(pwd_var, "OLDPWD"))
			{
				env_list->env_var = ft_strjoin("OLDPWD=", 
					find_envvar_value("PWD", env_list));
				if (!env_list->env_var)
					return (1);
			}
			else if (!ft_strcmp(pwd_var, "PWD"))
			{
				env_list->env_var = ft_strjoin("PWD=", getcwd(NULL, 1024));
				if (!env_list->env_var)
					return (1);
			}
		}
		env_list = env_list->next;
	}
	env_list = temp;
}

int cd(char *path, int argc, t_env *env_list, t_alloc *mllcd)
{
    if (argc > 2)
        return (ft_putstr_fd("Too many arguments", 2), 1);
    else if (argc == 1 || ft_strncmp(path, "~", 1) == 0)
    {
        if (chdir(find_envvar_value("HOME", env_list)) == -1)
		{
			mllcd->exit_status = 1;
            return (perror("Chdir failed"), 1);
		}
    }
    else
    {
        if (chdir(path) == -1)
		{
			mllcd->exit_status = 1;
            return (perror("Chdir failed"), 1);
		}
    }
	update_pwds(env_list, "OLDPWD");
	update_pwds(env_list, "PWD");
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