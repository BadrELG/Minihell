/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:19:33 by badr              #+#    #+#             */
/*   Updated: 2026/01/08 16:15:03 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	else
		return (REDIR_APPEND);
}

int	syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	int		skip_next;

	count = 0;
	tmp = tokens;
	skip_next = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (skip_next)
		{
			skip_next = 0;
			tmp = tmp->next;
			continue ;
		}
		if (is_redir_token(tmp->type))
			skip_next = 1;
		else if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
