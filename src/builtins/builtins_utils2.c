/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:23:32 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:36:40 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <stdlib.h>

int	env_count(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

int	env_find_index(char **env, char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*build_entry(char *key, char *value)
{
	char	*entry;
	int		key_len;

	key_len = ft_strlen(key);
	entry = g_malloc(key_len + ft_strlen(value) + 2);
	if (!entry)
		return (NULL);
	ft_strlcpy(entry, key, key_len + 1);
	ft_strlcat(entry, "=", key_len + 2);
	ft_strlcat(entry, value, key_len + ft_strlen(value) + 2);
	return (entry);
}

static char	**append_entry(char **env, char *entry)
{
	char	**new_env;
	int		count;
	int		i;

	count = env_count(env);
	new_env = g_malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (env);
	i = -1;
	while (++i < count)
		new_env[i] = env[i];
	new_env[count] = entry;
	new_env[count + 1] = NULL;
	return (new_env);
}

char	**env_set(char **env, char *key, char *value)
{
	char	*entry;
	int		index;

	if (!key)
		return (env);
	if (!value)
		value = "";
	entry = build_entry(key, value);
	if (!entry)
		return (env);
	index = env_find_index(env, key);
	if (index >= 0)
		return (env[index] = entry, env);
	return (append_entry(env, entry));
}
