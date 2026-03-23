/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 02:55:43 by badr              #+#    #+#             */
/*   Updated: 2026/03/23 18:20:16 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redir_syntax(t_token *tmp)
{
	if (!tmp->next || tmp->next->type != TOKEN_WORD)
	{
		if (!tmp->next)
			return (syntax_error("newline"));
		return (syntax_error(tmp->next->value));
	}
	return (1);
}

static int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == TOKEN_PIPE)
		return (syntax_error("|"));
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				return (syntax_error("|"));
		if (is_redir_token(tmp->type) && !check_redir_syntax(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static t_token	*parse_redirection(t_token *token, t_cmd *cmd, t_shell *shell)
{
	t_redir_type	type;
	char			*file;
	t_redir			*redir;

	type = token_to_redir_type(token->type);
	if (token->next && token->next->type == TOKEN_WORD)
	{
		file = get_redir_file(token, type, shell);
		if (!file)
			return (NULL);
		redir = new_redir(type, file);
		if (redir && type == REDIR_HEREDOC)
			redir->expand = !token->next->quoted;
		add_redir(&cmd->redirs, redir);
		return (token->next->next);
	}
	return (token->next);
}

static t_token	*parse_command(t_token *tokens, t_cmd **cmds, t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	cmd = new_cmd();
	cmd->args = g_malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (is_redir_token(tokens->type))
			tokens = parse_redirection(tokens, cmd, shell);
		else
		{
			if (tokens->type == TOKEN_WORD)
				if (tokens->value[0] || tokens->quoted)
					cmd->args[i++] = tokens->value;
			tokens = tokens->next;
		}
	}
	cmd->args[i] = NULL;
	add_cmd(cmds, cmd);
	return (tokens);
}

t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;

	cmds = NULL;
	if (!tokens)
		return (NULL);
	if (!check_syntax(tokens))
		return (NULL);
	while (tokens)
	{
		tokens = parse_command(tokens, &cmds, shell);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
