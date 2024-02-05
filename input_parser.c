/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:05:03 by pgober            #+#    #+#             */
/*   Updated: 2024/02/05 17:21:44 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_input_parser(t_input_parsing *in_pars, char *input_str)
{
	int		i;
	int		j;
	bool 	singlequote_open;
	bool 	doublequote_open;
	// char	**test_m_argv;

	singlequote_open = false;
	doublequote_open = false;
	in_pars->pipenum = 0;
	// test_m_argv = ft_split_w_quotes(input_str, ' '); // this is wrong as f.e. the cmd grep "ho" | < _test does not work in bash eigther
	// if ((ft_strcmp(test_m_argv[0], "<") == 0 || 
	// 	ft_strcmp(test_m_argv[0], ">") == 0) && 
	// 	test_m_argv[2] && ft_strcmp(test_m_argv[2], "|") == 0) // If there is just "< infile" in front of the first pipe, then pipenum-- as the first pipe is not needed/counted
	// 	in_pars->pipenum--;
	// if (ft_strcmp(in_pars->input_str, ">") == 0 && ft_strcmp(in_pars->input_str, "|") != 0)
	// 	in_pars->pipenum++;
	// free_strstr(test_m_argv);
	while (*input_str)
	{
		if (*input_str == '\"' && singlequote_open == false)
			doublequote_open = !doublequote_open;
		if (*input_str == '\'' && doublequote_open == false)
			singlequote_open = !singlequote_open;
		if (*input_str == '|' && singlequote_open == false && doublequote_open == false)
			in_pars->pipenum++;
		input_str++;
	}
	//printf("true (needed) pipenum = %d\n", in_pars->pipenum); //first pipe excluded as "< infile | cat | wc -l > out" can be re-written as cat infile | wc -l > out
	in_pars->m_argc = 0;
	in_pars->m_argv = NULL;
	in_pars->cmd_table = (char ***)malloc((in_pars->pipenum + 1) * 5 * sizeof(char *));  // in_pars->pipenum commands
	i = 0;
	while (i <= in_pars->pipenum) // just these strings for testing
	{
		in_pars->cmd_table[i] = (char **)malloc(5 * sizeof(char *));
		j = 0;
		while (j <= 4)
			in_pars->cmd_table[i][j++] = NULL;
		i++;
	}
	in_pars->cmd_table[i] = NULL;
	in_pars->doublequote_open = false;
	in_pars->singlequote_open = false;
}

static int	look_for_free_spot_in_cmdtable(t_input_parsing *in_pars, int curr_cmdnum, int i)
{
	if (in_pars->cmd_table[curr_cmdnum][0] == NULL)
	{
		in_pars->cmd_table[curr_cmdnum][0] = ft_strdup(in_pars->m_argv[i]);
		if (in_pars->m_argv[i + 1] && in_pars->m_argv[i + 1][0] == '-' && ft_strlen(in_pars->m_argv[i]) > 1)
		{
			in_pars->cmd_table[curr_cmdnum][0] = ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], " ");
			in_pars->cmd_table[curr_cmdnum][0] = ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], in_pars->m_argv[++i]);
		}
	}
	else if (in_pars->m_argv[i] && special_operator(in_pars->m_argv[i]) == -1)
	{
		while (in_pars->m_argv[i] && special_operator(in_pars->m_argv[i]) == -1)
			in_pars->cmd_table[curr_cmdnum][0] = ft_strjoin_w_free(ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], " "), in_pars->m_argv[i++]);
		i--; // bc argv[i] was not processed yet
	}
	else if (in_pars->cmd_table[curr_cmdnum][1] == NULL)
		in_pars->cmd_table[curr_cmdnum][1] = ft_strdup(in_pars->m_argv[i]);
	else if (in_pars->cmd_table[curr_cmdnum][2] == NULL)
		in_pars->cmd_table[curr_cmdnum][1] = ft_strdup(in_pars->m_argv[i]);
	else
		return (ft_putstr_fd("Error: too many arguments\n", 2), -1);
	return (i);
}

static int processing_read(t_input_parsing *in_pars)  // here in_pars->cmd_table is filled with in_pars->m_argv
{
	int i;
	int curr_cmdnum;
	//int cmd_position;

	i = 0;
	curr_cmdnum = 0;
	//cmd_position = 0;
	while (i < in_pars->m_argc) // next step: need to find way to fill "r" next to grep
	{
		// if (in_pars->m_argv[i][0] == '\"' || in_pars->m_argv[i][0] == '\'') // not finished yet but work on it a little later as it is not in current command "< infile | cat | wc -l > out"
		// {
		// 	i = look_for_free_spot_in_cmdtable(in_pars, curr_cmdnum, i);
		// 	if (i == -1)
		// 		return (1);
		// 	// if (in_pars->cmd_table[curr_cmdnum][0] == NULL)
		// 	// 	cmd_position = 0;
		// 	// else if (in_pars->cmd_table[curr_cmdnum][1] == NULL)
		// 	// 	cmd_position = 1;
		// 	// else if (in_pars->cmd_table[curr_cmdnum][2] == NULL)
		// 	// 	cmd_position = 2;
		// 	// else
		// 	// {
		// 	// 	ft_putstr_fd("Error: too many arguments\n, 2");
		// 	// 	return (1);
		// 	// } //problem to solve: what is in between the quotes can be a command or an argument (filename)...	
		// 	// if (ft_strlen(in_pars->m_argv[i]) > 1)
		// 	// {
		// 	// 	if (ft_strcmp(in_pars->cmd_table[curr_cmdnum][0], "grep") == 0 || ft_strcmp(in_pars->cmd_table[curr_cmdnum][0], "\"grep\"") == 0 || ft_strcmp(in_pars->cmd_table[curr_cmdnum][0], "\'grep\'") == 0) // grep is the only cmd that needs/takes a string as an argument, right?? no?
		// 	// 		in_pars->cmd_table[curr_cmdnum][0] = ft_strjoin_w_free(ft_strjoin_w_free(in_pars->cmd_table[curr_cmdnum][0], " "), in_pars->m_argv[i]);
		// 	// 	else
		// 	// 		in_pars->cmd_table[curr_cmdnum][cmd_position] = ft_strdup(in_pars->m_argv[i]); //done: what if quote closure is included in this string as well?? --> handled with ft_split_w_quotes
		// 	// }
		// }
		if ((ft_strcmp(in_pars->m_argv[i], "<") == 0)) // && inside_qu(in_pars) == false)) // input redirection <
			in_pars->cmd_table[curr_cmdnum][1] = ft_strdup(in_pars->m_argv[++i]); // input file should not generally be in first position in a-s-t (abstract synax tree) - it should be on first position of the resp command that it belongs to as it should mimic shell
		// else if (i == 1 && ft_strchr(in_pars->input_str, (int)'<') == NULL && ft_strcmp(in_pars->m_argv[1], "|") != 0) // no input redirection
		// {
		// 	//printf("%d", i); // ls > out   vs. cat infile | wc -l > out
		// 	if (ft_strcmp(in_pars->m_argv[i], ">") == 0)
		// 		in_pars->cmd_table[0][2] = ft_strdup(in_pars->m_argv[++i]);
		// 	else
		// 		in_pars->cmd_table[0][1] = ft_strdup(in_pars->m_argv[i]); // input file should be in first position in a-s-t (abstract synax tree)
		// }
		else if (ft_strcmp(in_pars->m_argv[i], ">") == 0) // && inside_qu(in_pars) == false) // output redirection >
			in_pars->cmd_table[curr_cmdnum][2] = ft_strdup(in_pars->m_argv[++i]); // output file should not generally be in last position in a-s-t (abstract synax tree) - it should be on last position of the resp command that it belongs to as it should mimic shell
		else if (ft_strncmp(in_pars->m_argv[i], "<<", 2) == 0) // input reading until delimiter
		{
			if (ft_strlen(in_pars->m_argv[i]) == 2)
				in_pars->cmd_table[curr_cmdnum][3] = ft_strdup(in_pars->m_argv[++i]);
			else
				in_pars->cmd_table[curr_cmdnum][3] = ft_strtrim(ft_strdup(in_pars->m_argv[i++] + 2), "\"\'");
		}
		else if (ft_strcmp(in_pars->m_argv[i], ">>") == 0)
			in_pars->cmd_table[curr_cmdnum][4] = ft_strdup(in_pars->m_argv[++i]);
		else if (ft_strcmp(in_pars->m_argv[i], "|") == 0 && in_pars->m_argv[i + 1])
		{
			if (in_pars->cmd_table[curr_cmdnum][0] == 0)
				curr_cmdnum--; //so that we proceed with same cmd as we will increase it in the next step
		}
		else if (in_pars->m_argv[i] != NULL) // && curr_cmdnum <= in_pars->pipenum)
		{
			i = look_for_free_spot_in_cmdtable(in_pars, curr_cmdnum, i);
			if (i == -1)
				return (1);
		}
		if (in_pars->m_argv[i] && ft_strcmp(in_pars->m_argv[i], "|") == 0)
			curr_cmdnum++;
		i++;
	}
	return (0);  // next step: 
}

static void 	remove_quotes_from_cmd_table(t_input_parsing *in_pars)
{
	int i;
	int j;

	i = 0;
	while (i <= in_pars->pipenum)
	{
		j = 1;
		while (j <= 4)
		{
			if (in_pars->cmd_table[i][j])
				in_pars->cmd_table[i][j] = ft_remove_quotes(in_pars->cmd_table[i][j]);
			j++;
		}
		i++;
	}
}

int	cmdline_input_parser(t_input_parsing *in_pars, char *input_str)
{
	if (!input_str || ft_strlen(input_str) == 0)
		return (ft_putstr_fd("Error: Input parser did nnnnot receive input.\n", 2), 1);
	
	in_pars->input_str = input_str;
	init_input_parser(in_pars, input_str);
	in_pars->m_argc = count_words(input_str, ' ');
	//printf("m_argc = %d\n", m_argc);
	in_pars->m_argv = ft_split_w_quotes(input_str, ' ');

	// int i = 0;
	// while (i < in_pars->m_argc)
	// {
	// 	printf("m_argv[%d] = %s\n", i, in_pars->m_argv[i]);
	// 	i++;
	// }

	if (processing_read(in_pars))
		return (1);

	remove_quotes_from_cmd_table(in_pars);
	
	// free(input_str);
	return (0);
}

// cc -Wall -Wextra -Werror input_parser.c input_parser_ft_split_w_quotes.c finish.c input_parser_utils.c libft/*.c -g -lreadline
// valgrind --leak-check=full --show-leak-kinds=all -s ./a.out 
// int main(void) // will later be parsing tester
// {
// 	t_input_parsing in_pars;
// 	int			 i;  
// 	char	*input_str;

// 	input_str = "cat << h < _testfile >> out"; //fill in stuff from EXTRA/input_parser_testing
// 	// input_str = read_input_print_prompt(); 
// 	if (cmdline_input_parser(&in_pars, input_str))
// 		return (1);
// 	i = 0;
// 	while (i < in_pars.m_argc)
// 	{
// 		printf("m_argv[%d] = %s\n", i, in_pars.m_argv[i]);
// 		i++;
// 	}
// 	free_strstr(in_pars.m_argv);
// 	free_cmd_table(&in_pars);
// }



/*
What can the input look like acc to subject?
Generally, we have to implement command lines like the examples in "general_research_input".

command -option argument

command < input_file

command > output_file

command < input_file > output_file

command >> output_file

command1 | command2

command1 -option1 argument1 | command2 -option2 argument2

cat file.txt | grep "pattern" | sort | uniq

cat data.log | awk '{print $2}' | sed 's/error/ERROR/g'

echo "This is a quoted string"
echo 'Another quoted string with $variable'

cat < input_file                    # Redirecting input from a file
echo "Hello" > output_file          # Redirecting output to a file
echo "Appending" >> output_file     # Redirecting output in append mode
cat <<EOF                           # Here document
This is a multiline
text block.
EOF

echo "PATH is $PATH" | grep "bin"

command1 | command2
echo "Exit status: $?"

*/