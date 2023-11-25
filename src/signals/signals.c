/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:51:03 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/11/25 14:10:40 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

void	handle_ctr_c(int signal)
{
	// Display a new promp on a new line
	// Call ft_minishell
	printf("\n");
}

void	handle_ctr_d(int signal)
{
	printf("Exiting the program\n");
	// Clean minishell, free, close processes
	return ;
}

void	handle_ctr_backslash(int signal)
{
	// Nothing to do here
}

int	main()
{
	signal(SIGINT, handle_ctr_c);
	signal(SIGINT, handle_ctr_d);
	signal(SIGINT, handle_ctr_backslash);

	// while minishell
	while (1)
	{
		printf("Doing something..\n");
		sleep(2);
	}

	return (0);
}