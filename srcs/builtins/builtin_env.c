/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:23:53 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/20 00:44:29 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(char **arg)
{
	t_list *env;

	(void)arg; /* si on envoie env 3 doit on afficher une erreur ?*/
	env = *_list();
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
