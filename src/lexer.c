/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:10:15 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/01 17:55:08 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_char_type(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '0')
		return (CHAR_NULL);
	else
		return (CHAR_GENERAL);
}

void	delete_quotes(char *src, char *dst)
{
	int		n;
	int		i;
	int		j;
	char	last_quote;
	char	c;

	n = ft_strlen(src);
	i = 0;
	j = 0;
	last_quote = 0;
	if (n <= 1)
	{
		strcpy(dst, src);
		return ;
	}
	while (i < n)
	{
		c = src[i];
		if ((c == '\'' || c == '\"') && last_quote == 0)
			last_quote = c;
		else if (c == last_quote)
			last_quote = 0;
		else
			dst[j++] = c;
		i++;
	}
	dst[j] = 0;
}

void	tok_init(t_tok *tok, int datasize)
{
	tok->data = malloc(sizeof(int) * (datasize + 1));
	if (!tok->data)
	{
		printf("Error in tok malloc\n");
		return ;
	}
	tok->data[0] = 0;
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

void	tok_destroy(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

int	lexer(char *input, int size, t_lexer *lexerbuf)
{
	int		i;
	int		j;
	char	c;
	int		state;
	int		chtype;
	int		ntemtok;
	t_tok	*token;

	i = 0;
	j = 0;
	ntemtok = 0;
	state = STATE_GENERAL;
	if (lexerbuf == NULL)
		return (-1);
	if (size == 0)
	{
		lexerbuf->ntoks = 0;
		return (0);
	}
	lexerbuf->list_tok = malloc(sizeof(t_tok));
	if (!lexerbuf->list_tok)
	{
		printf("Error in malloc of token list\n");
		return (-2);
	}
	token = lexerbuf->list_tok;
	tok_init(token, size);



	// Separarlo en otra funcion
	while (input[i] != '\0')
	{
		chtype = get_char_type(input[i]);
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QUOTE)
			{
				state = STATE_IN_QUOTE;
				token->data[j++] = CHAR_QUOTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				token->data[j++] = CHAR_DQUOTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_ESCAPESEQUENCE)
			{
				token->data[j++] = input[++i];
				token->type = TOKEN;
			}
			else if (chtype == CHAR_GENERAL)
			{
				token->data[j++] = input[i];
				token->type = TOKEN;
			}
			else if (chtype == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_tok));
					if (!token->next)
						return (-1);
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
			}
			else if (chtype == CHAR_SEMICOLON)
				continue ;
			else if (chtype == CHAR_GREATER)
				continue ;
			else if (chtype == CHAR_LESSER)
				continue ;
			else if (chtype == CHAR_AMPERSAND)
				continue ;
			else if (chtype == CHAR_PIPE)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_tok));
					if (!token->next)
						return (-1);
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				token->data[0] = chtype;
				token->data[1] = 0;
				token->type = chtype;
				token->next = malloc(sizeof(t_tok));
				if (!token->next)
						return (-1);
				token = token->next;
				tok_init(token, size - i);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = input[i];
			if (chtype == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = input[i];
			if (chtype == CHAR_QUOTE)
				state = STATE_GENERAL;
		}
		if (chtype == CHAR_NULL)
		{
			if (j > 0)
			{
				token->data[j] = 0;
				ntemtok++;
				j = 0;
			}
		}
		i++;
	}

	// Separarlo en otra funcion

	int		k;
	//int		i;
	t_tok	*saved;
	char	*deleted;

	k = 0;
	token = lexerbuf->list_tok;
	while (token != NULL)
	{
		if (token->type == TOKEN)
		{
			//*****************CUSTOM GLOB*******************//
			glob_t	globbuf;
			glob(token->data, GLOB_TILDE, NULL, &globbuf);

			if (globbuf.gl_pathc > 0)
			{
				k += globbuf.gl_pathc;
				// Save the next token so we can adde it later
				saved = token->next;

				// replace the current token with the first one
				free(token->data);
				token->data = malloc(ft_strlen(globbuf.gl_pathv[0]) + 1);
				if (!token->data)
					return (-1);
				ft_strcpy(token->data, globbuf.gl_pathv[0]);
				i = 1;
				while (i < globbuf.gl_pathc)
				{
					token->next = malloc(sizeof(t_tok));
					if (!token->next)
						return (-1);
					tok_init(token->next, ft_strlen(globbuf.gl_pathv[i]));
					token = token->next;
					token->type = TOKEN;
					ft_strcpy(token->data, globbuf.gl_pathv[i]);
					i++;
				}
				token->next = saved;
			}
			else
			{
				// token might be inside quotation, hence delete the quotation symbol
				deleted = malloc(ft_strlen(token->data) + 1);
				if (!deleted)
					return (-1);
				delete_quotes(token->data, deleted);
				free(token->data);
				token->data = deleted;
				k++;
			}
		}
		token = token->next;
	}
	lexerbuf->ntoks = k;
	return (k);
}

void	lexer_destroy(t_lexer *lexerbuf)
{
	if (lexerbuf == NULL)
		return ;
	tok_destroy(lexerbuf->list_tok);
}

//**************************************************//

// void print_tokens(t_tok *tokens) {
// 	t_tok *current = tokens;

// 	while (current != NULL && current->type != CHAR_NULL) {
// 		printf("Token Data: %s\tType: %d\n", current->data, current->type);
// 		current = current->next;
// 	}
// }


// int main() {

// 	// Initialize lexer buffer
// 	t_lexer	*lexerbuf;
// 	lexerbuf->list_tok = NULL;
// 	lexerbuf->ntoks = 0;

// 	printf("Number of tokens: %d\n", lexer("echo \"hello\" | ls -la", strlen("echo \"hello\" | ls -la"), lexerbuf));
// 	print_tokens(lexerbuf->list_tok);
// 	lexer_destroy(lexerbuf);

// 	return 0;
// }