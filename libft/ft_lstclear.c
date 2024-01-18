/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:14:21 by apashkov          #+#    #+#             */
/*   Updated: 2024/01/18 17:13:52 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!del || !lst || !*lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		if ((*lst)->malloced == true)
			free((*lst)->env_var);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
