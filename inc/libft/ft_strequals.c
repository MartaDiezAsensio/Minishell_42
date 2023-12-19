/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:22 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/19 20:38:40 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequals(char *str1, char *str2)
{
	size_t	len1;

	len1 = ft_strlen(str1);
	if (len1 != ft_strlen(str2))
		return (1);
	return (ft_strncmp(str1, str2, len1));
}
