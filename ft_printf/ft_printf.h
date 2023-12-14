/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:44:15 by pgober            #+#    #+#             */
/*   Updated: 2023/09/17 17:52:50 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

typedef struct s_bstct
{
	int	incr;
	int	bytes;
}	t_bytest;

typedef struct s_hexsze
{
	int	i;
	int	s;
}	t_hexsize;

int		ft_printf(const char *format, ...);
int		ft_printf_char(char alpha);
int		ft_printf_string(char *str);
int		ft_printf_ptradr(unsigned long int ptr);
void	ft_putnbr_base(long long int nbr, char *base, t_hexsize *bytes);
int		ft_printf_d_int(int nbr);
void	ft_printf_unsdec(unsigned int n);
int		ft_printf_hex_lu(unsigned int ptr, char lu);

#endif
