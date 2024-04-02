/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:20 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 13:49:50 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_multipipe.h"
#include "minishell.h"

static int	multi_execute_interpreter(t_alloc *mllcd)
{
	int c;
	int in;
	int out;

    mllcd->pipex_m.cmd = ft_split_w_quotes(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][0], ' '); // on the cmd-position 0 there is always the command
	if (!(mllcd->pipex_m.cmd) || !(mllcd->pipex_m.cmd[0]) || !(mllcd->pipex_m.cmd[0][0]))
		return (1);
	c = 0; // now remove "" from everywhere
	while (mllcd->pipex_m.cmd[c] && c < 6)
	{
		mllcd->pipex_m.cmd[c] = ft_remove_quotes(mllcd->pipex_m.cmd[c]);
		c++;
	}

    // printf("cmd = ["); // PRINTING FOR DEBUGGING
    // int i = -1;
    // while ((mllcd->pipex_m.cmd)[++i])
    //     printf("%s,", (mllcd->pipex_m.cmd)[i]);
    // printf("]\n"); //printf("should be: (char *[]){\"grep\",\"ho\",\"_testfile\", NULL}\n");

	in = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1]) // input redirection
    {
        in = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1], O_RDONLY);
        if (in == -1 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL)
            return (pipex_error_handling(2, &mllcd->pipex_m));
        if (in != -1 && dup2(in, 0) == -1) //the stdin will always be the in
        {
            close(in);
            return (pipex_error_handling(4, &mllcd->pipex_m));
        }
    }

	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2]) // input redirection
    {
		out = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2], O_WRONLY | O_CREAT | O_TRUNC, 0777); // on the 2nd position of the last command there will always be what is interpreted as the outfile by the parser
		if (out == -1 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2] != NULL)
			return (pipex_error_handling(10, &mllcd->pipex_m));
		if (out != -1 && dup2(out, 1) == -1) //the stdout will always be the outfile
		{
			close(out);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
	}

	return (0);
}

static int	execute(int **pipe_ends, t_alloc *mllcd)
{
	char	**envv;
	int		res;

	if (multi_execute_interpreter(mllcd))
		return (ft_lstclear(&mllcd->env_list), pipex_free_all(&mllcd->pipex_m, pipe_ends), 1);

	envv = convert_linkedlst_to_table(mllcd);
	// ft_lstclear(&mllcd->env_list);
	res = builtins_all(mllcd->pipex_m.cmd, mllcd);
	if (res != -1) // printf("res: %d\n", res), perror("builtins in pipes"), 
		return (free_env_table(envv), free_strstr(mllcd->pipex_m.cmd), res);
	
	mllcd->pipex_m.cmdpath = find_cmd_path(mllcd->pipex_m.cmd[0], envv, &mllcd->pipex_m);
	if (mllcd->pipex_m.cmdpath == NULL)
	{
		// mllcd->pipex_m.cmdpath = mllcd->pipex_m.cmd[0];
		free_env_table(envv);
		return (pipex_error_handling(127, &mllcd->pipex_m));
	}
	if (access(mllcd->pipex_m.cmdpath, F_OK) != 0)
		return (free_env_table(envv), free_strstr(mllcd->pipex_m.cmd), pipex_error_handling(127, &mllcd->pipex_m));
	if (access(mllcd->pipex_m.cmdpath, F_OK) == 0 && \
		access(mllcd->pipex_m.cmdpath, X_OK) != 0)
		return (free_env_table(envv), free_strstr(mllcd->pipex_m.cmd), pipex_free_all(&mllcd->pipex_m, pipe_ends), \
				pipex_error_handling(126, &mllcd->pipex_m));

	// printf("cmdpath: %s\n", mllcd->pipex_m.cmdpath);
	if (execve(mllcd->pipex_m.cmdpath, mllcd->pipex_m.cmd, envv) == -1)
		return (free_env_table(envv), free_strstr(mllcd->pipex_m.cmd), pipex_error_handling(3, &mllcd->pipex_m));
	return (free_env_table(envv), free_strstr(mllcd->pipex_m.cmd), ft_putstr_fd("Something went wrong", 2), pipex_free_all(&mllcd->pipex_m, pipe_ends), 0);
}

