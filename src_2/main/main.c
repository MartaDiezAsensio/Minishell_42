/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:12:17 by mgaspar-          #+#    #+#             */
/*   Updated: 2024/01/06 16:02:22 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_2/main.h"

int	shell_loop(void)
{
	char	*prompt;
	char	*parsed_prompt;

	//signal(SIGINT, ft_signal_handler);
	//signal(SIGQUIT, ft_signal_handler);

	while (1)
	{
		prompt = readline("\n:) minishell> ");
		// wait for command
		parsed_prompt = prompt;
		// parse prompt
		if (!ft_strequals("exit", prompt))
			exit(EXIT_SUCCESS);
		if (!ft_strequals("pwd", prompt))
			printf("%s\n", getenv("PWD"));
		// if (!ft_strequals("cd", prompt))
		// if (!ft_strequals("export", prompt))
		// if (!ft_strequals("unset", prompt))
		// if (!ft_strequals("env", prompt))

		// if (!ft_strequals("echo", prompt))





		add_history(prompt);
		// execute command
		free(prompt);
	}
}

// int	main(int argc, char **argv, char **parent_env)
// {
// 	t_env	env;

// 	(void)argc;
// 	(void)argv;
// 	init_env(parent_env, &env);
// 	shell_loop();
// 	return (EXIT_SUCCESS);
// }
