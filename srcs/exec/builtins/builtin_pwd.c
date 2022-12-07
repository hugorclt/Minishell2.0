/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:57:02 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/05 16:19:34 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char **arg)
{
	char	cwd[PATH_MAX];
	
	(void)arg;
	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	update_last_cmd_status(SUCCESS);
}
