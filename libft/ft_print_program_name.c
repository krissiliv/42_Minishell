/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:16:02 by pgober            #+#    #+#             */
/*   Updated: 2023/12/14 15:32:26 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_program_name(int argc, char *argv[])
{
	write(1, argv[argc - 1], ft_strlen(argv[argc - 1]));
	write(1, "\n", 1);
}
