/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/19 16:18:42 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie si un type de token représente une redirection
** Retourne 1 si c'est une redirection (IN, OUT ou APPEND), 0 sinon
*/
int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND);
}

/*
** Convertit un type de token en type de redirection correspondant
** Mapping: TOKEN_REDIR_IN -> REDIR_IN, TOKEN_REDIR_OUT -> REDIR_OUT, TOKEN_APPEND -> REDIR_APPEND
*/
t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else
		return (REDIR_APPEND);
}

/*
** Affiche un message d'erreur de syntaxe sur stderr
** Format: "minishell: syntax error near unexpected token `<msg>'"
** Retourne toujours 0 pour simplifier la gestion d'erreur
*/
int	syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

/*
** Compte le nombre d'arguments (tokens WORD) dans une commande
** Ignore les redirections et leurs fichiers associés
** S'arrête au pipe suivant ou à la fin de la liste
** Utilisé pour allouer le tableau d'arguments de la commande
*/
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
