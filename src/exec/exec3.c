/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 01:24:07 by bael-gho          #+#    #+#             */
/*   Updated: 2026/03/24 01:35:26 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../include/builtins.h"
#include "../../include/signals.h"

static int	apply_redir_in(t_redir *redir, t_exec_ctx *ctx)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->file);
		return (-1);
	}
	if (ctx->fds[0] != -1 && ctx->fds[0] != ctx->prev_pipe)
		close(ctx->fds[0]);
	ctx->fds[0] = fd;
	return (0);
}

static int	apply_redir_out(t_redir *redir, t_exec_ctx *ctx)
{
	int	flags;
	int	fd;

	flags = O_CREAT | O_WRONLY;
	if (redir->type == REDIR_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(redir->file, flags, 0644);
	if (fd < 0)
	{
		perror(redir->file);
		return (-1);
	}
	if (ctx->fds[1] != -1)
		close(ctx->fds[1]);
	ctx->fds[1] = fd;
	return (0);
}

static int	apply_redir_heredoc(t_redir *redir, t_exec_ctx *ctx)
{
	int	fd;

	fd = handle_heredoc(redir->file, redir->expand);
	if (fd < 0)
		return (-1);
	if (ctx->fds[0] != -1 && ctx->fds[0] != ctx->prev_pipe)
		close(ctx->fds[0]);
	ctx->fds[0] = fd;
	return (0);
}

static int	apply_one_redir(t_redir *redir, t_exec_ctx *ctx)
{
	if (redir->type == REDIR_IN)
		return (apply_redir_in(redir, ctx));
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (apply_redir_out(redir, ctx));
	if (redir->type == REDIR_HEREDOC)
		return (apply_redir_heredoc(redir, ctx));
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_exec_ctx *ctx)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (apply_one_redir(redir, ctx) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
