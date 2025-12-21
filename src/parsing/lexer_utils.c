/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/19 16:18:42 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si un caractère est un espace blanc (espace, tabulation ou retour à la ligne)
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

	if (*word)
	{
		tmp = ft_strjoin(*word, part);
		*word = tmp;
	}
	else
		*word = part;
}
