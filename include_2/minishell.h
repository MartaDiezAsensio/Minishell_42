/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:00:54 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/19 21:15:08 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/libft/libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
//# include "error_utils.h"

# define EXIT_SYNTAX_ERROR 258
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CTRL_D 130


#endif
