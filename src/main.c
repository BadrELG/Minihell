/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/21 10:13:12 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ==========================================================================
** TOUT CE FICHIER EST TEMPORAIRE - C'EST JUSTE POUR TESTER LE PARSING
** Tu peux virer print_debug() et shell_loop() quand tu fais l'exec
** ==========================================================================
*/

/*
** Affiche le contenu d'une liste de commandes pour debug
** Parcourt chaque cmd et affiche ses args entre crochets [arg1] [arg2]
** Puis affiche les redirections avec leur type (<, >, >>)
** Les pipes sont représentés par un | entre les commandes
*/
static void	print_debug(t_cmd *cmd)
{
	int		i;
	t_redir	*r;

	while (cmd)
	{
		ft_printf("CMD: ");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				ft_printf("[%s] ", cmd->args[i]);
				i++;
			}
		}
		ft_printf("\n");
		r = cmd->redirs;
		while (r)
		{
			ft_printf("  -> ");
			if (r->type == REDIR_IN)
				ft_printf("< ");
			else if (r->type == REDIR_OUT)
				ft_printf("> ");
			else if (r->type == REDIR_APPEND)
				ft_printf(">> ");
			if (r->file)
				ft_printf("%s", r->file);
			ft_printf("\n");
			r = r->next;
		}
		if (cmd->next)
			ft_printf("  |\n");
		cmd = cmd->next;
	}
}

/*
** Boucle principale du shell (version test)
** Lit l'input avec readline, le passe au lexer puis au parser
** Affiche le résultat avec print_debug pour vérifier que ça marche
** CTRL+D (input == NULL) quitte proprement
** Pour l'exec: remplace print_debug() par ta fonction d'exécution
*/
static void	shell_loop(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			tokens = lexer(input);
			if (tokens)
			{
				cmds = parser(tokens);
				if (cmds)
					print_debug(cmds);
			}
		}
		free(input);
	}
}

/*
** Point d'entrée - pour l'instant on ignore argc/argv/envp
** envp te servira pour récupérer les variables d'environnement
** garbage_destroy() à la fin libère toute la mémoire allouée avec g_malloc
*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	shell_loop();
	garbage_destroy();
	return (0);
}
