/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_list_printer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:42:09 by pgober            #+#    #+#             */
/*   Updated: 2024/04/03 12:00:00 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	prntlist_int(t_list *head)
{
	t_list	*pos;

	pos = head;
	while (pos != NULL)
	{
		ft_putnbr_fd(*((int *)(pos->data)), 1);
		if (pos->next != NULL)
			ft_putstr_fd(" -> ", 1);
		pos = pos->next;
	}
}

void	prntlist_char(t_charlist *head)
{
	t_charlist	*pos;

	pos = head;
	while (pos != NULL)
	{
		ft_putstr_fd(((char *)(pos->data)), 1);
		if (pos-> next != NULL)
			ft_putstr_fd(" -> ", 1);
		pos = pos->next;
	}
}
