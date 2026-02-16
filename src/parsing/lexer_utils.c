/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:39:04 by badr              #+#    #+#             */
/*   Updated: 2026/01/08 16:14:04 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

void	append_to_word(char **word, char *part)
{
	char	*tmp;

	if (!part)
		return ;
	if (*word)
	{
		tmp = ft_strjoin(*word, part);
		if (tmp)
			*word = tmp;
	}
	else
		*word = part;
}

int	get_operator(char *input, int i, t_token **tokens)
{
	int				len;
	t_token_type	type;
	char			*val;

	len = 1;
	if (input[i] == '|')
		type = TOKEN_PIPE;
	else if (input[i] == '>' && input[i + 1] == '>' && ++len)
		type = TOKEN_APPEND;
	else if (input[i] == '<' && input[i + 1] == '<' && ++len)
		type = TOKEN_HEREDOC;
	else if (input[i] == '<')
		type = TOKEN_REDIR_IN;
	else
		type = TOKEN_REDIR_OUT;
	val = ft_substr(input, i, len);
	add_token(tokens, new_token(type, val));
	return (i + len);
}
