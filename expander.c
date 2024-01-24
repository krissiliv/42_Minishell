/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:53:42 by pgober            #+#    #+#             */
/*   Updated: 2024/01/24 13:42:58 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_dollar_sign(char *str, int starting_pt)
{
	int i;

	i = starting_pt;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] != ' ')
			return (i);
		i++;
	}
	return (-1);
}

char	*find_envvar_value(char *envvar, t_alloc *mllcd)
{
	t_env	*pos;
	int		len;

	if (ft_strcmp(envvar, "?") == 0)
		return (ft_itoa(mllcd->exit_status));
    pos = mllcd->env_list;
	len = ft_strlen(envvar);
    while (pos != NULL && ft_strncmp(pos->env_var, envvar, len) != 0)
    {
		pos = pos->next;
	}
	if (pos != NULL && ft_strncmp(pos->env_var, envvar, len) == 0)
		return (ft_strdup(pos->env_var + len + 1)); // + 1 to jump over "="
	return (ft_strdup("\n"));
}

static int	replace_dollar_sign(char **input_str, int dsign, t_alloc *mllcd)
{
	char	*new_str;
	char	*envvar;
	char	*envvar_value;
	int		i;
	int		j;

	// here it is already clear that there is sth after the $ (not a blankspace)
	new_str = (char *)malloc((dsign + 1) * sizeof(char)); // dsign is exactly the index where $ is
	i = -1;
	while (++i < dsign) // first bis dahin einsetzen, dann strjoin mit path var und dann  rest des input str
		new_str[i] = (*input_str)[i];
	new_str[i] = '\0';
	i++;
	// then i = dsign + 1
	while ((*input_str)[i] && (*input_str)[i] != ' ') //determine envvar size
		i++;
	envvar = (char *)malloc((i - dsign) * sizeof(char));
	i = dsign + 1;
	j = 0;
	while ((*input_str)[i] && (*input_str)[i] != ' ') // fill in envvar
		envvar[j++] = (*input_str)[i++];
	envvar[j] = '\0';
	envvar_value = find_envvar_value(envvar, mllcd);
	new_str = ft_strjoin_w_free(new_str, envvar_value); // fill in $ variable value
	new_str = ft_strjoin_w_free(new_str, (*input_str) + dsign + 1 + j); // fill in rest of (*input_str)
	free((*input_str));
	*input_str = new_str;
	return (free(envvar), free(envvar_value), j);
}

int expander(char **input_str, t_alloc *mllcd)
{
	int dsign;
	int i;

	dsign = 0;
	i = 0;
	while (dsign != -1 && (*input_str)[i])
	{
		dsign = find_dollar_sign((*input_str), i); // only those $ with no blankspace righ after will be found, as echo $ simply outputs $
		if (dsign != -1)
			i += replace_dollar_sign(input_str, dsign, mllcd);
		else
			i++; // go on looking from this spot on to find next $ and replace it
	}
	return (0);
}

//cc -Wall -Wextra -Werror expander.c input_parser_utils.c libft/*.c -g
// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./a.out
// int	main(int argc, char **argv, char **envv)
// {
// 	char *input_str;

// 	if (argv[argc - 1] == NULL)	
// 		return (1);
// 	input_str = ft_strdup("echo $PWD and $"); //fill in stuff from EXTRA/input_parser_testing
// 	// while (1)
// 	// {
// 	//	 input_str = read_input_print_prompt();

// 	if (expander(&input_str, envv))
// 		return (1);

// 	printf("%s\n", input_str);

// 	free(input_str);

// 	// if (cmdline_input_parser(&in_pars, input_str))
// 	// 	return (1);
// 	// int i = 0;
// 	// while (i < in_pars.m_argc)
// 	// {
// 	// 	printf("m_argv[%d] = %s\n", i, in_pars.m_argv[i]);
// 	// 	i++;
// 	// }
// 	return (0);
// }