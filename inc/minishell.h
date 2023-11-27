/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:07:43 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/11/27 16:52:41 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_BAD_ARGS 1

typedef struct s_input {
	// variables que ens calguin del environment?
}	t_input;



//*******************SIGNALS*******************//
void	ft_signal_handler(int sig);


//*******************LEXER*******************//

#endif



