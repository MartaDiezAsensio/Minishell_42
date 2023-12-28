/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:20:54 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/28 20:38:08 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

/**
 * @brief Exit on syntax error and free
 * 
 * @return int (exit status)
 */
int	exit_on_syntax_error(void)
{
	ft_fprintf(2, "minishell: Invalid Syntax at token\n");
	set_err_code(EXIT_SYNTAX_ERROR);
	ft_free_split(get_lex_toks());
	return (EXIT_SYNTAX_ERROR);
}

/**
 * @brief	If the conditions are met (i.e., the character at 
 * 			position i is not '&' and not '|'), the function returns true. 
 * 			Otherwise, it returns false.
 * 
 * @param line 
 * @param i 
 * @return true (if there are & or | chars)
 * @return false (if not)
 */
static bool	is_correct_subshell(char *line, int i)
{
	// Move back through whitespace chars
	while (i > 0 && line[i] && ft_isspace(line[i]))
		i--;
	// Check if cha at pos i is not '&' or '|'
	if (i >= 0 && (line[i] != '&' && line[i] != '|'))
		return (false);
	return (true);
}

/**
 * @brief chck if line at position i has opening brackets.
 * 
 * @param line 
 * @param i 
 * @return true 
 * @return false 
 */
static bool	has_opening_bracket(char *line, int i)
{
	while (i > 0 && line[i] && line[i] != '(')
		i--;
	if (i >= 0 && line[i] != '(')
		return (false);
	return (true);
}

/**
 * @brief	Count the occurrences of a character 'c' whithin the line.
 * 			Skips counting occurences of characters within single or double quotes.
 * 
 * @param line 
 * @param c 
 * @return int (c occurences)
 */
static int	count_subshell_chars(char *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		// If the current character is a single quote ('), skip characters until the next single quote
		if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		// Same for doubble quotes
		if (line[i] == '\"')
			while (line[++i] && line[i] != '\"')
				;
		if (line[i] == c)
			count++;
		if (line[i])
			i++;
	}
	return (count);
}

/**
 * @brief	Checks syntax of line.
 * 			It primarily focuses on ensuring balanced parentheses and checks for 
 * 			specific conditions related to single quotes, double quotes, parentheses,
 * 			semicolons, and backslashes.
 * 
 * @param line 
 * @return true 
 * @return false 
 */
bool	is_valid_line_syntax(char *line)
{
	int	i;

	i = 0;
	// Check weether all opened brackets are closed
	if (count_subshell_chars(line, '(') != count_subshell_chars(line, ')'))
		return (false);
	
	while (line[i])
	{
		// Check if quotes are properly closed
		if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		if (line[i] == '\"')
			while (line[++i] && line[i] != '\"')
				;
		if (line[i] == '(')
			if (!is_correct_subshell(line, i - 1))
				return (false);
		if (line[i] == ')')
			if (!has_opening_bracket(line, i - 1))
				return (false);
		if (line[i] == ';' || line[i] == '\\')
			return (false);
		if (line[i])
			i++;
	}
	return (true);
}

// int	main()
// {
// 	char	line[] = "echo Hello";
// 	char	c = 'l';
// 	int		i = 5;
// 	int		count;
// 	bool	res;

// 	count = count_subshell_chars(line, c);
// 	//res = has_opening_bracket(line, i);

// 	res = is_correct_subshell(line, c);
// 	printf("res = %d\n", res);
// }

