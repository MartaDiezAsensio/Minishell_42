/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:23:30 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/11 17:26:12 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Tokenizer

// Define token types
typedef enum {
	TOKEN_PROGRAM,
	TOKEN_ARGUMENT,
	TOKEN_END
} TokenType;

// Define structure for a token
typedef struct {
	TokenType	type;
	char		*value;
}	Token;

// Function to create a new token
Token	*createToken(TokenType type, char *value)
{
	Token	*newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return (NULL);
	newToken->type = type;
	newToken->value = strdup(value);
	return (newToken);
}

// Function to free memory from token
void	freeToken(Token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

// Function to print a token (Revise)
void	printToken(Token *token)
{
	if (!token)
		return ;
	printf("Type: %d, Value: %s\n", token->type, token->value);
}

// Function to tokenize a string

Token	*getNextToken(char **input)
{
	char	*start;
	char	*end;

	while (**input == ' ' || **input == '\t')
		(*input)++;
	if (**input == '\0')
		return (createToken(TOKEN_END, ""));

	if (**input == '\"')
	{
		(*input)++;
		start = *input;
		while (**input != '\"' && **input != '\0')
			(*input)++;
		if (**input == '\"')
			*(*input)++ = '\0';
		return (createToken(TOKEN_ARGUMENT, start));
	}
	else
	{
		start = *input;
		while (**input != '\0' && **input != '\t' && **input != ' ')
			(*input)++;
		end = *input;
		return (createToken(TOKEN_PROGRAM, strndup(start, end - start)));
	}
}

// Main function

int	main(int argc, char **argv)
{
	// char	command[] = "ls -l -a \"file name\"";
	// char	*input = command;

	Token	*token;

	token = getNextToken(&argv[1]);
	while (token->type != TOKEN_END)
	{
		printToken(token);
		freeToken(token);
		token = getNextToken(&argv[1]);
	}
	printToken(token);
	freeToken(token);

	return (0);
}
