/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:27:21 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/11 18:31:30 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

typedef struct s_quotes
{
	int		i;
	int		j;
	int		len;
	char	*start;
	char	*end;
	char	*quote;
}	t_quotes;

#endif
