
#include "libft.h"

int str_is_empty(char *str)
{
	int i;
	int check_only_spaces;

	if (!str || ft_strlen(str) == 0)
		return (1);
	i = 0;
	check_only_spaces = 1;
	while (str[i])
	{
		if (!is_space(str[i++]))
			check_only_spaces = 0;
	}
	if (check_only_spaces)
		return (1);
	return (0);
}