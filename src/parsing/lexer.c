/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/20 10:08:07 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Traite une chaîne entre guillemets (simples ou doubles)
** Extrait le contenu entre quotes et l'ajoute au mot en cours
** Retourne l'index après le guillemet fermant, ou -1 si quote non fermée
*/
static int	handle_quotes(char *input, int i, char quote, char **word)
{
	int		start;
	char	*quoted;

	i++;
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (-1);
	}
	quoted = g_malloc(i - start + 1);
	if (!quoted)
		return (-1);
	ft_strlcpy(quoted, input + start, i - start + 1);
	append_to_word(word, quoted);
	return (i + 1);
}

/*
** Traite les caractères normaux d'un mot (sans quotes)
** Extrait les caractères jusqu'à un espace, caractère spécial ou quote
** Retourne l'index du prochain caractère à traiter
*/
static int	handle_word_char(char *input, int i, char **word)
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
	append_to_word(word, part);
	return (i);
}

/*
** Extrait un mot complet de l'entrée (peut contenir plusieurs parties avec/sans quotes)
** Combine les parties entre quotes et sans quotes en un seul token TOKEN_WORD
** Retourne l'index après le mot, ou -1 en cas d'erreur
*/
static int	get_word(char *input, int i, t_token **tokens)
{
	char	*word;

	word = NULL;
	while (input[i] && !is_whitespace(input[i]) && !is_special_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i = handle_quotes(input, i, input[i], &word);
			if (i == -1)
				return (-1);
		}
		else
		{
			i = handle_word_char(input, i, &word);
			if (i == -1)
				return (-1);
		}
	}
	if (word)
		add_token(tokens, new_token(TOKEN_WORD, word));
	return (i);
}

/*
** Identifie et extrait un opérateur (pipe | ou redirections <, >, >>)
** Crée le token correspondant avec le bon type (TOKEN_PIPE, TOKEN_REDIR_*, TOKEN_APPEND)
** Retourne l'index après l'opérateur
*/
static int	get_operator(char *input, int i, t_token **tokens)
{
	int				len;
	t_token_type	type;
	char			*val;

	len = 1;
	if (input[i] == '|')
		type = TOKEN_PIPE;
	else if (input[i] == '>' && input[i + 1] == '>' && ++len)
		type = TOKEN_APPEND;
	else if (input[i] == '<')
		type = TOKEN_REDIR_IN;
	else
		type = TOKEN_REDIR_OUT;
	val = ft_substr(input, i, len);
	add_token(tokens, new_token(type, val));
	return (i + len);
}

/*
** Fonction principale de l'analyse lexicale (tokenisation)
** Transforme une chaîne d'entrée en liste chaînée de tokens
** Retourne la liste de tokens ou NULL en cas d'erreur (ex: quote non fermée)
*/
t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_special_char(input[i]))
			i = get_operator(input, i, &tokens);
		else
		{
			i = get_word(input, i, &tokens);
			if (i == -1)
				return (NULL);
		}
	}
	return (tokens);
}
