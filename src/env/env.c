/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static int	env_find_index(char **env, char *name)
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

static char	**create_empty_env(void)
{
	char	**env;

	env = g_malloc(sizeof(char *) * 1);
	if (!env)
		return (NULL);
	env[0] = NULL;
	return (env);
}

char	**env_init(char **envp)
{
	char	**env;
	int		count;
	int		i;

	if (!envp || !envp[0])
		return (create_empty_env());
	count = env_count(envp);
	env = g_malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env[i] = g_malloc(ft_strlen(envp[i]) + 1);
		if (!env[i])
			return (NULL);
		ft_strlcpy(env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*env_get(char **env, char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = env_find_index(env, name);
	if (i == -1)
		return (NULL);
	return (env[i] + len + 1);
}
