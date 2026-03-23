/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:56:23 by badr              #+#    #+#             */
/*   Updated: 2026/03/23 18:20:16 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	process_lexer_node(char *input, int i, t_token **tok, t_lex *lex)
{
	if (is_special_char(input[i]))
	{
		lex->after_redir = (input[i] == '<' || input[i] == '>');
		i = get_operator(input, i, tok);
	}
	else
	{
		i = get_word(input, i, tok, lex);
		if (i != -1)
			lex->after_redir = 0;
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
		i = process_lexer_node(input, i, &tokens, &lex);
		if (i == -1)
			return (NULL);
	}
	return (tokens);
}
