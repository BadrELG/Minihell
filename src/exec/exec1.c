/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:24:02 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:24:03 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

static void	setup_fds(t_exec_ctx *ctx)
{
	if (ctx->fds[0] > 0)
	{
		dup2(ctx->fds[0], STDIN_FILENO);
		close(ctx->fds[0]);
	}
	if (ctx->fds[1] > 0)
	{
		dup2(ctx->fds[1], STDOUT_FILENO);
		close(ctx->fds[1]);
	}
	if (ctx->prev_pipe > 2 && ctx->fds[0] != ctx->prev_pipe)
		close(ctx->prev_pipe);
}

static void	exec_cmd(t_cmd *cmd, char **env, t_shell *shell)
{
	char	*cmd_path;
	int		result;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		return (result = exec_builtin_child(cmd, shell), exit(result), (void)0);
	cmd_path = find_cmd_path(cmd->args[0], env);
	if (!cmd_path)
	{
		ft_printf("command not found: %s\n", cmd->args[0]);
		exit(127);
	}
	execve(cmd_path, cmd->args, env);
	perror("execve");
	exit(1);
}

static void	child_pro(t_cmd *cmd, t_exec_ctx *ctx, char **env, t_shell *shell)
{
	setup_child_signals();
	setup_fds(ctx);
	exec_cmd(cmd, env, shell);
}

int	fork_and_exec(t_cmd *cmd, t_exec_ctx *ctx, char **env, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		child_pro(cmd, ctx, env, shell);
	ctx->pids[ctx->pid_count++] = pid;
	if (ctx->fds[1] > 0)
		close(ctx->fds[1]);
	if (ctx->fds[0] > 2 && ctx->fds[0] != ctx->prev_pipe)
		close(ctx->fds[0]);
	return (0);
}
