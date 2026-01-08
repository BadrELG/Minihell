/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2026/01/07 18:13:14 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ==========================================================================
** TOUT CE FICHIER EST TEMPORAIRE - C'EST JUSTE POUR TESTER LE PARSING
** Tu peux virer print_debug() et shell_loop() quand tu fais l'exec
** ==========================================================================
*/

static void	print_redir(t_redir *r)
{
	while (r)
	{
		ft_printf("  -> ");
		if (r->type == REDIR_IN)
			ft_printf("< ");
		else if (r->type == REDIR_OUT)
			ft_printf("> ");
		else if (r->type == REDIR_APPEND)
			ft_printf(">> ");
		else if (r->type == REDIR_HEREDOC)
			ft_printf("<< ");
		if (r->file)
			ft_printf("%s", r->file);
		ft_printf("\n");
		r = r->next;
	}
}

static void	print_debug(t_cmd *cmd)
{
	int		i;

	while (cmd)
	{
		ft_printf("CMD:");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			ft_printf(" [%s]", cmd->args[i]);
			i++;
		}
		ft_printf("\n");
		print_redir(cmd->redirs);
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
static void	shell_loop(t_shell *shell)
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
			tokens = lexer(input, shell);
			if (tokens)
			{
				cmds = parser(tokens, shell);
				if (cmds)
					print_debug(cmds);
			}
		}
		free(input);
	}
}

/*
** Point d'entrée - initialise le shell avec l'environnement
** envp est copié dans shell.env pour pouvoir le modifier (export/unset)
** garbage_destroy() à la fin libère toute la mémoire allouée avec g_malloc
*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = env_init(envp);
	shell.last_exit_code = 0;
	shell_loop(&shell);
	garbage_destroy();
	return (0);
}
