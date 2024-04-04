/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:01:40 by apashkov          #+#    #+#             */
/*   Updated: 2024/04/03 18:28:50 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_with_minus(char **path, t_alloc *mllcd)
{
	free(*path);
	*path = find_envvar_value("OLDPWD", mllcd);
	pwd();
}

static int	var_is_pwd(t_env **temp)
{
	char	*cur_cwd;

	cur_cwd = getcwd(NULL, 1024);
	if ((*temp)->malloced)
		free((*temp)->env_var);
	if (!cur_cwd)
		return (1);
	(*temp)->env_var = ft_strjoin("PWD=", cur_cwd);
	free(cur_cwd);
	if (!(*temp)->env_var)
		return (1);
	(*temp)->malloced = true;
	return (0);
}

static int	var_is_oldpwd(t_env **temp, t_alloc *mllcd)
{
	char	*cur_cwd;

	cur_cwd = find_envvar_value("PWD", mllcd);
	if ((*temp)->malloced)
		free((*temp)->env_var);
	(*temp)->env_var = ft_strjoin("OLDPWD=", cur_cwd);
	free(cur_cwd);
	if (!(*temp)->env_var)
		return (1);
	(*temp)->malloced = true;
	return (0);
}

static int	update_pwds(t_env **env_list, char *pwd_var, t_alloc *mllcd)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->env_var, pwd_var, ft_strlen(pwd_var)))
		{
			if (!ft_strcmp(pwd_var, "OLDPWD"))
			{
				if (var_is_oldpwd(&temp, mllcd))
					return (1);
			}
			else if (!ft_strcmp(pwd_var, "PWD"))
			{
				if (var_is_pwd(&temp))
					return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	cd(char **cmd, int argc, t_alloc *mllcd)
{
	char	*path;

	if (argc > 2)
		return (cd_error_handler(mllcd, "cd: too many arguments"), 1);
	else if (argc == 1)
	{
		if (chdir(find_envvar_value("HOME", mllcd)) == -1)
			return (cd_error_handler(mllcd, "chdir failed"), 1);
	}
	else
	{
		path = ft_strdup(cmd[1]);
		if (!path)
			return (free_strstr(cmd), exit_mllcfail(mllcd), 1);
		if (!ft_strcmp(path, "-"))
			case_with_minus(&path, mllcd);
		if (chdir(path) == -1)
			return (free(path), cd_error_handler(mllcd, "chdir failed"), 1);
		free(path);
	}
	if (update_pwds(&mllcd->env_list, "OLDPWD", mllcd) == 1 || \
		update_pwds(&mllcd->env_list, "PWD", mllcd))
		return (free_strstr(cmd), exit_mllcfail(mllcd), 1);
	return (mllcd->exit_status = 0, 0);
}

/* int main(int argc, char *argv[])
{
    pwd();
    cd(argv[2], argc - 1);
    pwd();
    printf("DONE\n");
    return (0);
} */
