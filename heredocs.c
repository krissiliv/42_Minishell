/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:53:30 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 16:53:00 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int process_cmd(char **envv, t_alloc *mllcd)
{
	int	c;

	mllcd->simple_cmd.cmd = ft_split_w_quotes(mllcd->in_pars.cmd_table[0][0], ' '); // on the cmd-position 0 there is always the command
	if (!mllcd->simple_cmd.cmd)
		return (1);
	c = 0; // now remove "" from everywhere
	while (mllcd->simple_cmd.cmd[c] && c < 6)
	{
		if (mllcd->simple_cmd.cmd[c] && mllcd->simple_cmd.cmd[c][0] == '\"')
			mllcd->simple_cmd.cmd[c] = ft_strtrim(mllcd->simple_cmd.cmd[c], "\"");
		else if (mllcd->simple_cmd.cmd[c] && mllcd->simple_cmd.cmd[c][0] == '\'')
			mllcd->simple_cmd.cmd[c] = ft_strtrim(mllcd->simple_cmd.cmd[c], "\'");
		c++;
	}

	printf("cmd = ["); // PRINTING FOR DEBUGGING
	int i = -1;
	while (mllcd->simple_cmd.cmd[++i])
		printf("%s,", mllcd->simple_cmd.cmd[i]);
	printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	mllcd->simple_cmd.cmdpath = pipex_find_cmd_path(mllcd->simple_cmd.cmd[0], envv, &mllcd->simple_cmd);
	free_strstr(mllcd->simple_cmd.poss_paths);
	free(mllcd->simple_cmd.poss_path);
	if (mllcd->simple_cmd.cmdpath == NULL)
		mllcd->simple_cmd.cmdpath = ft_strdup(mllcd->simple_cmd.cmd[0]);
	if (access(mllcd->simple_cmd.cmdpath, F_OK) != 0)
		return (free(mllcd->simple_cmd.cmdpath), free_strstr(mllcd->simple_cmd.cmd), ft_putstr_fd("Pipex-Error: Cmdpath could not be found.\n", 2), 127);
	if (access(mllcd->simple_cmd.cmdpath, F_OK) == 0 && access(mllcd->simple_cmd.cmdpath, X_OK) != 0)
		return (free(mllcd->simple_cmd.cmdpath), free_strstr(mllcd->simple_cmd.cmd), ft_putstr_fd("Pipex-Error: Access to cmdpath denied\n", 2), 1);
	return (0);
}

static int	execute_cmd(int *pipe_ends, t_alloc *mllcd)
{
	char	**envv;
	int		res;

	envv = convert_linkedlst_to_table(mllcd);

	if (process_cmd(envv, mllcd))
		return (free_env_table(envv), free_strstr(mllcd->in_pars.m_argv), free_cmd_table(&mllcd->in_pars), 1);
	
	res = builtins(mllcd->simple_cmd.cmd, mllcd);
	if (res != -1)
		return (res);

	if (execve(mllcd->simple_cmd.cmdpath, mllcd->simple_cmd.cmd, envv) == -1)
		return (free_env_table(envv), free_strstr(mllcd->in_pars.m_argv), free_cmd_table(&mllcd->in_pars), 1);
	free_strstr(mllcd->in_pars.m_argv);
	free_cmd_table(&mllcd->in_pars);
	return (ft_putstr_fd("Something went wrong", 2), pipex_free_all(&mllcd->simple_cmd, &pipe_ends), 0);
}

static void	child(int *pipe_ends, t_alloc *mllcd)
{
	char	*gnl;

	close(pipe_ends[0]); // close reading pipeend
	while (1) // input reading until delimiter
	{
		gnl = readline("> ");
		if (ft_strcmp(gnl, mllcd->in_pars.cmd_table[0][3]) == 0)
			break;
		ft_putstr_fd(gnl, pipe_ends[1]); //made pipe_ends[1] to stdout
		ft_putstr_fd("\n", pipe_ends[1]);
		free(gnl);
	}
	close(pipe_ends[1]);
	exit(0);
}

static int	parent(int *pipe_ends, t_alloc *mllcd)
{
	wait(&mllcd->simple_cmd.status); // wait for (any) chil d--> Return Value: The PID of the terminated child, or -1 on error.
	close(pipe_ends[1]); // close writing end of pipe
	dup2(pipe_ends[0], 0);
	// line = get_next_line(pipe_ends[0]); // made pipe_ends[0] to stdin
	// while(line)
	// {
	// 	ft_putstr_fd(line, 0); //go on with printing here
	// 	free(line);
	// 	line = get_next_line(pipe_ends[0]);
	// }
	if (mllcd->in_pars.cmd_table[0][4])
		outredir_appendmode(mllcd, 0);
	close(pipe_ends[0]);
	execute_cmd(pipe_ends, mllcd);
	free_strstr(mllcd->in_pars.m_argv);
	free_cmd_table(&mllcd->in_pars);
	if (WEXITSTATUS(mllcd->simple_cmd.status) == 1)
		return (ft_putstr_fd("Child process failed: exited with 1.\n", 2), 1);
	return (WEXITSTATUS(mllcd->simple_cmd.status));
}

int	handle_heredocs(t_alloc *mllcd)
{
	int	c;
	int	pid;
	int	pipe_ends[2];

	init_simple_cmd(&mllcd->simple_cmd);
	c = pipe(pipe_ends);
	if (c == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		child(pipe_ends, mllcd);
		free(mllcd->simple_cmd.cmdpath);
		free_strstr(mllcd->simple_cmd.cmd);
	}
	else
	{
		c = parent(pipe_ends, mllcd);
		return (free(mllcd->simple_cmd.cmdpath), free_strstr(mllcd->simple_cmd.cmd), c);
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