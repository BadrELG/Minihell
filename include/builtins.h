/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:26:00 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:26:00 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <unistd.h>

int		is_builtin(char *cmd);
int		exec_builtin_parent(t_cmd *cmd, t_shell *shell);
int		exec_builtin_child(t_cmd *cmd, t_shell *shell);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(char **args);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_env(char **args, t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);
char	**env_set(char **env, char *key, char *value);
char	**env_unset(char **env, char *key);
int		env_count(char **env);
int		env_find_index(char **env, char *name);

#endif
