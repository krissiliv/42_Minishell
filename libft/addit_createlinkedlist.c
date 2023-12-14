/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_createlinkedlist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:22:15 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 14:39:36 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*create_linked_list(int listlen, int *elements)
{
	int		i;
	t_list	*head;
	t_list	*temp;
	t_list	*pos;

	i = 0;
	head = NULL;
	pos = NULL;
	while (i < listlen)
	{
		temp = (t_list *)malloc(sizeof(t_list));
		temp->data = malloc(sizeof(int));
		*((int *)(temp->data)) = elements[i++];
		temp->next = NULL;
		if (head == NULL)
			head = temp;
		else
		{
			pos = head;
			while (pos->next != NULL)
				pos = pos->next;
			pos->next = temp;
		}
	}
	return (head);
}

// int main(void)
// {
//     t_list *head = NULL;
//     int elements[] = {1,2,3,4,5}; //wished elements of the list
//     t_list *pos;

//     head = create_linked_list(5, elements);

//     pos = head;
//     while (pos != NULL) //print list
//     {
//         printf("%d", *((int*)(pos->data)));
//         if (pos-> next != NULL)
//             printf(" -> ");
//         pos = pos->next;
//     }
//     free(head);
//     return (0);
// }