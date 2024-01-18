/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:20 by pgober            #+#    #+#             */
/*   Updated: 2024/01/05 14:38:31 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	multi_execute_interpreter(char ***cmd_table, t_pipex_m *pipex_m)
{
	int c;
	int in;

    pipex_m->cmd = ft_split(cmd_table[pipex_m->cmdnum][0], ' '); // on the cmd-position 0 there is always the command
	if (!(pipex_m->cmd))
		return (1);
	c = 0; // now remove "" from everywhere
    while ((pipex_m->cmd)[c] && c < 6)
    {
        if ((pipex_m->cmd)[c] && (pipex_m->cmd)[c][0] == '\"')
            (pipex_m->cmd)[c] = ft_strtrim((pipex_m->cmd)[c], "\"");
        else if ((pipex_m->cmd)[c] && (pipex_m->cmd)[c][0] == '\'')
            (pipex_m->cmd)[c] = ft_strtrim((pipex_m->cmd)[c], "\'");
        c++;
    }

    printf("cmd = ["); // PRINTING FOR DEBUGGING
    int i = -1;
    while ((pipex_m->cmd)[++i])
        printf("%s,", (pipex_m->cmd)[i]);
    printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	in = -1;
	if (cmd_table[pipex_m->cmdnum][1]) // input redirection
    {
        in = open(cmd_table[pipex_m->cmdnum][1], O_RDONLY);
        if (in == -1 && cmd_table[pipex_m->cmdnum][1] != NULL)
            return (pipex_error_handling(NULL, pipex_m->pipenum, 2, pipex_m, false));
        if (in != -1 && dup2(in, 0) == -1) //the stdin will always be the in
        {
            close(in);
            return (pipex_error_handling(NULL, pipex_m->pipenum, 4, pipex_m, false));
        }
    }
	return (0);
}

int	execute(int **pipe_ends, char ***cmd_table, char **envv, t_pipex_m *pipex_m)
{
	if (multi_execute_interpreter(cmd_table, pipex_m))
		return (pipex_free_all(pipex_m, pipe_ends), 1);
	pipex_m->cmdpath = pipex_find_cmd_path(pipex_m->cmd[0], envv, pipex_m);
	if (pipex_m->cmdpath == NULL)
		pipex_m->cmdpath = pipex_m->cmd[0];
	if (access(pipex_m->cmdpath, F_OK) != 0)
		return (pipex_error_handling(pipe_ends, pipex_m->cmdnum, 127, pipex_m, true));
	if (access(pipex_m->cmdpath, F_OK) == 0 && \
		access(pipex_m->cmdpath, X_OK) != 0)
		return (pipex_free_all(pipex_m, pipe_ends), \
				pipex_error_handling(pipe_ends, pipex_m->cmdnum, 1, pipex_m, true));
	if (execve(pipex_m->cmdpath, pipex_m->cmd, envv) == -1)
		return (pipex_error_handling(pipe_ends, pipex_m->cmdnum, 3, pipex_m, true));
	return (ft_putstr_fd("Something went wrong", 2), pipex_free_all(pipex_m, pipe_ends), 0);
}

int	child(int **pipe_ends, char ***cmd_table, char **envv, t_pipex_m *pipex_m)
{
	int	cmd_file;
	int i;

	//printf("entered child %d\n", pipex_m->cmdnum);
	cmd_file = -1;
	if (cmd_table[pipex_m->cmdnum][1] != NULL) //on cmd-position 1 there is always sth that is believed to be a file
		cmd_file = open(cmd_table[pipex_m->cmdnum][1], O_RDONLY);
	if (cmd_file == -1 && cmd_table[pipex_m->cmdnum][1] != NULL) // I would set the filename of cmd_table[cmdnum][1] to NULL if the cmd doesn't have a file
		return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 1, pipex_m, false));
	//printf("in child %d, the cmd is %s and the file is %s\n", pipex_m->cmdnum, cmd_table[pipex_m->cmdnum][0], cmd_table[pipex_m->cmdnum][1]);
	// what is the stdin of my child? if cmdnum == 0, then if is probably a file, if it is not a file then it can be stdin as f.e. here: ls | cat > out
	if (pipex_m->cmdnum == 0 && cmd_table[pipex_m->cmdnum][1] != NULL) // turn file into stdin
	{
		if (dup2(cmd_file, 0) == -1) //turn file into stdin
		{
			close(cmd_file);
			return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 4, pipex_m, true));
		}
		//printf("in child %d, made %s to stdin\n", pipex_m->cmdnum, cmd_table[pipex_m->cmdnum][1]);
	}
	else if (pipex_m->cmdnum != 0)
	{
		if (dup2(pipe_ends[pipex_m->cmdnum - 1][0], 0) == -1) //turn reading pipeend into stdin
		{
			close(cmd_file);
			return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 4, pipex_m, true));
		}
		//printf("in child %d, made pipe_ends[%d][0] to stdin\n", pipex_m->cmdnum, pipex_m->cmdnum - 1);
	}
	// what is the stdout of my child? since for cmdnum == pipenum there is an other child, for this child the stdout will always be the pipeend to the next child 
	//printf("in child %d dup made pipe_ends[%d][1] to stdout ...\n", pipex_m->cmdnum, pipex_m->cmdnum);
	if (dup2(pipe_ends[pipex_m->cmdnum][1], 1) == -1) // turn writing pipeend into stdout
		return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 1, pipex_m, true));
	//printf("in child %d made pipe_ends[%d][1] to stdout\n", pipex_m->cmdnum, pipex_m->cmdnum);
	i = 0;
	while (i < pipex_m->pipenum)
	{
		close (pipe_ends[i][0]);
		close (pipe_ends[i][1]);
		i++;
	}
	free_intarr(pipe_ends, pipex_m->pipenum);
	if (cmd_file != -1)
		close(cmd_file);
	exit (execute(pipe_ends, cmd_table, envv, pipex_m));
}
// when you call the pipe syscall like pipe(array), then array[0] is for reading and array[1] is for writing.

int	last_child(int **pipe_ends, char ***cmd_table, char **envv, t_pipex_m *pipex_m)
{
	int	outfile;
	int i;

	//printf("last child ->opening %s\n", cmd_table[pipex_m->cmdnum][2]);
	outfile = -1;
	if (cmd_table[pipex_m->cmdnum][2])
	{
		outfile = open(cmd_table[pipex_m->cmdnum][2], O_WRONLY | O_CREAT | O_TRUNC, 0777); // on the 2nd position of the last command there will always be what is interpreted as the outfile by the parser
		if (outfile == -1 && cmd_table[pipex_m->cmdnum][2] != NULL)
			return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 10, pipex_m, true));
		if (outfile != -1 && dup2(outfile, 1) == -1) //the stdout will always be the outfile
		{
			close(outfile);
			return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 4, pipex_m, true));
		}
	}
	//printf("in child %d make %s to stdout\n", pipex_m->cmdnum, cmd_table[pipex_m->cmdnum][2]);
	if (dup2(pipe_ends[pipex_m->cmdnum - 1][0], 0) == -1) //for last child, the stdin will always be the reading pipeend to the last child
		return (pipex_error_handling(pipe_ends, pipex_m->pipenum, 1, pipex_m, true));
	//printf("in child %d, made pipe_ends[%d][0] to stdin\n", pipex_m->cmdnum, pipex_m->cmdnum - 1);
	i = 0;
	while (i < pipex_m->pipenum)
	{
		close (pipe_ends[i][0]);
		close (pipe_ends[i][1]);
		i++;
	}
	free_intarr(pipe_ends, pipex_m->pipenum);
	if (outfile != -1)
		close(outfile);
	exit (execute(pipe_ends, cmd_table, envv, pipex_m));
}

int	pipex(int **pipe_ends, char ***cmd_table, char **envv, t_pipex_m *pipex_m)
{
	int	i;
	int	pid[pipex_m->pipenum + 1];

	i = 0;
	pipex_m->status = 0;
	while (i < pipex_m->pipenum) // within each pipe there is one command => the number of the cmd < pipenum and the last command is pipenum
	{
		pipex_m->cmdnum = i;
		pid[i] = fork();
		if (pid[i] < 0)
			return (pipex_error_handling(pipe_ends, i, 6, pipex_m, true));
		else if (pid[i] == 0) // means we are in child process number i
		{
			//printf("created child %d with compil res %d\n", i, pipex_m->compil_res);
			pipex_m->compil_res = child(pipe_ends, cmd_table, envv, pipex_m);
			if (pipex_m->compil_res != 0)
				return (pipex_free_all(pipex_m, pipe_ends), pipex_m->compil_res);
			// i = 0;
			// while (i < pipex_m->pipenum)
			// {
			// 	close (pipe_ends[i][0]);
			// 	close (pipe_ends[i][1]);
			// 	i++;
			// }
			// return (0);
			break ;
		}
		// sleep(1);
		i++;
	}
	// last child --> should but this until ___ into if (pid[i] !=  0 for all i) in order to prevent child processes that broke while loop to form other child processes
	pipex_m->cmdnum = i;
	pid[i] = fork();
	if (pid[i] < 0)
		return (pipex_error_handling(pipe_ends, i, 6, pipex_m, true));
	else if (pid[i] == 0)
	{
		pipex_m->compil_res = last_child(pipe_ends, cmd_table, envv, pipex_m);
		if (pipex_m->compil_res != 0)
			return (pipex_free_all(pipex_m, pipe_ends), pipex_m->compil_res);
	}
	// __________
	i = 0;
	while (i < pipex_m->pipenum)
	{
		close (pipe_ends[i][0]);
		close (pipe_ends[i][1]);
		i++;
	}
	free_intarr(pipe_ends, pipex_m->pipenum);
	i = 0;
	while (i < pipex_m->pipenum) // for pid[0] && pid[1];
	{
		waitpid(pid[i], NULL, 0);
		// printf("%d. process arrived out of %d processes \n", i, pipex_m->pipenum); // so process with id = 1 does not arrived
		i++;
	}
	waitpid(pid[i], &(pipex_m->status), 0); // last pipes status code
	return (pipex_free_all(pipex_m, NULL), WEXITSTATUS(pipex_m->status)); // left to free but not here: cmd_table
}

// cc -Wall -Wextra -Werror pipex_multipipe.c pipex_multipipe_interpreter.c finish.c find_cmd.c error.c input_parser_utils.c libft/*.c -lreadline
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./a.out
// int	main(int argc, char **argv, char **envv)
// {
// 	t_pipex_m	pipex_m;
// 	int		**pipe_ends; // 1 pipe
// 	int		i;
// 	int		retval;

// 	if (argv[argc - 1] == NULL)
// 		return (1);
	
// 	// the below is just random numbers/strings for testing, can be deleted as soon as we have cmd_table
// 	//this command works -leak -proof  cat _testfile | wc -l > out
// 	//let's try the command cat _testfile | wc -l | cat >out   vs   cat _testfile | wc -l | wc -l >out
// 	char	***cmd_table;
// 	pipex_m.pipenum = 2; 
// 	cmd_table = (char ***)malloc((pipex_m.pipenum + 1) * 2 * sizeof(char *)); // 2 for (each pipenum + 1) ----> +1 as we start counting from 0
// 	i = 0;
// 	while (i <= pipex_m.pipenum) // 2 commands
// 	{
// 		cmd_table[i] = (char **)malloc(3 * sizeof(char *));
// 		i++;
// 	}
// 	cmd_table[0][0] = "wc -l";
// 	cmd_table[0][1] = "_testfile";
// 	cmd_table[0][2] = NULL;
// 	cmd_table[1][0] = "cat";
// 	cmd_table[1][1] = NULL;
// 	cmd_table[1][2] = NULL;
// 	cmd_table[2][0] = "cat";
// 	cmd_table[2][1] = NULL;
// 	cmd_table[2][2] = "out";
// 	// the above will be defined in parser and set to NULL if they are not specified in cmd

// 	pipe_ends = (int **)malloc(2 * pipex_m.pipenum * sizeof(int)); //2 pipe ends per pipe
// 	i = 0;
// 	while (i < pipex_m.pipenum)
// 	{
// 		pipe_ends[i] = (int *)malloc(2 * sizeof(int));
// 		i++;
// 	}
// 	// if (argc != 5 || (argc == 5 && !(argv[1][0])))
// 	// 	return (pipex_error_handling(NULL, 0, 8, NULL, false));
// 	i = 0;
// 	pipex_m.cmd = NULL;
// 	pipex_m.poss_paths = NULL;
// 	pipex_m.cmdpath = NULL;
// 	pipex_m.poss_path = NULL;
// 	while (i < pipex_m.pipenum)
// 	{
// 		if (pipe(pipe_ends[i]) == -1)
// 			return (pipex_error_handling(pipe_ends, i, 9, NULL, true));
// 		i++;
// 	}
// 	retval = pipex(pipe_ends, cmd_table, envv, &pipex_m);
// 	i = 0;
// 	while (i <= pipex_m.pipenum) // 2 commands
// 		free(cmd_table[i++]);
// 	free(cmd_table);
// 	return (retval);
// }
