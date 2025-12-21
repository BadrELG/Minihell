/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/19 16:18:42 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Crée et initialise un nouveau token avec son type et sa valeur
** Utilisé par le lexer pour construire la liste de tokens
** Retourne un pointeur vers le nouveau token ou NULL en cas d'échec
*/
t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = g_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

/*
** Ajoute un token à la fin de la liste chaînée de tokens
** Gère le cas d'une liste vide et les cas d'erreur (pointeurs NULL)
*/
void	add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
