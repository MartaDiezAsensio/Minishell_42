/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:58:25 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/28 20:18:53 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_2/minishell.h"
#include "../../include_2/main.h"
#include "../../include_2/lexer_utils.h"

/**
 * @brief frees tokens and adjusted tokens
 * 
 * @param tokens 
 * @param adjusted 
 * @return void* (NULL)
 */
static void	*free_tokens(char **tokens, char **adjusted)
{
	ft_free_split(tokens);
	ft_free_split(adjusted);
	reset_lex_toks();
	return (NULL);
}

/**
 * @brief	Get the next token object
 * 			Extracts a sequence of consecutive characters (run) from the beggining of a token
 * 			1. (Determine special)
 * 			2. If the character *tmp is the same as the ddeermined "next_speial" character,
 * 			a loop is entered to copy the consecutive identical characters into next_token
 * 			3. A new token tmp is created by extracting the remaininng characters into next_token  
 * 
 * @param token 
 * @return char * (next_token)
 */
static char	*get_next_token(char **token)
{
	char	*next_token;
	char	*tmp;
	char	next_special;
	int		i;

	tmp = *token;
	// Determine the special character that constitutes the run
	next_special = get_next_special(tmp);
	// Allocate memory for the next_token
	next_token = ft_calloc(get_next_token_size(tmp, next_special) + 1, \
			sizeof(*next_token));
	if (!next_token)
		return (NULL);
	
	i = 0;
	// If the current char is the next_special char, copy the run
	if (*tmp == next_special)
		while (*tmp && *tmp == next_special)
			next_token[i++] = *tmp++;
	
	// Create a new token without the extracted run
	tmp = ft_substr(*token, i, ft_strlen(*token));
	if (*token == NULL)
		return (ft_free((void **)&next_token));
	// Free the original token and update it to the new token
	free(*token);
	*token = tmp;
	return (next_token);
}

/**
 * @brief	Get the subshell token object
 * 			Extracts and concatenates tokens that belong to a subshell.
 * 
 * @param tokens 
 * @param i (i[0] index)
 * @return char* (subshell token)
 */
static char	*get_subshell_token(char *tokens[], int *i)
{
	char	*subshell_token;
	int		subshell_count;

	subshell_token = NULL;
	subshell_count = get_subshell_count(tokens, *i); // determine count of subshells at a given position of the array.
	while (tokens[*i] && subshell_count)
	{
		// Check if this is the last token of the subshell
		if (subshell_count == 1 && ft_strchr(tokens[*i], ')') \
		&& ft_strlen(ft_strrchr(tokens[*i], ')')) != 1)
			return (get_end_of_subshell(tokens, i, subshell_token));
		// Append the curren token to the subshell_token
		subshell_token = ft_append(&subshell_token, tokens[*i]);
		if (!subshell_token)
			return (NULL);
		// Adjust the subshell count based on the presence on '(' or ')'
		if (ft_strchr(tokens[*i], '(') || ft_strchr(tokens[*i], ')'))
			subshell_count--;
		(*i)++;
	}
	return (subshell_token);
}

/**
 * @brief	Token adjustment based on these conditions:
 * 				1. If the first character of a token is '(', the function assumes it is the start of a subshell.
 * 				2. If a token is not the start of a subshell and is not considered unadjusted, the function duplicates the token using ft_strdup.
 * 				3. If a token is unadjusted, the function calls get_next_token to obtain the next token.
 * 
 * @param tokens 
 * @return char** (adjusted tokens)
 */
static char	**adjust_tokens(char **tokens)
{
	char	**adjusted;
	size_t	adjusted_size;
	int		i[2];

	adjusted_size = 50;
	adjusted = ft_calloc(adjusted_size + 1, sizeof(*adjusted));
	if (!adjusted)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (tokens[i[0]])
	{
		if (tokens[i[0]][0] == '(')
			adjusted[i[1]] = get_subshell_token(tokens, &i[0]);
		else if (!token_is_unadjusted(tokens[i[0]]))
			adjusted[i[1]] = ft_strdup(tokens[i[0]++]);
		else
			adjusted[i[1]] = get_next_token(&tokens[i[0]]);

		if (adjusted[i[1]++] == NULL)
			return (free_tokens(tokens, adjusted));

		if ((size_t)i[1] == adjusted_size - 1)
			adjusted = ft_str_arr_realloc(adjusted, adjusted_size += 10);
	}
	ft_free_str_array(&tokens);
	return (adjusted);
}

/**
 * @brief	1. checks line syntax
 * 			2. split, creates tokens from line
 * 			3. (join quotes) exit if it fails
 * 			4. (adjust tokens) exit if it fails
 * 			5. (set lex)
 * 			6. check token syntax
 * 			7. Exit status, reurn, = parser
 * 			8. (reset lex)
 * 
 * @param line 
 * @return int (status)
 */
int	lexer(char *line)
{
	char	**tokens;
	int		exit_status;

	if (!is_valid_line_syntax(line))
		return (exit_on_syntax_error());

	tokens = ft_split_set(line, " \t\r\v\f\n");

	if (join_quotes(&tokens) == EXIT_FAILURE)
	{
		ft_free_str_array(&tokens);
		return (EXIT_FAILURE);
	}

	tokens = adjust_tokens(tokens);
	if (tokens == NULL)
		return (EXIT_FAILURE);

	set_lex_toks(tokens);
	if (!is_valid_syntax(tokens))
		return (exit_on_syntax_error());

	exit_status = parser(tokens);

	ft_free_split(tokens);
	reset_lex_toks();
	return (exit_status);
}
