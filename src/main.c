/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:07:14 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/11/25 14:49:32 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_input(t_input *input)
{
	// get env info we need??
}

int	shell_loop(t_input *input)
{
	char	*prompt;
	char	*parsed_prompt;

	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);

	while (1)
	{
		printf("\n:) minishell> ");
		// display prompt
		prompt = readline(NULL);
		// wait for command
		parsed_prompt = prompt;
		// parse prompt
		printf("prompt i got: %s", parsed_prompt);
		// execute command
		free(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_input	input;
	int		exit_code;

	init_input(&input);
	exit_code = shell_loop(&input);
	//cleanup??
	if (exit_code)
		return (exit_code);
	return (EXIT_SUCCESS);
}
