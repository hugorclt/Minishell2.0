/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:23:53 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/08 23:08:08 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_env_error(char **arg)
{
	if (arg[1])
	{
		dprintf(STDERR, "mimishell: env: '%s': No such file or directory\n",
					arg[1]);
		update_last_cmd_status(NOT_FOUND);
	}
}

void	builtin_env(char **arg)
{
	t_list	*env;

	env = *_list();
	check_env_error(arg);
	if (get_last_cmd_status() == NOT_FOUND)
		return ;
	while (env)
	{
		if (!env->value)
			printf("%s\n", env->key);
		else
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	update_last_cmd_status(SUCCESS);
}
