/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:41:58 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/01 19:12:28 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
<command line>:

Represents a command line, which is the top-level construct.
It can be a <job> followed by a semicolon and another <command line> (<job> ';' <command line>).
It can be a <job> followed by a semicolon (<job> ';').
It can be a <job> followed by an ampersand and another <command line> (<job> '&' <command line>).
It can be a <job> followed by an ampersand (<job> '&').
It can also simply be a <job>.
<job>:

Represents a job, which can be a <command> followed by a pipe symbol and another <job> (<command> '|' <job>).
Alternatively, it can be just a <command>.
<command>:

Represents a command, which can be a <simple command> followed by a less-than symbol and a <filename>.
Alternatively, it can be a <simple command> followed by a greater-than symbol and a <filename>.
Alternatively, it can be just a <simple command>.
<simple command>:

Represents a simple command, which can be a <pathname> followed by a <token list>.
<token list>:

Represents a list of tokens, which can be a <token> followed by another <token list>.
Alternatively, it can be empty ((EMPTY)).
*/

// Definitions 

t_tree_node	*CMDLINE();			// all commandline
t_tree_node	*CMDLINE1();		// <job> ; <commandline>
t_tree_node	*CMDLINE2();		// <job> ;
t_tree_node	*CMDLINE3();		// <job> & <commandline>
t_tree_node	*CMDLINE4();		// <job> &
t_tree_node	*CMDLINE5();		// <job>

t_tree_node	*JOB();				// test all jobs
t_tree_node	*JOB1();			// <command> | <job>
t_tree_node	*JOB2();			// <command>

t_tree_node	CMD();				// test all commands
t_tree_node	CMD1();				// <simple command> < <filename>
t_tree_node	CMD2();				// <simple command> > <filename>
t_tree_node	CMD3();				// <simple command>

t_tree_node	SIMPLE_COMMAND();	// test sismple commands
t_tree_node	SIMPLE_COMMAND1();	// <pathname> <tokenlist>

t_tree_node	TOKEN_LIST();		// test tokenlist
t_tree_node	TOKEN_LIST1();		// <token> <token list>
t_tree_node	TOKEN_LIST2();		// EMPTY


// current token pointer ** Variable global con optencial de estar prohibida. 
t_tok	*curr_tok;
//curr_tok = NULL;

int	term(int token_type, char **buffer_ptr)
{
	if (curr_tok == NULL)
		return (0);
	if (curr_tok->type == token_type)
	{
		if (buffer_ptr != NULL)
		{
			*buffer_ptr = malloc(strlen(curr_tok->data) + 1);
			if (!buffer_ptr)
				return (-1);
			strcpy(*buffer_ptr, curr_tok->data);
		}
		curr_tok = curr_tok->next;
		return (1);
	}
	curr_tok = curr_tok->next;
	return (0);
}

t_tree_node	*CMDLINE()
{
	t_tok		*save;
	t_tree_node	*node;

	save = curr_tok;
	if (curr_tok = save, node = CMDLINE1() != NULL)
		return (node);
	if (curr_tok = save, node = CMDLINE2() != NULL)
		return (node);
	if (curr_tok = save, node = CMDLINE3() != NULL)
		return (node);
	if (curr_tok = save, node = CMDLINE4() != NULL)
		return (node);
	if (curr_tok = save, node = CMDLINE5() != NULL)
		return (node);
	return (NULL);
}



int	parse(t_lexer *lexerbuf, t_tree_node **syntax_tree)
{

} 