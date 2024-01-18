
#include "minishell.h"

static int preparing_minishell(char **envv, t_input_parsing *in_pars)
{
	char    *input_str;

    input_str = read_input_print_prompt();
	// input_str = ft_strdup("cat << x"); //fill in stuff from EXTRA/input_parser_testing
    if (expander(&input_str, envv))
        return (1);
    printf("input_str expanded: %s\n", input_str);

    if (cmdline_input_parser(in_pars, input_str))
        return (1);
    free(input_str);
    int i = -1;
    while (i++ < in_pars->m_argc)
        printf("m_argv[%d] = %s\n", i, in_pars->m_argv[i]);
    return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell
int main(int argc, char **argv, char **envv)
{
	t_input_parsing	in_pars;
    t_pipex_m	    simple_cmd;
    int             retval;

    retval = 0;
    while (1)
    {
        if (preparing_minishell(envv, &in_pars))
            return (1);
        if (in_pars.cmd_table[0][3])
            handle_heredocs(envv, &in_pars, &simple_cmd);
        else if (in_pars.pipenum > 0)
            retval = run_pipex_multipipe(in_pars, argc, argv, envv);
        else
            retval = run_simple_cmd(&in_pars, &simple_cmd, envv);
        free_strstr(in_pars.m_argv);
        free_cmd_table(&in_pars);
    }
    return (retval);
}