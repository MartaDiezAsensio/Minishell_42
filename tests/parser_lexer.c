/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:54:49 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/04 18:17:18 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// Define structure for node in parse tree
typedef struct TreeNode {
	char			*value;
	struct TreeNode	*children[10];
}	TreeNode;

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

// Function to create a new node in the parse tree
TreeNode	*createNode(char *value)
{
	int	i;

	i = 0;
	TreeNode	*node = (TreeNode *)malloc(sizeof(TreeNode));
	if (!node)
		return (NULL);
	node->value = strdup(value);
	while (i < 10)
	{
		node->children[i] = NULL;
		i++;
	}
	return (node);
}

// Function to free a node
void	freeParseTree(TreeNode *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	while (i < 10)
	{
		freeParseTree(root->children[i]);
		i++;
	}
	free(root->value);
	free(root);
}

// Functiton to print the parse tree
void printParseTree(TreeNode *root, int level) {
	if (root == NULL) {
		return;
	}
	for (int i = 0; i < level; i++) {
		printf("  ");  // Print indentation for better visualization
	}
	printf("%s", root->value);

	// Print arguments for the "Program" node
	if (strcmp(root->value, "Program") == 0) {
		int i = 0;
		while (root->children[i] != NULL) {
			printf("\n");
			printf("%s\n", root->children[i]->value);
			printParseTree(root->children[i], level + 1);
			i++;
		}
	}

	printf("\n");
}

// Recursive descent parser
TreeNode	*parseProgram(Token **tokens);

// Function to parse a command string and build a parse tree
TreeNode *parseCommand(Token **tokens) {
    // Create a new node for the program
    TreeNode *programNode = createNode("Program");

    // Parse the program name
    TreeNode *programNameNode = parseProgram(tokens);
    if (programNameNode == NULL) {
        fprintf(stderr, "Error: Failed to parse program name\n");
        freeParseTree(programNode);
        return NULL;
    }
    programNode->children[0] = programNameNode;

    // Parse the arguments
    int argumentIndex = 1;
    while ((*tokens)->type == TOKEN_ARGUMENT) {
        // Parse each argument
        TreeNode *argumentNode = parseProgram(tokens);
        if (argumentNode == NULL) {
            fprintf(stderr, "Error: Failed to parse argument\n");
            freeParseTree(programNode);
            return NULL;
        }
        programNode->children[argumentIndex++] = argumentNode;
    }

    return programNode;
}

TreeNode	*parseProgram(Token **tokens)
{
	TreeNode	*programNode;
	Token		*programToken;
	TreeNode	*programNameNode;
	int			argumentIndex;
	TreeNode	*argumentNode;

	programNode = createNode("Program");
	programToken = *tokens;
	if (programToken->type != TOKEN_PROGRAM)
	{
		printf("Error: Expected a program name token.\n");
		return (NULL);
	}

	programNameNode = createNode(programToken->value);
	programNode->children[0] = programNameNode;

	(*tokens)++;

	argumentIndex = 1;
	while ((*tokens)->type == TOKEN_ARGUMENT)
	{
		argumentNode = createNode((*tokens)->value);
		programNode->children[argumentIndex++] = argumentNode;
		(*tokens)++;
	}

	return (programNode);
}

int main() {
	char command[] = "ls -l -a \"file name\"";

	// Tokenize the command string
	char *input = command;
	Token *tokens[20];  // Assuming a maximum of 20 tokens for simplicity
	int tokenIndex = 0;

	Token *token;
	do {
		token = getNextToken(&input);
		tokens[tokenIndex++] = token;
	} while (token->type != TOKEN_END);

	// Reset the input for the parser
	input = command;

	// Parse the command and build the parse tree
	TreeNode *parseTree = parseCommand(tokens);

	// For debugging purposes, print the parse tree
	printf("Parse Tree:\n");
	printParseTree(parseTree, 0);

	// Free the memory used by the parse tree and tokens
	freeParseTree(parseTree);
	for (int i = 0; i < tokenIndex; i++) {
		freeToken(tokens[i]);
	}

	return 0;
}
