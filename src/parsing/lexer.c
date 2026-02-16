/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:56:23 by badr              #+#    #+#             */
/*   Updated: 2026/01/08 16:13:37 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quotes(char *in, int i, char quote, t_lex *lex)
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
	if (quote == '"')
	{
		lex->only_single = 0;
		if (!lex->after_redir)
		{
			quoted = expand_variables(quoted, lex->shell);
			if (!quoted)
				return (-1);
		}
	}
	append_to_word(lex->word, quoted);
	lex->has_quotes = 1;
	return (i + 1);
}

static int	handle_word_char(char *input, int i, t_lex *lex)
{
	int		start;
	char	*part;

	start = i;
	while (input[i] && !is_whitespace(input[i]) && !is_special_char(input[i])
		&& input[i] != '\'' && input[i] != '"')
		i++;
	part = g_malloc(i - start + 1);
	if (!part)
		return (-1);
	ft_strlcpy(part, input + start, i - start + 1);
	lex->only_single = 0;
	if (!lex->after_redir)
	{
		part = expand_variables(part, lex->shell);
		if (!part)
			return (-1);
	}
	append_to_word(lex->word, part);
	return (i);
}

static void	set_token_flags(t_token *token, t_lex *lex)
{
	if (token)
	{
		token->quoted = lex->has_quotes;
		token->no_expand = (lex->has_quotes && lex->only_single);
	}
}

static int	get_word(char *in, int i, t_token **tok, t_lex *lex)
{
	char	*word;
	t_token	*token;

	word = NULL;
	lex->word = &word;
	lex->has_quotes = 0;
	lex->only_single = 1;
	while (in[i] && !is_whitespace(in[i]) && !is_special_char(in[i]))
	{
		if (in[i] == '\'' || in[i] == '"')
			i = handle_quotes(in, i, in[i], lex);
		else
			i = handle_word_char(in, i, lex);
		if (i == -1)
			return (-1);
	}
	if (word)
	{
		token = new_token(TOKEN_WORD, word);
		set_token_flags(token, lex);
		add_token(tok, token);
	}
	return (i);
}

t_token	*lexer(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_lex	lex;
	int		i;

	tokens = NULL;
	i = 0;
	lex.shell = shell;
	lex.after_redir = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_special_char(input[i]))
		{
			lex.after_redir = (input[i] == '<' || input[i] == '>');
			i = get_operator(input, i, &tokens);
		}
		else
		{
			i = get_word(input, i, &tokens, &lex);
			if (i == -1)
				return (NULL);
			lex.after_redir = 0;
		}
	}
	return (tokens);
}
