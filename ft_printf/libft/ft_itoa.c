/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:08:33 by pgober            #+#    #+#             */
/*   Updated: 2023/09/11 16:42:38 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numsize(int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		while (nbr <= -10)
		{
			nbr /= 10;
			i++;
		}
		i++;
	}
	else
	{
		while (nbr >= 10)
		{
			nbr /= 10;
			i++;
		}
	}
	return (i);
}

static char	*anumcreator(char *str, int i, int minus, int n)
{
	str[i] = '\0';
	if (n < 0)
		n = -n;
	while (i-- > minus)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
	}
	if (minus == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		minus;

	minus = 0;
	i = numsize(n);
	if (n < 0)
		minus = 1;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", numsize(-2147483648) * sizeof(int));
	else
		str = anumcreator(str, i, minus, n);
	return (str);
}

/*int	main(void)
{
	int len = 0;
	char	*res = ft_itoa(2147483647);
    
	//printf("%d\n", numsize(-147483648));
	//printf("%d\n", numsize(-1));
	//printf("%d\n", numsize(1));
	//printf("%d\n", numsize(15));
	//return 0;

	len = 0;
	while (res[len])
		len++;
	write(1, res, len);
}*/
