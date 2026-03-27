/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:23:43 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:35:55 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <stdlib.h>
#include <unistd.h>

static void	export_print_all(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env && shell->env[i])
		ft_printf("declare -x %s\n", shell->env[i++]);
}

static int	export_one(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (shell->env = env_set(shell->env, arg, ""), 0);
	key = g_malloc(eq - arg + 1);
	if (!key)
		return (1);
	ft_strlcpy(key, arg, eq - arg + 1);
	shell->env = env_set(shell->env, key, eq + 1);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	size_t	i;

	if (!args || !args[1])
		return (export_print_all(shell), 0);
	i = 1;
	while (args[i])
		if (export_one(args[i++], shell))
			return (1);
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args || !args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		shell->env = env_unset(shell->env, args[i]);
		i++;
	}
	return (0);
}
