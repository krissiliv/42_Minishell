/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:15 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 17:52:39 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char str)
{
	if (str == 32 || (9 <= str && str <= 13) || str == '\n')
		return (1);
	return (0);
}

static int  pre_check_input(char *input_str)
{
    int i;
    int check_only_spaces;

    // printf("input_str: %s has length %zu\n", input_str, ft_strlen(input_str));
    if (!input_str || ft_strlen(input_str) == 0)
    {
        printf("\n");
        return (1);
    }
    i = 0;
    check_only_spaces = 1;
    while (input_str[i])
    {
        if (!is_space(input_str[i++]))
            check_only_spaces = 0;
    }
    if (check_only_spaces)
        return (1);
    return (0);
}

static int preparing_minishell(t_alloc *mllcd)
{
	char    *input_str;

    input_str = read_input_print_prompt();
	// input_str = ft_strdup("echo -\"$SHELL-\"-"); //fill in stuff from EXTRA/input_parser_testing
    // signals();
    if (pre_check_input(input_str) || !input_str || ft_strlen(input_str) == 0 || input_check_adapt(input_str))
		return (ft_putstr_fd("Error: Input is invalid.\n", 2), 1);
    if (expander(&input_str, mllcd))
        return (1);
    // printf("input_str expanded: %s\n", input_str);
    // remove_quotes_from_argv(&input_str); // not possible to put this here because then cmds like grep "ho < _test" do not work correctly

    if (cmdline_input_parser(&mllcd->in_pars, input_str))
        return (1);
    free(input_str);

    // printf("print m_argv again:\n");
    // int i = -1;
    // while (i++ < mllcd->in_pars.m_argc)
    //     printf("m_argv[%d] = %s\n", i, mllcd->in_pars.m_argv[i]);

    mllcd->exit_status = 0;
    mllcd->saved_stdin = dup(0);
    return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell
int main(int argc, char **argv, char **envv)
{
    int             retval;
    t_alloc         mllcd;

    retval = 0;
	mllcd.env_list = (t_env *)malloc(sizeof(t_env));
    get_env(envv, &mllcd.env_list);
	//prntlist(mllcd.env_list);
    while (1)
    {
        if (preparing_minishell(&mllcd))
        {
            mllcd.exit_status = 1;
            continue;
        }
        // if (mllcd.in_pars.cmd_table[0][4]) // I put this inside the forked processes in order not to redir parents output no?
        //     outredir_appendmode(&mllcd);
        if (mllcd.in_pars.cmd_table[0][3])
            handle_heredocs(&mllcd);
        if (mllcd.in_pars.pipenum > 0)
            retval = run_pipex_multipipe(&mllcd, argc, argv);
        else
            retval = run_simple_cmd(&mllcd);
        if (mllcd.in_pars.cmd_table[0][3])
            dup2(mllcd.saved_stdin, 0);
        free_strstr(mllcd.in_pars.m_argv);
        free_cmd_table(&mllcd.in_pars);
    }
    free_before_exit(&mllcd); // this is the only thing that is not freedwhen pressing CTRL+C
    return (retval);
}