/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:24:04 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:35:35 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

void	cleanup_fds(t_exec_ctx *ctx)
{
	if (ctx->fds[0] > 1)
		close(ctx->fds[0]);
	if (ctx->fds[1] > 1)
		close(ctx->fds[1]);
	if (ctx->prev_pipe > 1)
		close(ctx->prev_pipe);
}

void	wait_children(t_exec_ctx *ctx, t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < ctx->pid_count)
	{
		waitpid(ctx->pids[i], &status, 0);
		if (i == ctx->pid_count - 1)
		{
			if (WIFEXITED(status))
				shell->last_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->last_exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	handle_stateful_builtin(t_cmd *cmds, t_shell *shell)
{
	char	*cmd;
	int		result;

	cmd = cmds->args[0];
	if (ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0)
	{
		result = exec_builtin_parent(cmds, shell);
		shell->last_exit_code = result;
		return (result);
	}
	return (-2);
}

int	init_exec_ctx(t_exec_ctx *ctx, int num_cmds)
{
	ctx->pids = g_malloc(sizeof(pid_t) * num_cmds);
	ctx->fds = g_malloc(sizeof(int) * 2);
	if (!ctx->pids || !ctx->fds)
		return (-1);
	ctx->pid_count = 0;
	ctx->prev_pipe = -1;
	return (0);
}

int	setup_pipe(t_cmd *current_cmd, t_exec_ctx *ctx, int pipe_fds[2])
{
	if (!current_cmd->next)
		return (0);
	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	ctx->fds[1] = pipe_fds[1];
	ctx->prev_pipe = pipe_fds[0];
	return (0);
}
