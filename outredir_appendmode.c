/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outredir_appendmode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:41:28 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 14:06:48 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outredir_appendmode(t_alloc *mllcd, int cmdnum)
{
	int fd;

	fd = open(mllcd->in_pars.cmd_table[cmdnum][4], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		mllcd->exit_status = 1;
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

// cc -Wall -Wextra -Werror outredir_appendmode.c expander.c input_parser.c input_parser_ft_split_w_quotes.c input_parser_utils.c finish.c libft/*.c -lreadline -g
// valgrind --leak-check=full --show-leak-kinds=all -s ./a.out
// int main(int argc, char **argv)
// {
// 	char	*input_str;
// 	t_alloc	mllcd;

// 	if (!(*argv)[argc - 1])
// 		return (1);
// 	input_str = ft_strdup("cat EXTRA/EXTRA_progress_tracking >> _testfile"); //fill in stuff from EXTRA/input_parser_testing
// 	 // while (1)
// 	 // {
// 		 // input_str = read_input_print_prompt();
		
// 	 if (expander(&input_str, &mllcd))
//         return (1);
//     // printf("input_str expanded: %s\n", input_str);

//     if (cmdline_input_parser(&mllcd.in_pars, input_str))
//         return (1);
//     free(input_str);
//     int i = -1;
//     while (i++ < mllcd.in_pars.m_argc)
//     {
// 		printf("m_argv[%d] = %s\n", i, mllcd.in_pars.m_argv[i]);
// 	}

// 	if (mllcd.in_pars.cmd_table[0][4])
// 		outredir_appendmode(&mllcd);

// 	free_strstr(mllcd.in_pars.m_argv);
// 	free_cmd_table(&mllcd.in_pars);
// 	// }
// 	return (0);
// }