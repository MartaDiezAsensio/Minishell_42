/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:07:43 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/11 17:48:32 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"


#include <string.h>


# define EXIT_SUCCESS 0
# define EXIT_BAD_ARGS 1

typedef struct s_input {
	// variables que ens calguin del environment?
}	t_input;


//*******************SIGNALS*******************//
void	ft_signal_handler(int sig);


//*******************LEXER*******************//

#include <glob.h>
/*Si no es pot utilitzar aquesta llibreria es
pot recrear la funcio glob() des de 0 amb les funcions "legals"*/

enum token_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,

	TOKEN	= -1,
};

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,

	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

typedef struct tok t_tok;
typedef struct lexer t_lexer;

struct tok {
	char	*data;
	int		type;
	t_tok	*next;
};

struct lexer {
	t_tok	*list_tok;
	int		ntoks;
};

int		lexer(char *inut, int size, t_lexer *lexerbuf);
void	lexer_destroy(t_lexer *lexerbuf);

//*******************ASTREE*******************//
typedef enum {
	NODE_PIPE 			= (1 << 0), // 1
	NODE_BCKGRND 		= (1 << 1), // 2
	NODE_SEQ 			= (1 << 2), // 4
	NODE_REDIRECT_IN 	= (1 << 3), // 8
	NODE_REDIRECT_OUT 	= (1 << 4), // 16
	NODE_CMDPATH		= (1 << 5), // 32
	NODE_ARGUMENT		= (1 << 6), // 64
	NODE_DATA 			= (1 << 7), // 128
} node_type;

typedef struct s_tree_node	t_tree_node;

typedef struct s_tree_node {
	int			type;
	char		*sz_data;
	t_tree_node	*right;
	t_tree_node	*left;
}	t_tree_node;

#define NODE_TYPE(a) (a & (~NODE_DATA)) // get the type of noddes

void	tree_attach_branch(t_tree_node *root, t_tree_node *left, t_tree_node *right);
void	tree_node_set_type(t_tree_node *node, node_type type);
void	tree_node_set_data(t_tree_node *node, char *data);
void	tree_node_delete(t_tree_node *node);

//*******************PARSER*******************//

int	parse(t_lexer *lexerbuf, t_tree_node **syntax_tree);

#endif



