/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2026/03/24 01:24:48 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_quote(char *quoted, char quote, t_lex *lex)
{
	if (quote == '"')
	{
		lex->only_single = 0;
		if (!lex->after_redir)
		{
			quoted = expand_variables(quoted, lex->shell);
			if (!quoted)
				return (NULL);
		}
	}
	return (quoted);
}

int	handle_quotes(char *in, int i, char quote, t_lex *lex)
{
	int		start;
	char	*quoted;

	i++;
	start = i;
	while (in[i] && in[i] != quote)
		i++;
	if (!in[i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (-1);
	}
	quoted = g_malloc(i - start + 1);
	if (!quoted)
		return (-1);
	ft_strlcpy(quoted, in + start, i - start + 1);
	quoted = process_quote(quoted, quote, lex);
	if (!quoted)
		return (-1);
	append_to_word(lex->word, quoted);
	lex->has_quotes = 1;
	return (i + 1);
}
