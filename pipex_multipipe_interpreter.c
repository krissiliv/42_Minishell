/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_multipipe_interpreter.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:06:55 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 10:41:33 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_pipex_multipipe(t_alloc *mllcd, int argc, char **argv)
{
	int		**pipe_ends; // 1 pipe
	int		i;

	if (argv[argc - 1] == NULL)
		return (1);
	
	// the below is just random numbers/strings for testing, can be deleted as soon as we have cmd_table
	//this command works -leak -proof  cat _testfile | wc -l > out
	//let's try the command cat _testfile | wc -l | cat >out   vs   cat _testfile | wc -l | wc -l >out
	// char	***cmd_table;
	// mllcd->pipex_m.pipenum = 2; 
	// cmd_table = (char ***)malloc((mllcd->pipex_m.pipenum + 1) * 2 * sizeof(char *)); // 2 for (each pipenum + 1) ----> +1 as we start counting from 0
	// i = 0;
	// while (i <= mllcd->pipex_m.pipenum) // 2 commands
	// {
	// 	cmd_table[i] = (char **)malloc(2 * sizeof(char *));
	// 	i++;
	// }
	// cmd_table[0][0] = "cat";
	// cmd_table[0][1] = "_testfile";	
	// cmd_table[1][0] = "wc -l";
	// cmd_table[1][1] = NULL;
	// cmd_table[2][0] = "cat"; 
	// cmd_table[2][1] = "out"; // changes position of this to be cmd_table[i][2]
	// the above will be defined in parser and set to NULL if they are not specified in cmd

    mllcd->pipex_m.pipenum = mllcd->in_pars.pipenum;
	pipe_ends = (int **)malloc(2 * mllcd->pipex_m.pipenum * sizeof(int)); //2 pipe ends per pipe
	if (!pipe_ends)  //correct??
		return (pipex_error_handling(NULL, 0, 9, NULL));
	i = 0;
	while (i < mllcd->pipex_m.pipenum)
	{
		pipe_ends[i] = (int *)malloc(2 * sizeof(int));
		if (!pipe_ends[i])
			return (pipex_error_handling(pipe_ends, i, 9, NULL));
		i++;
	}
	// if (argc != 5 || (argc == 5 && !(argv[1][0])))
	// 	return (pipex_error_handling(NULL, 0, 8, NULL, false));
	i = 0;
	mllcd->pipex_m.cmd = NULL;
	mllcd->pipex_m.poss_paths = NULL;
	mllcd->pipex_m.cmdpath = NULL;
	mllcd->pipex_m.poss_path = NULL;
	while (i < mllcd->pipex_m.pipenum)
	{
		if (pipe(pipe_ends[i]) == -1)
			return (pipex_error_handling(pipe_ends, i, 9, NULL));
		i++;
	}
	// i = 0; // done in main.c
	// while (i <= mllcd->pipex_m.pipenum) // 2 commands
	// 	free(cmd_table[i++]);
	// free(cmd_table);
	return (pipex(pipe_ends, mllcd));
}


// cmdline_interpreter looked as follows:
// void    cmdline_input_parser(t_input_parsing *in_pars)
// {
//     char    *input_str;
//    
//     input_str = read_input_print_prompt(); // memory leaks due to readline (not to worry about for us)
//     in_pars->m_argc = wordcount(input_str);
//     //printf("m_argc = %d\n", m_argc);
//     in_pars->m_argv = ft_split(input_str, ' ');
//     free(input_str);
// }

// int	main(int argc, char **argv, char **envv) // can call this pipex_interpreter later and say pipex_interpreter(node 1, node 2) of list where node = [cmd, option, argument]
// {
// 	int				pipe_ends[2];
// 	t_pipex_m			pipex_m;
// 	t_input_parsing	in_pars;
// 	int				err;
//
// 	if (!argv[argc - 1]) // just to avoid unused var error
// 		return (0);
// 	while (1)
// 	{
// 		cmdline_input_parser(&in_pars);
// 		if (in_pars.m_argc != 4 || (in_pars.m_argc == 4 && !(in_pars.m_argv[0][0])))
// 			return (general_free_all(in_pars.m_argv), pipex_error_handling(pipe_ends, 8, NULL, false));
// 		// i = 0;
// 		// while (in_pars.m_argv[i])
// 		// {
// 		// 	printf("%s\n", in_pars.m_argv[i]);
// 		//  	i++;
// 		// }
// 		err = pipex_init(pipe_ends, in_pars.m_argc, in_pars.m_argv, &pipex_m);
// 		if (err == 0)
// 			pipex(pipe_ends, in_pars.m_argv, envv, &pipex_m);
// 	}
// 	return (general_free_all(in_pars.m_argv), 0);
// }

