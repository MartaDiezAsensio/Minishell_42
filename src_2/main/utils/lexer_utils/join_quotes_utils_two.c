/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:56:23 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/28 12:00:11 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_2/minishell.h"
#include "../../../../include_2/main.h"
#include "../../../../include_2/lexer_utils.h"

int	combine_loop(char ***tokens, t_quotes *quo)
{
	while (*tokens && (*tokens)[quo->i]
		&& ft_strhas((*tokens)[quo->i], quo->quote) == false)
	{
		(*tokens)[quo->j] = ft_strstrjoin((*tokens)[quo->j],
				(*tokens)[quo->i], " ");
		if ((*tokens)[quo->j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(tokens, quo->i);
	}
	return (EXIT_SUCCESS);
}

int	token_join_end_one(char ***tokens, t_quotes *quo)
{
	quo->end = ft_strdup((*tokens)[quo->i]);
	if (quo->end == NULL)
		return (EXIT_FAILURE);
	quo->len = ft_strclen(quo->end, *quo->quote) + 1;
	(*tokens)[quo->j] = ft_append_len_div(&(*tokens)[quo->j],
			quo->end, quo->len, " ");
	if ((*tokens)[quo->j] == NULL)
		return (EXIT_FAILURE);
	if (quo->end[quo->len] == '\0')
		ft_free_single_str(tokens, quo->i);
	else
	{
		ft_free_str(&(*tokens)[quo->i]);
		(*tokens)[quo->i] = ft_strdup(quo->end + quo->len);
		if ((*tokens)[quo->i] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
