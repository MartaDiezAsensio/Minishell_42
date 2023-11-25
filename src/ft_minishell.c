/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:28:48 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/11/25 14:39:31 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_minishell(char **env)
{
	// Minishell logic
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}