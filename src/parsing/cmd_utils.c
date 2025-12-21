/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/19 16:18:42 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Crée et initialise une nouvelle structure de commande
** Retourne un pointeur vers la nouvelle commande ou NULL en cas d'échec
*/
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = g_malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

/*
** Ajoute une commande à la fin de la liste chaînée de commandes
** Gère le cas d'une liste vide et les cas d'erreur (pointeurs NULL)
*/
void	add_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

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

/*
** Crée et initialise une nouvelle structure de redirection
** Paramètres : type de redirection (IN/OUT/APPEND) et nom du fichier
** Retourne un pointeur vers la nouvelle redirection ou NULL en cas d'échec
*/
t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = g_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

/*
** Ajoute une redirection à la fin de la liste chaînée de redirections
** Gère le cas d'une liste vide et les cas d'erreur (pointeurs NULL)
*/
void	add_redir(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

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
