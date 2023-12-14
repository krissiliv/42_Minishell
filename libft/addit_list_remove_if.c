/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_list_remove_if.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:25:24 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 14:43:50 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int cmp(void *data1, void *data2)
// {
//     if (*(int *)data1 == *(int *)data2)
//         return (0);
//     return (1);
// }

void	free_listnode(t_list *pos)
{
	free(pos->data);
	free(pos);
}

static t_list	*free_and_resetnode(t_list *pos, t_list *begin_list)
{
	free_listnode(pos);
	return (begin_list);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*pos;
	t_list	*prev;

	pos = *begin_list;
	prev = *begin_list;
	while (pos != NULL)
	{
		while (cmp(pos->data, data_ref) == 0)
		{
			if (cmp((*begin_list)->data, data_ref) == 0)
			{
				*begin_list = (*begin_list)->next;
				pos = free_and_resetnode(pos, *begin_list);
			}
			else
			{
				prev = *begin_list;
				while (prev->next != pos)
					prev = prev->next;
				prev->next = pos->next;
				pos = free_and_resetnode(pos, *begin_list);
			}
		}
		pos = pos->next;
	}
}

// void prntlist(t_list *head)
// {
//     t_list *pos;

//     pos = head;
//     while (pos != NULL) //print original list
//     {
//         printf("%d", *((int*)(pos->data))); 
// 			//have to fix datatype as "int" again
//         if (pos->next != NULL)
//             printf(" -> ");
//         pos = pos->next;
//     }
// }

// int main(void)
// {
//     t_list *head;
//     t_list *pos;    
//     int elements[] = {60, 60, 60, 60, 20, 20, 30, 30, 40, 60, 60, 50}; 
//// wished elements of the list
//     int i = 60;

//     head = create_linked_list(12, elements);
//     prntlist(head);
//     ft_list_remove_if(&head, &i, (*cmp));
//     printf("\n");
//     prntlist(head);
//     free(head);
//     return (0);
// }