/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:07:43 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/11/30 20:16:14 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

//*******************PARSER*******************//

#endif



