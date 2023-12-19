/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:58:24 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/19 18:48:58 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_2/minishell.h"
#include "../../include_2/main.h"

int	executor() {return 0;}

// int main(int argc, char **argv, char** env)
// {
// 	// echo $SHELL
// 	char **args = malloc(2*sizeof(char*));
// 	*args = argv[0];
// 	*(args + 1) = getenv("SHELL");
// 	execve("/bin/echo", args, env);

// 	// echo hola > test.txt
// 	int fd = open("test.txt", O_RDWR | O_CREAT);
// 	if (fd == -1)
// 	{
// 		printf("open failed");
// 		return 0;
// 	}
// 	dup2(fd, STDOUT_FILENO);
// 	*(args + 1) = "hola";
// 	// en el path hauria d'anar el path al executable del nostre builtin?
// 	execve("/bin/echo", args, env);
// 	return (0);
// }

/**
 * 	:) minishell> ls -la
 *
 *  :) minishell> echo $SHELL
 *
 * 	:) minishell> echo hola > test.txt
 *
 * 	:) minishell> cd ..
 *
 * 	:) minishell> echo hola | cat
 * **/
