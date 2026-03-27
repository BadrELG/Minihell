/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:24:36 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:24:39 by bael-gho         ###   ########.fr       */
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
	int	i;
	int	in_braces;

	if (!str)
	{
		*len = 0;
		return (NULL);
	}
	in_braces = (str[0] == '{');
	if (in_braces)
		str++;
	if (ft_isdigit(str[0]))
		return (handle_digit_var(len, in_braces, str));
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		*len = 0;
		return (NULL);
	}
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (extract_var_name(str, i, in_braces, len));
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

static int	handle_expand_char(char *str, char **result, t_shell *shell, int i)
{
	int	ret;

	if (str[i] == '$' && str[i + 1] == '?')
		ret = expand_exit_code(result, shell);
	else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '{'))
		ret = expand_var(str + i, result, shell);
	else
	{
		*result = append_char(*result, str[i]);
		if (!*result)
			return (-1);
		ret = 1;
	}
	return (ret);
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
		ret = handle_expand_char(str, &result, shell, i);
		if (ret < 0)
			return (NULL);
		i += ret;
	}
	return (result);
}
