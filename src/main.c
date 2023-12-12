/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:07:14 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/12 17:15:57 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	shell_loop(t_input *input)
{
	(void)input;
	char	*prompt;
	char	*parsed_prompt;

	//signal(SIGINT, ft_signal_handler);
	//signal(SIGQUIT, ft_signal_handler);

	while (1)
	{
		printf("\n:) minishell> ");
		// display prompt
		prompt = readline(NULL);
		// wait for command
		parsed_prompt = prompt;
		// parse prompt
		if (ft_strlen(prompt) == 4 && !ft_strncmp("exit",prompt,4))
			exit(0);
		if (ft_strlen(prompt) == 3 && !ft_strncmp("pwd", prompt, 3))
			printf("%s\n", getenv("PWD"));
		add_history(prompt);
		// execute command
		free(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_input	input;
	int		exit_code;

	(void)argc;
	(void)argv;

	int i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	exit_code = shell_loop(&input);
	//cleanup??
	if (exit_code)
		return (exit_code);
	return (EXIT_SUCCESS);
}
