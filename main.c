/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:15 by pgober            #+#    #+#             */
/*   Updated: 2024/01/18 16:58:16 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int preparing_minishell(char **envv, t_alloc *mllcd)
{
	char    *input_str;

    get_env(envv, &mllcd->env_list);
    // input_str = read_input_print_prompt();
	input_str = ft_strdup("cat EXTRA/EXTRA_progress_tracking >> _testfile"); //fill in stuff from EXTRA/input_parser_testing
    if (expander(&input_str, mllcd))
        return (1);
    // printf("input_str expanded: %s\n", input_str);

    if (cmdline_input_parser(&mllcd->in_pars, input_str))
        return (1);
    free(input_str);
    int i = -1;
    while (i++ < mllcd->in_pars.m_argc)
        printf("m_argv[%d] = %s\n", i, mllcd->in_pars.m_argv[i]);

    mllcd->exit_status = 0;
    return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell
int main(int argc, char **argv, char **envv)
{
    int             retval;
    t_alloc         mllcd;

    retval = 0;
    // while (1)
    // {
        if (preparing_minishell(envv, &mllcd))
            return (1);
        if (mllcd.in_pars.cmd_table[0][4])
            outredir_appendmode(&mllcd);
        if (mllcd.in_pars.cmd_table[0][3])
            handle_heredocs(&mllcd);
        else if (mllcd.in_pars.pipenum > 0)
            retval = run_pipex_multipipe(&mllcd, argc, argv);
        else
            retval = run_simple_cmd(&mllcd);
        free_strstr(mllcd.in_pars.m_argv);
        free_cmd_table(&mllcd.in_pars);
    // }
    return (retval);
}