/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:24:00 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:24:01 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

static int	ex_onecmd(t_cmd *cmd, t_exec_ctx *ctx, char **env, t_shell *shell)
{
	int	pipe_fds[2];

	ctx->fds[0] = ctx->prev_pipe;
	ctx->fds[1] = -1;
	if (setup_pipe(cmd, ctx, pipe_fds) < 0)
		return (-1);
	if (apply_redirections(cmd, ctx) < 0)
		return (-1);
	if (fork_and_exec(cmd, ctx, env, shell) < 0)
		return (-1);
	return (0);
}

int	exec_cmds(t_cmd *cmds, char **env, t_shell *shell)
{
	int			num_cmds;
	t_exec_ctx	ctx;
	t_cmd		*current_cmd;
	int			result;

	num_cmds = count_cmds(cmds);
	if (num_cmds == 1 && is_builtin(cmds->args[0]))
	{
		result = handle_stateful_builtin(cmds, shell);
		if (result != -2)
			return (result);
	}
	if (init_exec_ctx(&ctx, num_cmds) < 0)
		return (-1);
	current_cmd = cmds;
	while (current_cmd)
	{
		if (ex_onecmd(current_cmd, &ctx, env, shell) < 0)
			return (-1);
		current_cmd = current_cmd->next;
	}
	cleanup_fds(&ctx);
	wait_children(&ctx, shell);
	return (shell->last_exit_code);
}
