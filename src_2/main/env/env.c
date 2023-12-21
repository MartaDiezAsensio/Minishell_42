/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaspar- <mgaspar-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:00:14 by mgaspar-          #+#    #+#             */
/*   Updated: 2023/12/19 21:15:48 by mgaspar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_2/main.h"

int	init_env(char **parent_env, t_env *env)
{
	char	*env_var;
	int		n_vars;

	// copy every str pointer in parent_env to env->env
	n_vars = 0;
	while (parent_env[n_vars])
		n_vars++;
	env->env = (char **)malloc(n_vars * sizeof(char *));
	if (!env->env)
		return (EXIT_FAILURE);
	env_var = *parent_env;

}

char	*query_env(char *var_name, t_env *env)
{

}

