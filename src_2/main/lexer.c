/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:58:25 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/19 18:54:09 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_2/minishell.h"
#include "../../include_2/main.h"
#include "../../include_2/lexer_utils.h"

// int	lexer(char *line)
// {
// 	char	**tokens;
// 	int		exit_status;

// 	if (!is_valid_line_syntax(line))
// 		return (exit_on_syntax_error());

// 	tokens = ft_split_set(line, " \t\r\v\f\n");

// 	if (join_quotes(&tokens) == EXIT_FAILURE)
// 	{
// 		ft_free_str_array(&tokens);
// 		return (EXIT_FAILURE);
// 	}

// 	tokens = adjust_tokens(tokens);
// 	if (tokens == NULL)
// 		return (EXIT_FAILURE);

// 	se_lex_toks(tokens);
// 	if (!is_valid_syntax(tokens))
// 		return (exit_on_syntax_error());

// 	exit_status = parser(tokens);

// 	ft_free_split(tokens);
// 	reset_lex_toks();
// 	return (exit_status);
// }
