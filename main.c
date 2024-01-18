
#include "minishell.h"

static int  count_cmd_args(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    return (i - 1);
}

static void	builtins(char **cmd, t_alloc *mllcd, t_env *env_list)
{
	if (!ft_strncmp("echo", cmd[0], 4))
		echo(cmd, mllcd);
	if (!ft_strncmp("cd", cmd[0], 2))
		cd(cmd[1], count_cmd_args(cmd), env_list, mllcd);
	if (!ft_strncmp("pwd", cmd[0], 3))
		pwd(mllcd);
	if (!ft_strncmp("env", cmd[0], 3))
		env(env_list, mllcd);
	if (!ft_strncmp("exporting", cmd[0], 6))
		exporting(&env_list, cmd, mllcd); // should have no dollar signs
	if (!ft_strncmp("unset", cmd[0], 5))
		unset(&env_list, cmd, mllcd);
	if (!ft_strncmp("exit", cmd[0], 4))
		exiting(mllcd, cmd[1], count_cmd_args(cmd));
}

static int preparing_minishell(char **envv, t_input_parsing *in_pars, t_alloc *mllcd)
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

    mllcd->exit_status = 0;
    return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell
int main(int argc, char **argv, char **envv)
{
	t_input_parsing	in_pars;
    t_pipex_m	    simple_cmd;
    int             retval;
    t_alloc         mllcd;

    retval = 0;
    while (1)
    {
        if (preparing_minishell(envv, &in_pars, &mllcd))
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