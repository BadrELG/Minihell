/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badr <badr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by badr              #+#    #+#             */
/*   Updated: 2025/12/20 10:09:00 by badr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/*
** Types de tokens - le lexer découpe l'input en ces catégories
** TOKEN_WORD    = un mot (commande, argument, nom de fichier)
** TOKEN_PIPE    = le caractère |
** TOKEN_REDIR_* = les redirections <, >, >>
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND
}	t_token_type;

/*
** Structure d'un token - liste chaînée
** type  = le type du token (voir enum au-dessus)
** value = la valeur brute (ex: "ls", "|", ">")
** next  = pointeur vers le token suivant
*/
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/*
** Types de redirections pour l'exec
** REDIR_IN     = < (lecture depuis fichier)
** REDIR_OUT    = > (écriture dans fichier, écrase)
** REDIR_APPEND = >> (écriture dans fichier, ajoute à la fin)
*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND
}	t_redir_type;

/*
** Structure d'une redirection - liste chaînée
** type = le type de redirection (voir enum au-dessus)
** file = le nom du fichier cible
** next = pointeur vers la redirection suivante
** Une commande peut avoir plusieurs redirections: cat < in > out
*/
typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

/*
** Structure d'une commande - liste chaînée (pour les pipes)
** args   = tableau de strings, args[0] = la commande, args[1+] = les arguments
** redirs = liste chaînée des redirections de cette commande
** next   = commande suivante (après un pipe)
**
** Exemple: "ls -la | grep foo > out"
** Donne 2 t_cmd:
**   cmd1: args=["ls", "-la"], redirs=NULL, next=cmd2
**   cmd2: args=["grep", "foo"], redirs=[REDIR_OUT, "out"], next=NULL
*/
typedef struct s_cmd
{
	char				**args;
	t_redir				*redirs;
	struct s_cmd		*next;
}	t_cmd;

/*
** Fonctions du lexer - transforme l'input en liste de tokens
** C'est la première étape: "ls -la | grep" -> [WORD:ls][WORD:-la][PIPE][WORD:grep]
*/
t_token			*lexer(char *input);
t_token			*new_token(t_token_type type, char *value);
void			add_token(t_token **list, t_token *new);
int				skip_whitespace(char *input, int i);
void			append_to_word(char **word, char *part);

/*
** Fonctions du parser - transforme les tokens en liste de commandes
** C'est la deuxième étape: [WORD:ls][PIPE][WORD:grep] -> cmd1 -> cmd2
*/
t_cmd			*parser(t_token *tokens);
t_cmd			*new_cmd(void);
void			add_cmd(t_cmd **list, t_cmd *new);
t_redir			*new_redir(t_redir_type type, char *file);
void			add_redir(t_redir **list, t_redir *new);
int				is_redir_token(t_token_type type);
int				count_args(t_token *tokens);
t_redir_type	token_to_redir_type(t_token_type type);
int				syntax_error(char *msg);

/*
** Utils - fonctions helper
*/
int				is_whitespace(char c);
int				is_special_char(char c);

#endif
