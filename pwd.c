/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:24:16 by pgober            #+#    #+#             */
/*   Updated: 2024/02/06 14:34:26 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get_cwd allocates memory, so i need to make sure to free it

int pwd()
{
    char    *cwd;

    cwd = getcwd(NULL, 1024);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (0);
}
/*int main()
{
    if (pwd() == 0)
        printf("DONE\n");
    return (0);
}*/