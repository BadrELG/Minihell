/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:23:29 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:23:29 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <stdlib.h>

static char	**copy_without(char **env, int skip, int count)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = g_malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < count - 1)
		if (i != skip)
			new_env[j++] = env[i];
	new_env[j] = NULL;
	return (new_env);
}

char	**env_unset(char **env, char *name)
{
	int		index;
	char	**new_env;

	if (!env || !name)
		return (env);
	index = env_find_index(env, name);
	if (index < 0)
		return (env);
	new_env = copy_without(env, index, env_count(env));
	if (new_env)
		env = new_env;
	return (env);
}
