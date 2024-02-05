/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:24:16 by pgober            #+#    #+#             */
/*   Updated: 2024/02/05 09:22:58 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd()
{
    char    *cwd;

    cwd = getcwd(NULL, 1024);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    // printf("%s\n", cwd);
    free(cwd);
    return (0);
}
/*int main()
{
    if (pwd() == 0)
        printf("DONE\n");
    return (0);
}*/