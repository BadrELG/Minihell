/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-gho <bael-gho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2026/03/24 01:38:00 by bael-gho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_shell
{
	char	**env;
	int		last_exit_code;
}	t_shell;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					quoted;
	int					no_expand;
	struct s_token		*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	int					expand;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_lex
{
	char				**word;
	t_shell				*shell;
	int					has_quotes;
	int					only_single;
	int					after_redir;
}	t_lex;

t_token			*lexer(char *input, t_shell *shell);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **list, t_token *new);
int				skip_whitespace(char *input, int i);
void			append_to_word(char **word, char *part);
int				get_operator(char *input, int i, t_token **tokens);
char			*get_redir_file(t_token *token, t_redir_type type,
					t_shell *shell);
int				expand_exit_code(char **result, t_shell *shell);
void			set_token_flags(t_token *token, t_lex *lex);
int				handle_quotes(char *in, int i, char quote, t_lex *lex);

t_cmd			*parser(t_token *tokens, t_shell *shell);
t_cmd			*new_cmd(void);
void			add_cmd(t_cmd **list, t_cmd *new);
t_redir			*new_redir(t_redir_type type, char *file);
void			add_redir(t_redir **list, t_redir *new);
int				is_redir_token(t_token_type type);
int				count_args(t_token *tokens);
t_redir_type	token_to_redir_type(t_token_type type);
int				syntax_error(char *msg);

int				is_whitespace(char c);
int				is_special_char(char c);

char			**env_init(char **envp);
char			*env_get(char **env, char *name);

char			*expand_variables(char *str, t_shell *shell);
char			*append_char(char *str, char c);
char			*extract_var_name(char *str, int i, int in_braces, int *len);

int				exec_cmds(t_cmd *cmds, char **env, t_shell *shell);

#endif
