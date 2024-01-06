/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:30:42 by mdiez-as          #+#    #+#             */
/*   Updated: 2024/01/06 17:05:11 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

/*************************************************************/
bool	is_quote_token(char *lex_tok)
{
	if (ft_strchr(lex_tok, '\'') || ft_strchr(lex_tok, '\"'))
		return (true);
	return (false);
}
/*************************************************************/

bool	is_quote_token(char *lex_tok);

/**
 * @brief	Boolean function to check if the token is a single or double redirection.
 * 
 * @param lex_tok 
 * @return true 
 * @return false 
 */
static bool	is_redir(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (true);
	}
	if (ft_strlen(lex_tok) == 1)
	{
		if (ft_strstr(lex_tok, '<') || ft_strstr(lex_tok, '>'))
			return (true);
	}
	return (false);
}

/**
 * @brief	Boolean function to check if the token has a special character.
 * 			If the special character is set to 0, the function will check all
 * 			special characters.
 * 
 * @param lex_tok 
 * @param special_kind 
 * @return true 
 * @return false 
 */
static bool	is_special(char *lex_tok, int special_kind)
{
	if (ft_strlen(lex_tok) == 1 && special_kind == 0)
	{
		if ((ft_strstr(lex_tok, '<') && !ft_strstr(lex_tok, "<<")) \
		|| (ft_strstr(lex_tok, '>') && !ft_strstr(lex_tok, ">")) \
		|| (ft_strstr(lex_tok, '|') && !ft_strstr(lex_tok, "||")))
			return (true);
	}
	if (ft_strlen(lex_tok) == 2 && special_kind == 0)
	{
		if (ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (true);
	}
	// Part of bonus
	if (ft_strlen(lex_tok) == 2 && special_kind == 3)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||"))
			return (true);
	}
	return (false);
}

/**
 * @brief	Boolean function that checks if the lex_tok has some incorrect 
 * 			combination of special characters.
 * 
 * @param lex_tok 
 * @return true 
 * @return false 
 */
static bool	is_correct_special(char *lex_tok)
{
	if (lex_tok[0] == '(' && ft_strchr(lex_tok, ')'))
		return (true);
	if (ft_strlen(lex_tok) != 2)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||") \
		|| ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (false);
		if (ft_strchr(lex_tok, '&'))
			return (false);
	}
	if (ft_strlen(lex_tok) != 1)
	{
		if ((ft_strchr(lex_tok, '<') && !ft_strstr(lex_tok, "<<"))\
		|| (ft_strchr(lex_tok, '>') && !ft_strstr(lex_tok, ">>")) \
		|| (ft_strchr(lex_tok, '|') && !ft_strstr(lex_tok, "||")))
			return (false);
	}
	return (true);
}

/**
 * @brief	Checks if the token after pipe is correct (is not && || or null)
 * 
 * @param curr 
 * @param next 
 * @return true 
 * @return false 
 */
static bool	is_correct_pipe(char *curr, char *next)
{
	if (ft_strlen(curr) == 1 && ft_strchr(curr, '|'))
	{
		if (next == NULL)
			return (false);
		if (ft_strlen(next) == 2)
		{
			if (ft_strstr(next, "&&") || ft_strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

/**
 * @brief	Checks the syntax for the array of tokens.
 * 
 * @param lex_toks 
 * @return true 
 * @return false 
 */
// bool	is_valid_syntax(char *lex_toks[])
// {
// 	int	i;

// 	i = 0;
// 	while (lex_toks[i])
// 	{
// 		if (!is_quote_token(lex_toks[i]))
// 		{
// 			if (i == 0 || get_lex_toks()[i + 1] == NULL)
// 				if (ft_strlen(lex_toks[i]) == 2 && (ft_strstr(lex_toks[i], "&&")
// 						|| ft_strstr(lex_toks[i], "||")))
// 					return (false);
// 			if (get_lex_toks()[i + 1] == NULL)
// 				if (is_redir(lex_toks[i]))
// 					return (false);
// 			if (!is_correct_special(lex_toks[i]))
// 				return (false);
// 			if (!is_correc_pipe(lex_toks[i], lex_toks[i + 1]))
// 				return (false);
// 			if (ft_strchr(lex_toks[i], '(') && ft_strchr(lex_toks[i], ')'))
// 				if (i != 0 && is_special(lex_toks[i - 1], 0))
// 					return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }
