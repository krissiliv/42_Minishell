
#include "minishell.h"

static int process_cmd(char **envv, t_input_parsing *in_pars, t_pipex_m *simple_cmd)
{
	int	c;

	simple_cmd->cmd = ft_split(in_pars->cmd_table[0][0], ' '); // on the cmd-position 0 there is always the command
	if (!simple_cmd->cmd)
		return (1);
	c = 0; // now remove "" from everywhere
	while (simple_cmd->cmd[c] && c < 6)
	{
		if (simple_cmd->cmd[c] && simple_cmd->cmd[c][0] == '\"')
			simple_cmd->cmd[c] = ft_strtrim(simple_cmd->cmd[c], "\"");
		else if (simple_cmd->cmd[c] && simple_cmd->cmd[c][0] == '\'')
			simple_cmd->cmd[c] = ft_strtrim(simple_cmd->cmd[c], "\'");
		c++;
	}

	printf("cmd = ["); // PRINTING FOR DEBUGGING
	int i = -1;
	while (simple_cmd->cmd[++i])
		printf("%s,", simple_cmd->cmd[i]);
	printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	simple_cmd->cmdpath = pipex_find_cmd_path(simple_cmd->cmd[0], envv, simple_cmd);
	free_strstr(simple_cmd->poss_paths);
	free(simple_cmd->poss_path);
	if (simple_cmd->cmdpath == NULL)
		simple_cmd->cmdpath = simple_cmd->cmd[0];
	if (access(simple_cmd->cmdpath, F_OK) != 0)
		return (free(simple_cmd->cmdpath), free_strstr(simple_cmd->cmd), ft_putstr_fd("Pipex-Error: Cmdpath could not be found.\n", 2), 127);
	if (access(simple_cmd->cmdpath, F_OK) == 0 && access(simple_cmd->cmdpath, X_OK) != 0)
		return (free(simple_cmd->cmdpath), free_strstr(simple_cmd->cmd), ft_putstr_fd("Pipex-Error: Access to cmdpath denied\n", 2), 1);
	return (0);
}

static int	execute_cmd(char **envv, int *pipe_ends,t_input_parsing *in_pars, t_pipex_m *simple_cmd)
{
	if (process_cmd(envv, in_pars, simple_cmd))
		return (free_strstr(in_pars->m_argv), free_cmd_table(in_pars), 1);
	if (execve(simple_cmd->cmdpath, simple_cmd->cmd, envv) == -1)
		return (free_strstr(in_pars->m_argv), free_cmd_table(in_pars), 1);
	free_strstr(in_pars->m_argv);
	free_cmd_table(in_pars);
	return (ft_putstr_fd("Something went wrong", 2), pipex_free_all(simple_cmd, &pipe_ends), 0);
}

static void	child(int *pipe_ends, t_input_parsing *in_pars)
{
	char	*gnl;

	close(pipe_ends[0]); // close reading pipeend
	while (1) // input reading until delimiter
	{
		gnl = readline("> ");
		if (ft_strcmp(gnl, in_pars->cmd_table[0][3]) == 0)
			break;
		ft_putstr_fd(gnl, pipe_ends[1]); //made pipe_ends[1] to stdout
		ft_putstr_fd("\n", pipe_ends[1]);
		free(gnl);
	}
	close(pipe_ends[1]);
	exit(0);
}

static int	parent(char **envv, int *pipe_ends, t_input_parsing *in_pars, t_pipex_m *simple_cmd)
{
	wait(&simple_cmd->status); // wait for (any) chil d--> Return Value: The PID of the terminated child, or -1 on error.
	close(pipe_ends[1]); // close writing end of pipe
	dup2(pipe_ends[0], 0);
	// line = get_next_line(pipe_ends[0]); // made pipe_ends[0] to stdin
	// while(line)
	// {
	// 	ft_putstr_fd(line, 0); //go on with printing here
	// 	free(line);
	// 	line = get_next_line(pipe_ends[0]);
	// }
	close(pipe_ends[0]);
	execute_cmd(envv, pipe_ends, in_pars, simple_cmd);
	free_strstr(in_pars->m_argv);
	free_cmd_table(in_pars);
	if (WEXITSTATUS(simple_cmd->status) == 1)
		return (ft_putstr_fd("Child process failed: exited with 1.\n", 2), 1);
	return (WEXITSTATUS(simple_cmd->status));

}

int	handle_heredocs(char **envv, t_input_parsing *in_pars, t_pipex_m *simple_cmd)
{
	int	c;
	int	pid;
	int	pipe_ends[2];

	init_simple_cmd(simple_cmd);
	c = pipe(pipe_ends);
	if (c == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		child(pipe_ends, in_pars);
		free(simple_cmd->cmdpath);
		free_strstr(simple_cmd->cmd);
	}
	else
	{
		c = parent(envv, pipe_ends, in_pars, simple_cmd);
		return (free(simple_cmd->cmdpath), free_strstr(simple_cmd->cmd), c);
	}
	return (0);

}

// cc -Wall -Wextra -Werror heredocs.c finish.c find_cmd.c expander.c input_parser.c input_parser_utils.c input_parser_ft_split_w_quotes.c simple_cmd_execution.c libft/*.c get_next_line/*.c -lreadline -g
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./a.out
// int main(int argc, char **argv, char **envv)
// {
// 	t_input_parsing	in_pars;
// 	char			*input_str;
// 	t_pipex_m		simple_cmd;

// 	if (!(*argv)[argc - 1])
// 		return (1);
// 	input_str = ft_strdup("cat << x"); //fill in stuff from EXTRA/input_parser_testing
// 	 // while (1)
// 	 // {
// 		 // input_str = read_input_print_prompt();
		
// 	 if (expander(&input_str, envv))
// 	 	return (1);
// 	 printf("input_str expanded: %s\n", input_str);

// 	 if (cmdline_input_parser(&in_pars, input_str))
// 		 return (1);
// 	 free(input_str);
// 	 int i = 0;
// 	 while (i < in_pars.m_argc)
// 	 {
// 		 printf("m_argv[%d] = %s\n", i, in_pars.m_argv[i]);
// 		 i++;
// 	 }

// 	 if (in_pars.cmd_table[0][3])
// 		 handle_heredocs(envv, &in_pars, &simple_cmd);

// 	 free_strstr(in_pars.m_argv);
// 	 free_cmd_table(&in_pars);
// 	 // }
// 	 return (0);
// }