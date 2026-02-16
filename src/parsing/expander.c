/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_digit_var(int *len, int in_braces, char *str)
{
	char	*name;

	*len = 1;
	if (in_braces)
	{
		*len = 2;
		if (str[1] == '}')
			*len = 3;
	}
	name = g_malloc(1);
	if (name)
		name[0] = '\0';
	return (name);
}

static char	*get_var_name(char *str, int *len)
{
	int		i;
	int		in_braces;

	if (!str)
		return (*len = 0, NULL);
	in_braces = (str[0] == '{');
	if (in_braces)
		str++;
	if (ft_isdigit(str[0]))
		return (handle_digit_var(len, in_braces, str));
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (*len = 0, NULL);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (extract_var_name(str, i, in_braces, len));
}

static int	expand_exit_code(char **result, t_shell *shell)
{
	char	*code;
	char	*tmp;

	code = ft_itoa(shell->last_exit_code);
	if (!code)
		return (-1);
	tmp = ft_strjoin(*result, code);
	if (!tmp)
		return (-1);
	*result = tmp;
	return (2);
}

static int	expand_var(char *str, char **result, t_shell *shell)
{
	char	*name;
	char	*value;
	char	*tmp;
	int		len;

	name = get_var_name(str + 1, &len);
	if (!name)
	{
		*result = append_char(*result, '$');
		if (!*result)
			return (-1);
		return (1);
	}
	value = env_get(shell->env, name);
	if (value)
	{
		tmp = ft_strjoin(*result, value);
		if (!tmp)
			return (-1);
		*result = tmp;
	}
	return (len + 1);
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	int		ret;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			ret = expand_exit_code(&result, shell);
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '{'))
			ret = expand_var(str + i, &result, shell);
		else
		{
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
			ret = 1;
		}
		if (ret < 0)
			return (NULL);
		i += ret;
	}
	return (result);
}
