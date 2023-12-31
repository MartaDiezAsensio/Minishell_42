/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:43:10 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/12 19:35:01 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_2/minishell.h"

/**
 * Que ha de rebre el expander
 * hauria de rebre un "arbre" amb tokens d'execucio
 * substituir les variables d'entorn i preparar pipes
 * per que el executor executi coses...
 *
 * Quina pinta hauria de tenir un output del parser
 * per aquests prompts:
 * 	:) minishell> ls -la
 *
 *  :) minishell> echo $SHELL
 *
 * 	:) minishell> echo hola > test.txt
 *
 * 	:) minishell> cd ..
 *
 * 	:) minishell> echo hola | cat
 *
 * **/

