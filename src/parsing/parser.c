/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/19 16:18:42 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie la validité syntaxique de la liste de tokens
** Détecte: pipe en début, pipes consécutifs, redirections sans fichier
** Retourne 1 si la syntaxe est correcte, 0 en cas d'erreur
*/
static int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == TOKEN_PIPE)
		return (syntax_error("|"));
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE && (!tmp->next || tmp->next->type == TOKEN_PIPE))
			return (syntax_error("|"));
		if ((tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
				|| tmp->type == TOKEN_APPEND)
			&& (!tmp->next || tmp->next->type != TOKEN_WORD))
		{
			if (!tmp->next)
				return (syntax_error("newline"));
			return (syntax_error(tmp->next->value));
		}
		tmp = tmp->next;
	}
	return (1);
}

/*
** Traite un token de redirection et l'ajoute à la commande
** Extrait le type de redirection et le nom du fichier du token suivant
** Retourne le pointeur vers le token après le nom de fichier
*/
static t_token	*parse_redirection(t_token *token, t_cmd *cmd)
{
	t_redir_type	type;

	type = token_to_redir_type(token->type);
	if (token->next && token->next->type == TOKEN_WORD)
	{
		add_redir(&cmd->redirs, new_redir(type, token->next->value));
		return (token->next->next);
	}
	return (token->next);
}

/*
** Parse une commande complète (arguments + redirections) jusqu'au prochain pipe
** Crée une structure t_cmd avec ses arguments et redirections
** Ajoute la commande à la liste et retourne le token après la commande (pipe ou NULL)
*/
static t_token	*parse_command(t_token *tokens, t_cmd **cmds)
{
	t_cmd	*cmd;
	int		i;

	cmd = new_cmd();
	cmd->args = g_malloc(sizeof(char *) * (count_args(tokens) + 1));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (is_redir_token(tokens->type))
			tokens = parse_redirection(tokens, cmd);
		else
		{
			if (tokens->type == TOKEN_WORD)
				cmd->args[i++] = tokens->value;
			tokens = tokens->next;
		}
	}
	cmd->args[i] = NULL;
	add_cmd(cmds, cmd);
	return (tokens);
}

/*
** Fonction principale de l'analyse syntaxique
** Transforme une liste de tokens en liste chaînée de commandes exécutables
** Vérifie d'abord la syntaxe puis parse chaque commande séparée par des pipes
** Retourne la liste de commandes ou NULL en cas d'erreur
*/
t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmds;

	cmds = NULL;
	if (!tokens)
		return (NULL);
	if (!check_syntax(tokens))
		return (NULL);
	while (tokens)
	{
		tokens = parse_command(tokens, &cmds);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
