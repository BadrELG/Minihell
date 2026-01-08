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

/*
** Vérifie si un caractère est un espace blanc
** (espace, tabulation ou retour à la ligne)
** Retourne 1 si c'est un espace blanc, 0 sinon
*/
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
** Vérifie si un caractère est un caractère spécial du shell (pipe ou redirections)
** Retourne 1 si c'est un caractère spécial (|, <, >), 0 sinon
*/
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Avance dans la chaîne en sautant tous les espaces blancs consécutifs
** Retourne l'index du premier caractère non-blanc
*/
int	skip_whitespace(char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

/*
** Concatène une partie de texte au mot en cours de construction
** Si le mot est vide, initialise le mot avec la partie
** Utilisé pour assembler les mots avec quotes et sans quotes
*/
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

/*
** Extrait un opérateur (pipe ou redirection) et crée le token correspondant
** Gère: | (pipe), < (input), > (output), >> (append), << (heredoc)
** Détecte les opérateurs doubles (>> et <<) automatiquement
** Retourne la position après l'opérateur
*/
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
