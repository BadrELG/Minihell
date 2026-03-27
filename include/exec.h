/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:26:03 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:26:03 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec_ctx
{
	int		*fds;
	int		prev_pipe;
	pid_t	*pids;
	int		pid_count;
}	t_exec_ctx;

int		exec_cmds(t_cmd *cmds, char **env, t_shell *shell);
int		handle_heredoc(char *delimiter, int expand);
int		setup_pipe(t_cmd *current_cmd, t_exec_ctx *ctx, int pipe_fds[2]);
int		apply_redirections(t_cmd *cmd, t_exec_ctx *ctx);
int		init_exec_ctx(t_exec_ctx *ctx, int num_cmds);
int		fork_and_exec(t_cmd *cmd, t_exec_ctx *ctx, char **env, t_shell *shell);
int		handle_stateful_builtin(t_cmd *cmds, t_shell *shell);
void	cleanup_fds(t_exec_ctx *ctx);
void	wait_children(t_exec_ctx *ctx, t_shell *shell);
int		count_cmds(t_cmd *cmds);
char	*find_cmd_path(char *cmd, char **env);

#endif
