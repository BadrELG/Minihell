/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:23:40 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:36:09 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <stdlib.h>
#include <unistd.h>

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	if (!args || !args[0])
		return (0);
	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

int	builtin_pwd(char **args)
{
	char	cwd[4096];

	(void)args;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

static char	*resolve_cd_path(char **args, t_shell *shell)
{
	char	*path;

	path = args[1];
	if (!path)
		path = env_get(shell->env, "HOME");
	if (!path)
		return (ft_printf("cd: HOME not set\n"), NULL);
	if (ft_strncmp(path, "-", 2) == 0)
	{
		path = env_get(shell->env, "OLDPWD");
		if (!path)
			return (ft_printf("cd: OLDPWD not set\n"), NULL);
	}
	return (path);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	oldpwd[4096];
	char	newpwd[4096];

	if (!args || !args[0])
		return (1);
	path = resolve_cd_path(args, shell);
	if (!path)
		return (1);
	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) < 0)
		return (perror(path), 1);
	getcwd(newpwd, sizeof(newpwd));
	shell->env = env_set(shell->env, "OLDPWD", oldpwd);
	shell->env = env_set(shell->env, "PWD", newpwd);
	return (0);
}
