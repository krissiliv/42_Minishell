/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgober <pgober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:53:42 by pgober            #+#    #+#             */
/*   Updated: 2024/02/09 15:09:52 by pgober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_dollar_sign(char *str, int starting_pt)
{
	int		i;
	bool	single_quotes_open;
	bool	double_quotes_open;

	i = 0;
	single_quotes_open = false;
	double_quotes_open = false;
	while (i < starting_pt)
	{
		if (str[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		else if (str[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
		i++;
	}
	i = starting_pt;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quotes_open)
			single_quotes_open = !single_quotes_open;
		else if (str[i] == '\"' && !single_quotes_open)
			double_quotes_open = !double_quotes_open;
		if (single_quotes_open == false && \
			str[i + 1] && str[i] == '$' && (ft_isalpha(str[i + 1]) != 0 \
			|| str[i + 1] == '?' || (str[i + 1] == '\"' && double_quotes_open == false) || str[i + 1] == '\''))
			return (i);
		i++;
	}
	return (-1);
}

char	*find_envvar_value(char *envvar, t_alloc *mllcd)
{
	t_env	*pos;
	int		len;
	char	*envvar_w_equalsign;
	char	*return_value;

	if (!envvar || ft_strlen(envvar) == 0)
		return (NULL);
	if (ft_strcmp(envvar, "?") == 0)
	{
		return_value = ft_itoa(mllcd->exit_status);
		if (!return_value)
			return (NULL);
		return (return_value);
	}
    pos = mllcd->env_list;
	envvar_w_equalsign = ft_strjoin(envvar, "=");
	if (!envvar_w_equalsign)
		return (NULL);
	len = ft_strlen(envvar_w_equalsign);
    while (pos != NULL && ft_strncmp(pos->env_var, envvar_w_equalsign, len) != 0)
		pos = pos->next;
	if (pos != NULL && ft_strncmp(pos->env_var, envvar_w_equalsign, len) == 0)
		return (free(envvar_w_equalsign), ft_strdup(pos->env_var + len)); // + 1 to jump over "="
	return (free(envvar_w_equalsign), ft_strdup(""));
}

static int	replace_dollar_sign(char **input_str, int dsign, t_alloc *mllcd)
{
	char	*new_str;
	char	*envvar;
	char	*envvar_value;
	int		i;

	if ((*input_str)[dsign + 1] == '\"' || (*input_str)[dsign + 1] == '\'')
	{
		new_str = ft_substr((*input_str), 0, dsign);
		if (!new_str)
			return (free((*input_str)), -1);
		new_str = ft_strjoin_w_free(new_str, (*input_str) + dsign + 1);
		free((*input_str));
		if (!new_str)
			return (-1);
		*input_str = new_str;
		// printf("in replace_dsign: input_str = %s\n", *input_str);
		return (1);
	}
	// here it is already clear that there is sth after the $ (not a blankspace)
	new_str = ft_substr((*input_str), 0, dsign); // fill in new_str with everything before $ variable
	if (!new_str)
		return (free(*input_str), -1);
	i = dsign + 1;
	while ((*input_str)[i] && (ft_isalnum((*input_str)[i]) || (*input_str)[i] == '_' || (*input_str)[i] == '?')) //determine envvar size
		i++;
	envvar = ft_substr((*input_str), dsign + 1, i - dsign - 1); // fill in envvar with $ variable
	if (!envvar || ft_strlen(envvar) == 0)
		return (free(new_str), exit_mllcfail(mllcd), -1);
	envvar_value = find_envvar_value(envvar, mllcd);
	if (envvar)
	{
		free(envvar);
		envvar = NULL;
	} //added this to fix leaks - and it did but caused additional seg faults
	if (!envvar_value)
		return (free(new_str), -1);
	new_str = ft_strjoin_w_free(new_str, envvar_value); // fill in $ variable value
	if (!new_str)
		return (free(envvar_value), free(*input_str), -1);
	new_str = ft_strjoin_w_free(new_str, (*input_str) + dsign + 1 + i - dsign - 1); // fill in rest of (*input_str)
	free(*input_str);
	if (!new_str)
		return (free(envvar_value), -1);
	*input_str = new_str;
	i = ft_strlen(envvar_value);
	return (free(envvar_value), i);
}

static void	expand_tilde(char **input_str, t_alloc *mllcd)
{
	int i;
	bool single_quotes_open;
	bool double_quotes_open;
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	single_quotes_open = false;
	double_quotes_open = false;
	i = 0;
	while ((*input_str)[i])
	{
		if ((*input_str)[i] == '~' && !single_quotes_open && !double_quotes_open)
		{
			tmp = find_envvar_value("USER", mllcd);
			if ((*input_str)[i + 1] == '\0' || is_space((*input_str)[i + 1]) || (*input_str)[i + 1] == '/')
			{
				tmp2 = ft_substr((*input_str), i + 1, ft_strlen((*input_str)) - i - 1);
				tmp3 = find_envvar_value("HOME", mllcd);
				tmp4 = ft_substr((*input_str), 0, i);
				free(*input_str);
				*input_str = ft_strjoin_w_free(ft_strjoin_w_free(tmp4, tmp3), tmp2);
				free(tmp2);
				free(tmp3);
				if (!(*input_str))
					return ;
			}
			else if (((*input_str)[i + 1] == '+' || (*input_str)[i + 1] == '-'))
			{
				tmp2 = ft_substr((*input_str), i + 2, ft_strlen((*input_str)) - i - 2);
				tmp3 = find_envvar_value("PWD", mllcd);
				tmp4 = ft_substr((*input_str), 0, i);
				free(*input_str);
				*input_str = ft_strjoin_w_free(ft_strjoin_w_free(tmp4, tmp3), tmp2);
				free(tmp2);
				free(tmp3);
				if (!(*input_str))
					return ;
			}
			else if (ft_strncmp((*input_str) + i + 1, tmp, ft_strlen(tmp) - 1) == 0)
			{
				// printf("input_str[i + 1] = %c\n", (*input_str)[i + 1]);
				*input_str = ft_strjoin_w_free(ft_strjoin_w_free(ft_substr((*input_str), 0, i), find_envvar_value("HOME", mllcd)), ft_substr((*input_str), i + 1 + ft_strlen(tmp), ft_strlen((*input_str)) - i - 1 - ft_strlen(tmp)));
				if (!(*input_str))
					return ;
				i += ft_strlen(find_envvar_value("HOME", mllcd));
				// printf("strlen( envvar) = %ld\n", ft_strlen(find_envvar_value("HOME", mllcd)) - 1);
				// printf("envvar_value = %s\n", find_envvar_value("HOME", mllcd));
				// printf("input_str[i + 1] = %c\n", (*input_str)[i + 1]);
			}
			free(tmp);
		}
		i++;
	}
}

int expander(char **input_str, t_alloc *mllcd)
{
	int dsign;
	int i;
	int j;

	expand_tilde(input_str, mllcd);
	dsign = 0;
	i = 0;
	// if (!(*input_str))
	// 	return (ft_putstr_fd("Expander-error: no input received.\n", 2), 1);
	while (*input_str && dsign != -1 && (*input_str)[i])
	{
		dsign = find_dollar_sign((*input_str), i); // only those $ with no blankspace righ after will be found, as echo $ simply outputs $
		j = 0;
		if (dsign != -1)
		{
			j = replace_dollar_sign(input_str, dsign, mllcd);
			if (j == -1)
				return (1);
			i += j;
		}
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