/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/20 01:11:34 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(void)
{
	t_list	*env;

	env = *_list();
	while (env)
	{
		printf("export %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	builtin_export(char **arg)
{
	if (!arg[1])
	{
		print_export_env();
		return ;
	}
	env_add_node(arg[1], arg[2]);
}
