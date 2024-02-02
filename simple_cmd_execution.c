/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:33:51 by pgober            #+#    #+#             */
/*   Updated: 2024/01/31 15:19:38 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	init_simple_cmd(t_pipex_m *simple_cmd)
{
	simple_cmd->cmd = NULL;
	simple_cmd->poss_paths = NULL;
	simple_cmd->cmdpath = NULL;
	simple_cmd->poss_path = NULL;
	simple_cmd->compil_res = 0;
	simple_cmd->status = 0;
}

static int	simple_execute_interpreter(t_alloc *mllcd)
{
	int out;
	int in;

	if (mllcd->in_pars.cmd_table[0][1]) // input redirection
	{
		in = open(mllcd->in_pars.cmd_table[0][1], O_RDONLY);
		if (in == -1 && mllcd->in_pars.cmd_table[0][1] != NULL)
			return (ft_putstr_fd("Simplecmd-Error: Could not open input-file.\n", 2), 1);
		if (in != -1 && dup2(in, 0) == -1) //the stdin will always be the in
		{
			close(in);
			return (ft_putstr_fd("Simplecmd-Error: Interrupted system call. Permission for input-file denied.\n", 2), 4);
		}
	}

	if (mllcd->in_pars.cmd_table[0][4])
		outredir_appendmode(mllcd, 0);

	if (mllcd->in_pars.cmd_table[0][2]) // output redirection
	{
		out = open(mllcd->in_pars.cmd_table[0][2], O_WRONLY | O_CREAT | O_TRUNC, 0777); // on the 2nd position of the last command there will always be what is interpreted as the out by the parser
		if (out == -1 && mllcd->in_pars.cmd_table[0][2] != NULL)
			return (ft_putstr_fd("Simplecmd-Error: Could not open outputfile.\n", 2), 1);
		if (out != -1 && dup2(out, 1) == -1) //the stdout will always be the out
		{
			if (in != -1)
				close(in);
			close(out);
			return (ft_putstr_fd("Simplecmd-Error: Interrupted system call. Permission for output-file denied.\n", 2), 4);
		}
	}
	return (0);
}

static int	simple_execute(t_alloc *mllcd, char **cmd)
{
	//char	**cmd;
	char	*cmdpath;
	char	**envv;
	int		res;

	/* if (simple_execute_interpreter(mllcd, &cmd))
		return (ft_lstclear(&mllcd->env_list), 1); */
	envv = convert_linkedlst_to_table(mllcd);

	res = builtins_2(cmd, mllcd);
	if (res != -1)
		return (free_env_table(envv), perror("builtins2"), res);

	cmdpath = pipex_find_cmd_path(cmd[0], envv, &mllcd->simple_cmd);
	if (cmdpath == NULL)
	{
		// cmdpath = cmd[0]; //try if this command is right here in the current directory
		free_env_table(envv);
		return (ft_putstr_fd("Simplecmd-Error: cmd not found.\n", 2), 127);
	}
	if (access(cmdpath, F_OK) != 0)
		return (free_env_table(envv), ft_putstr_fd("Simplecmd-Error: cmd not found.\n", 2), 127);
	if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) != 0)
		return (free_env_table(envv), ft_putstr_fd("Simplecmd-Error: Access to cmdpath denied\n", 2), 126);
	
	if (execve(cmdpath, cmd, envv) == -1)
		return (free_env_table(envv), ft_putstr_fd("Simplecmd-Error: No such process!\n", 2), 2);
	return (free_env_table(envv), ft_putstr_fd("Something went wrong", 2), 0);
}

int	run_simple_cmd(t_alloc *mllcd)
{
	int		pid;
	char	**cmd;
	int		res;
	int		c;

	init_simple_cmd(&mllcd->simple_cmd);
	cmd = ft_split_w_quotes(mllcd->in_pars.cmd_table[0][0], ' '); // on the cmd-position 0 there is always the command
	if (!cmd)
		return (1);
	c = 0; // now remove "" from everywhere
	while (cmd[c] && c < 6)
	{
		cmd[c] = ft_remove_quotes(cmd[c]);
		c++;
	}

	printf("cmd = ["); // PRINTING FOR DEBUGGING
	int i = -1;
	while (cmd[++i])
		printf("%s,", cmd[i]);
	printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	res = builtins_1(cmd, mllcd);
	if (res != -1)
		return (perror("builtins1"), res);
	pid = fork();
	if (pid < 0)
		return (ft_lstclear(&mllcd->env_list), free_strstr(cmd), ft_putstr_fd("Simplecmd-Error: forking process failed.\n", 2), 6);
	else if (pid == 0) // means we are in child process
	{
		if (simple_execute_interpreter(mllcd))
		{
			free_strstr(cmd);
			free_before_exit(mllcd);
			exit(mllcd->exit_status);
		}
		//printf("created child %d with compil res %d\n", i, compil_res);
		mllcd->simple_cmd.compil_res = simple_execute(mllcd, cmd);
		mllcd->exit_status = mllcd->simple_cmd.compil_res;
		free_strstr(cmd);
		free_before_exit(mllcd);
		// break ; //should break the loop in order to prevent child process from building pther processes
		exit(mllcd->exit_status);
	}
	waitpid(pid, &mllcd->simple_cmd.compil_res, 0);
	mllcd->exit_status = WEXITSTATUS(mllcd->simple_cmd.compil_res);
	return (free_strstr(cmd), mllcd->exit_status);
}

//cc -Wall -Wextra -Werror simple_cmd_execution.c find_cmd.c finish.c libft/*.c -lreadline -g
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./a.out
// int	main(int argc, char **argv, char **envv)
// {
// 	t_pipex_m	simple_cmd;
//	 int	 pid;
//
// 	if (argv[argc - 1] == NULL)
// 		return (1);
//	
// 	// the below is just random numbers/strings for testing, can be deleted as soon as we have cmd_table
// 	//this command works -leak -proof  cat _testfile | wc -l > out
// 	//let's try the command cat _testfile | wc -l | cat >out   vs   cat _testfile | wc -l | wc -l >out
// 	char	***cmd_table;
// 	cmd_table = (char ***)malloc(1 * sizeof(char *)); // 2 for (each pipenum + 1) ----> +1 as we start counting from 0
// 	cmd_table[0] = (char **)malloc(3 * sizeof(char *));
// 	cmd_table[0][0] = "wc -l";
// 	cmd_table[0][1] = "_testfile";
// 	cmd_table[0][2] = "out";
// 	// the above will be defined in parser and set to NULL if they are not specified in cmd
//
//	 init_simple_cmd(&simple_cmd);
//	 pid = fork();
//	 if (pid < 0)
//		 return (ft_putstr_fd("Simplecmd-Error: forking process failed.\n", 2), 6);
//	 else if (pid == 0) // means we are in child process
//	 {
//		 //printf("created child %d with compil res %d\n", i, compil_res);
//		 simple_cmd.compil_res = simple_execute(cmd_table, envv, &simple_cmd);
//		 if (simple_cmd.compil_res != 0)
//			 return (simple_cmd.compil_res);
//	 }
//	 waitpid(pid, &simple_cmd.status , 0);
//	 //return ()
//	 free(cmd_table[0]);
// 	free(cmd_table);
// 	return (WEXITSTATUS(simple_cmd.status));
// }