int	child(int **pipe_ends, t_alloc *mllcd)
{
	int	cmd_file;
	int i;

	//printf("entered child %d\n", mllcd->pipex_m.cmdnum);
	cmd_file = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL) //on cmd-position 1 there is always sth that is believed to be a file
		cmd_file = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1], O_RDONLY);
	if (cmd_file == -1 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL) // I would set the filename of mllcd->in_pars.cmd_table[cmdnum][1] to NULL if the cmd doesn't have a file
		return (pipex_error_handling(1, &mllcd->pipex_m));
	//printf("in child %d, the cmd is %s and the file is %s\n", mllcd->pipex_m.cmdnum, mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][0], mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1]);
	// what is the stdin of my child? if cmdnum == 0, then if is probably a file, if it is not a file then it can be stdin as f.e. here: ls | cat > out
	if (mllcd->pipex_m.cmdnum == 0 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1] != NULL) // turn file into stdin
	{
		if (dup2(cmd_file, 0) == -1) //turn file into stdin
		{
			close(cmd_file);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
		//printf("in child %d, made %s to stdin\n", mllcd->pipex_m.cmdnum, mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][1]);
	}
	else if (mllcd->pipex_m.cmdnum != 0)
	{
		if (dup2(pipe_ends[mllcd->pipex_m.cmdnum - 1][0], 0) == -1) //turn reading pipeend into stdin
		{
			close(cmd_file);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
		//printf("in child %d, made pipe_ends[%d][0] to stdin\n", mllcd->pipex_m.cmdnum, mllcd->pipex_m.cmdnum - 1);
	}
	// what is the stdout of my child? since for cmdnum == pipenum there is an other child, for this child the stdout will always be the pipeend to the next child 
	//printf("in child %d dup made pipe_ends[%d][1] to stdout ...\n", mllcd->pipex_m.cmdnum, mllcd->pipex_m.cmdnum);
	if (dup2(pipe_ends[mllcd->pipex_m.cmdnum][1], 1) == -1) // turn writing pipeend into stdout
		return (pipex_error_handling(1, &mllcd->pipex_m));
	//printf("in child %d made pipe_ends[%d][1] to stdout\n", mllcd->pipex_m.cmdnum, mllcd->pipex_m.cmdnum);
	i = 0;
	while (i < mllcd->pipex_m.pipenum)
	{
		close (pipe_ends[i][0]);
		close (pipe_ends[i][1]);
		i++;
	}
	if (pipe_ends)
	{
		free_intarr(pipe_ends, mllcd->pipex_m.pipenum);
		pipe_ends = NULL;
	}
	if (cmd_file != -1)
		close(cmd_file);
	i = execute(pipe_ends, mllcd);
	free_before_exit(mllcd, true);
	exit(i);
}
// when you call the pipe syscall like pipe(array), then array[0] is for reading and array[1] is for writing.

int	last_child(int **pipe_ends, t_alloc *mllcd)
{
	int	outfile;
	int i;

	//printf("last child ->opening %s\n", mllcd->in_pars.[pipex_m->cmdnum][2]);
	outfile = -1;
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2])
	{
		outfile = open(mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2], O_WRONLY | O_CREAT | O_TRUNC, 0777); // on the 2nd position of the last command there will always be what is interpreted as the outfile by the parser
		if (outfile == -1 && mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2] != NULL)
			return (pipex_error_handling(10, &mllcd->pipex_m));
		if (outfile != -1 && dup2(outfile, 1) == -1) //the stdout will always be the outfile
		{
			close(outfile);
			return (pipex_error_handling(4, &mllcd->pipex_m));
		}
	}
	if (mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][4])
	{
		if (outredir_appendmode(mllcd, mllcd->pipex_m.cmdnum))
			return (pipex_error_handling(10, &mllcd->pipex_m));
	}
	//printf("in child %d make %s to stdout\n", mllcd->pipex_m.cmdnum, mllcd->in_pars.cmd_table[mllcd->pipex_m.cmdnum][2]);
	if (dup2(pipe_ends[mllcd->pipex_m.cmdnum - 1][0], 0) == -1) //for last child, the stdin will always be the reading pipeend to the last child
		return (pipex_error_handling(1, &mllcd->pipex_m));
	//printf("in child %d, made pipe_ends[%d][0] to stdin\n", mllcd->pipex_m.cmdnum, mllcd->pipex_m.cmdnum - 1);
	i = 0;
	while (i < mllcd->pipex_m.pipenum)
	{
		close(pipe_ends[i][0]);
		close(pipe_ends[i][1]);
		i++;
	}
	if (pipe_ends)
	{
		free_intarr(pipe_ends, mllcd->pipex_m.pipenum);
		pipe_ends = NULL;
	}
	if (outfile != -1)
		close(outfile);
	i = execute(pipe_ends, mllcd);
	free_before_exit(mllcd, true);
	exit(i);
}

