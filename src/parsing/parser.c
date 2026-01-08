/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 02:55:43 by badr              #+#    #+#             */
/*   Updated: 2026/01/08 16:14:31 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Vérifie la validité syntaxique de la liste de tokens
** Détecte: pipe en début, pipes consécutifs, redirections sans fichier
** Retourne 1 si la syntaxe est correcte, 0 en cas d'erreur
*/
static int	check_redir_syntax(t_token *tmp)
{
	if (!tmp->next || tmp->next->type != TOKEN_WORD)
	{
		if (!tmp->next)
			return (syntax_error("newline"));
		return (syntax_error(tmp->next->value));
	}
	return (1);
}

static int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp && tmp->type == TOKEN_PIPE)
		return (syntax_error("|"));
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				return (syntax_error("|"));
		if (is_redir_token(tmp->type) && !check_redir_syntax(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/*
** Traite un token de redirection et l'ajoute à la commande
** Extrait le type de redirection et le nom du fichier du token suivant
** Pour heredoc: le delimiter n'est PAS expandé (sauf si entre quotes)
** Retourne le pointeur vers le token après le nom de fichier
*/
static t_token	*parse_redirection(t_token *token, t_cmd *cmd, t_shell *shell)
{
	t_redir_type	type;
	char			*file;
	t_redir			*redir;

	type = token_to_redir_type(token->type);
	file = NULL;
	if (token->next && token->next->type == TOKEN_WORD)
	{
		if (type == REDIR_HEREDOC)
		{
			if (token->next->quoted && !token->next->no_expand)
				file = expand_variables(token->next->value, shell);
			else
				file = token->next->value;
		}
		else if (token->next->no_expand)
			file = token->next->value;
		else
			file = expand_variables(token->next->value, shell);
		if (!file)
			return (NULL);
		redir = new_redir(type, file);
		if (redir && type == REDIR_HEREDOC)
			redir->expand = !token->next->quoted;
		add_redir(&cmd->redirs, redir);
		return (token->next->next);
	}
	return (token->next);
}

/*
** Parse une commande complete jusqu au prochain pipe
** Filtre les arguments vides qui ne viennent PAS de quotes (Bug 3)
*/
static t_token	*parse_command(t_token *tokens, t_cmd **cmds, t_shell *shell)
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
			tokens = parse_redirection(tokens, cmd, shell);
		else
		{
			if (tokens->type == TOKEN_WORD)
				if (tokens->value[0] || tokens->quoted)
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
t_cmd	*parser(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;

	cmds = NULL;
	if (!tokens)
		return (NULL);
	if (!check_syntax(tokens))
		return (NULL);
	while (tokens)
	{
		tokens = parse_command(tokens, &cmds, shell);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
