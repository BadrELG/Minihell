/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2026/03/24 01:24:33 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_var_name(char *str, int i, int in_braces, int *len)
{
	char	*name;

	*len = i;
	name = g_malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	if (in_braces && str[i] == '}')
		*len += 2;
	else if (in_braces)
		*len += 1;
	return (name);
}

char	*append_char(char *str, char c)
{
	char	*result;
	int		len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	result = g_malloc(len + 2);
	if (!result)
		return (NULL);
	if (str)
		ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

int	expand_exit_code(char **result, t_shell *shell)
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
