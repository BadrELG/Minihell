/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2026/03/24 01:34:34 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/exec.h"
#include "../include/signals.h"

static int	handle_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (!*input)
		return (0);
	add_history(input);
	tokens = lexer(input, shell);
	if (!tokens)
		return (0);
	cmds = parser(tokens, shell);
	if (!cmds)
		return (0);
	exec_cmds(cmds, shell->env, shell);
	return (0);
}

static int	read_input(char **input)
{
	*input = readline("minishell> ");
	if (!*input)
	{
		ft_printf("exit\n");
		return (1);
	}
	if (g_signal == SIGINT || g_signal == SIGQUIT)
	{
		free(*input);
		return (2);
	}
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;
	int		status;

	while (1)
	{
		g_signal = 0;
		status = read_input(&input);
		if (status == 1)
			break ;
		if (status == 2)
			continue ;
		handle_input(input, shell);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	setup_signals();
	shell.env = env_init(envp);
	shell.last_exit_code = 0;
	shell_loop(&shell);
	garbage_destroy();
	return (0);
}