int	pipex(int **pipe_ends, t_alloc *mllcd)
{
	int	i;
	int	pid[mllcd->pipex_m.pipenum + 1];

	i = 0;
	mllcd->pipex_m.status = 0;
	while (i < mllcd->pipex_m.pipenum) // within each pipe there is one command => the number of the cmd < pipenum and the last command is pipenum
	{
		mllcd->pipex_m.cmdnum = i;
		signals(2);
		pid[i] = fork();
		if (pid[i] < 0)
			return (pipex_error_handling(6, &mllcd->pipex_m));
		else if (pid[i] == 0) // means we are in child process number i
		{
			//signals(3);
			//printf("created child %d with compil res %d\n", i, mllcd->pipex_m.compil_res);
			mllcd->pipex_m.compil_res = child(pipe_ends, mllcd);
			if (mllcd->pipex_m.compil_res != 0)
				return (pipex_free_all(&mllcd->pipex_m, pipe_ends), mllcd->pipex_m.compil_res);
			// i = 0;
			// while (i < mllcd->pipex_m.pipenum)
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
	mllcd->pipex_m.cmdnum = i;
	signals(2);
	pid[i] = fork();
	if (pid[i] < 0)
		return (pipex_error_handling(6, &mllcd->pipex_m));
	else if (pid[i] == 0)
	{
		//signals(2);
		mllcd->pipex_m.compil_res = last_child(pipe_ends, mllcd);
		if (mllcd->pipex_m.compil_res != 0)
			return (pipex_free_all(&mllcd->pipex_m, pipe_ends), mllcd->pipex_m.compil_res);
	}
	// __________
	i = 0;
	while (i < mllcd->pipex_m.pipenum)
	{
		close (pipe_ends[i][0]);
		close (pipe_ends[i][1]);
		i++;
	}
	free_intarr(pipe_ends, mllcd->pipex_m.pipenum);
	i = 0;
	while (i < mllcd->pipex_m.pipenum) // for pid[0] && pid[1];
	{
		waitpid(pid[i], NULL, 0);
		// printf("%d. process arrived out of %d processes \n", i, mllcd->pipex_m.pipenum); // so process with id = 1 does not arrived
		i++;
	}
	waitpid(pid[i], &(mllcd->pipex_m.status), 0); // last pipes status code
	/* if (WIFSIGNALED(mllcd->simple_cmd.compil_res))
		mllcd->exit_status = WTERMSIG(mllcd->simple_cmd.compil_res);
	else */
	mllcd->exit_status = WEXITSTATUS(mllcd->pipex_m.status);
	return (pipex_free_all(&mllcd->pipex_m, NULL), mllcd->exit_status); // left to free but not here: mllcd->in_pars.cmd_table
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
