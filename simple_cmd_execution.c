
#include "minishell.h"

void	init_simple_cmd(t_pipex_m *simple_cmd)
{
	simple_cmd->cmd = NULL;
	simple_cmd->poss_paths = NULL;
	simple_cmd->cmdpath = NULL;
	simple_cmd->poss_path = NULL;
	simple_cmd->compil_res = 0;
	simple_cmd->status = 0;
}

static int	simple_execute_interpreter(char ***cmd_table, char ***cmd)
{
	int out;
	int in;
	int c;

	*cmd = ft_split(cmd_table[0][0], ' '); // on the cmd-position 0 there is always the command
	if (!(*cmd))
		return (1);
	c = 0; // now remove "" from everywhere
	while ((*cmd)[c] && c < 6)
	{
		if ((*cmd)[c] && (*cmd)[c][0] == '\"')
			(*cmd)[c] = ft_strtrim((*cmd)[c], "\"");
		else if ((*cmd)[c] && (*cmd)[c][0] == '\'')
			(*cmd)[c] = ft_strtrim((*cmd)[c], "\'");
		c++;
	}

	printf("cmd = ["); // PRINTING FOR DEBUGGING
	int i = -1;
	while ((*cmd)[++i])
		printf("%s,", (*cmd)[i]);
	printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	if (cmd_table[0][1]) // input redirection
	{
		in = open(cmd_table[0][1], O_RDONLY);
		if (in == -1 && cmd_table[0][1] != NULL)
			return (ft_putstr_fd("Pipex-Error: Could not open input-file.\n", 2), 1);
		if (in != -1 && dup2(in, 0) == -1) //the stdin will always be the in
		{
			close(in);
			return (ft_putstr_fd("Pipex-Error: Interrupted system call. Permission for input-file denied.\n", 2), 4);
		}
	}

	if (cmd_table[0][2]) // output redirection
	{
		out = open(cmd_table[0][2], O_WRONLY | O_CREAT | O_TRUNC, 0777); // on the 2nd position of the last command there will always be what is interpreted as the out by the parser
		if (out == -1 && cmd_table[0][2] != NULL)
			return (ft_putstr_fd("Pipex-Error: Could not open outputfile.\n", 2), 1);
		if (out != -1 && dup2(out, 1) == -1) //the stdout will always be the out
		{
			if (in != -1)
				close(in);
			close(out);
			return (ft_putstr_fd("Pipex-Error: Interrupted system call. Permission for output-file denied.\n", 2), 4);
		}
	}
	return (0);
}

static int	simple_execute(char ***cmd_table, char **envv, t_pipex_m *simple_cmd)
{
	char	**cmd;
	char	*cmdpath;

	if (simple_execute_interpreter(cmd_table, &cmd))
		return (1);
	cmdpath = pipex_find_cmd_path(cmd[0], envv, simple_cmd);
	if (cmdpath == NULL)
		cmdpath = cmd[0]; //try if this command is right here
	if (access(cmdpath, F_OK) != 0)
		return (ft_putstr_fd("Pipex-Error: cmd not found.\n", 2), 1);
	if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) != 0)
		return (ft_putstr_fd("Pipex-Error: Access to cmdpath denied\n", 2), 1);

	if (execve(cmdpath, cmd, envv) == -1)
		return (ft_putstr_fd("Pipex-Error: No such process!\n", 2), 3);
	return (ft_putstr_fd("Something went wrong", 2), 0);
}

int	run_simple_cmd(t_input_parsing *in_pars, t_pipex_m *simple_cmd, char **envv)
{
	int	pid;

	init_simple_cmd(simple_cmd);
	pid = fork();
	if (pid < 0)
		return (free_strstr(in_pars->m_argv), free_cmd_table(in_pars), ft_putstr_fd("Pipex-Error: forking process failed.\n", 2), 6);
	else if (pid == 0) // means we are in child process
	{
		//printf("created child %d with compil res %d\n", i, compil_res);
		simple_cmd->compil_res = simple_execute(in_pars->cmd_table, envv, simple_cmd);
		if (simple_cmd->compil_res != 0)
			return (free_strstr(in_pars->m_argv), free_cmd_table(in_pars), simple_cmd->compil_res);
		// break ; //should break the loop in order to prevent child process from building pther processes
	}
	waitpid(pid, &simple_cmd->status , 0);
	return (WEXITSTATUS(simple_cmd->status));
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
//		 return (ft_putstr_fd("Pipex-Error: forking process failed.\n", 2), 6);
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