/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creater.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:04:36 by pgober            #+#    #+#             */
/*   Updated: 2024/01/05 12:41:14 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_ast_creater.h"

// cc -Wall -Wextra -Werror *.c ../libft/ft_strdup.c ../libft/ft_strlen.c ../finish.c ../libft/addit_free_arr.c ../libft/ft_putstr_fd.c ../libft/ft_putnbr_fd.c ../libft/ft_putchar_fd.c -lreadline -g

void    list_add_branches(t_ast *head, char ***cmd_table) 
{
    t_ast	*pos;
    t_ast	*branch;
	int		i;
	int		j;

    pos = head;
	// first branch is added manually to the 0. node (as this is the only node that has two branches)
	pos->first_branch = (t_ast *)malloc(sizeof(t_ast));
	if (pos->first_branch == NULL) 
		return ;
	pos->first_branch->bdata = (char **)malloc(3 * sizeof(char *));
	j = -1;
	while (++j < 2)
		pos->first_branch->bdata[j] = ft_strdup(cmd_table[0][j]);
	i = 1; // go on with second branch
    while (pos != NULL)
    {
        branch = (t_ast *)malloc(sizeof(t_ast));
        if (branch == NULL) 
            return ;
		j = -1;
		branch->bdata = (char **)malloc(3 * sizeof(char *));
		while (++j < 2)
        	branch->bdata[j] = ft_strdup(cmd_table[i][j]); //made tree into a duplicate of cmd_table so that if I free tree, I have to/can free cmd_table independently
		branch->bdata[j] = NULL;
        branch->next = NULL;
        pos->branch = branch;
        pos = pos->next;
		i++;
    }
}

t_ast *create_ast(int listlen, char **elements, char ***cmd_table) // create linked list of nodes, each node containing the string "pipe" and a branch is added using list_add_branches(head, cmd_table); 
{
    t_ast	*head; //initial node
    t_ast	*temp; //temporal node at appropriate position
    t_ast	*pos; //for adding node at correct position
    int		i;

	head = NULL;
    temp = NULL;
    pos = NULL;
    i = 0;
    while (i < listlen)
    {
        temp = (t_ast *)malloc(sizeof(t_ast)); //allocate memory for a node in the list
        temp->data = ft_strdup(elements[i]);
        temp->next = NULL;

        if (head == NULL) //if list is empty
            head = temp; //make temp the first node
        else //add newly created node to non-empty list
        {
            pos = head;
            while (pos->next != NULL) //while the end of the list is not reached
                pos = pos->next; //take one (positional) step
            pos->next = temp; //attach newly created node to the end
        }
        i++;
    } 
    list_add_branches(head, cmd_table); // now to each node of the list, a branch [cmd -option, file] is added
    return (head);
}

int main(void)
{
    t_pipex_m pipex_m;
    t_ast *head;
    char **elements; //wished elements of the list
    int     i;

	// the below is just random numbers/strings for testing, can be deleted as soon as we have cmd_table
	char ***cmd_table;
    pipex_m.pipenum = 10;
	cmd_table = (char ***)malloc((pipex_m.pipenum + 1) * 3 * sizeof(char *));  // pipex_m.pipenum commands
	i = 0;
	while (i <= pipex_m.pipenum) // just these strings for testing
	{
		cmd_table[i] = (char **)malloc(3 * sizeof(char *));
		cmd_table[i][0] = "cmd -option";
		cmd_table[i][1] = "file";
		cmd_table[i][2] = NULL;
		i++;
	}
	cmd_table[i] = NULL;
	// the above will be defined in parser and set to NULL if they are not specified in cmd
	
    elements = (char **)malloc((pipex_m.pipenum + 1) * sizeof(char *)); // pipex_m.pipenum pipes
    i = 0;
    while (i < pipex_m.pipenum)
        elements[i++] = ft_strdup("pipe");
    elements[i] = NULL;
    head = create_ast(pipex_m.pipenum, elements, cmd_table);

    prnt_ast(head);

	// free everything to check valgrind already
    free_ast(head);
    free_strstr(elements);
	i = 0;
	while (i <= pipex_m.pipenum)
		free(cmd_table[i++]);
	free(cmd_table);
    return (0);
}