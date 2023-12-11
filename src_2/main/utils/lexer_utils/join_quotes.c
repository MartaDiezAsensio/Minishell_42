/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:05:55 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/11 18:17:30 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

// int	join_quotes(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	if (*tokens == NULL)
// 		return(EXIT_FAILURE);
// 	while ((*tokens)[i])
// 	{
// 		if ((*tokens)[i] && (ft_strhas((*tokens)[i], "\'\"") == true))
// 		{
// 			if (token_join(tokens, i) == EXIT_FAILURE)
// 				return (EXIT_FAILURE);
// 			else
// 			{
// 				if (ft_strhas((*tokens)[i], "\'\"") == false)
// 			}
// 		}
// 		else
// 			i++;
// 	}
// }