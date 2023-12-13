/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:30:42 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/13 14:22:48 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

bool	is_quote_token(char *lex_tok);

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
	if (ft_strlen(lex_tok) == 2 && special_kind == 3)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||"))
			return (true);
	}
	return (false);
}
