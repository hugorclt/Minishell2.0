/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:53:28 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/21 21:20:43 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	too_many_arg(void)
{
	dprintf(STDERR, "mimishell: cd: too many arguments\n");
	update_last_cmd_status(FAILURE);	
}

static void	erno_error(char *arg)
{
	if (errno == ENOENT)
		dprintf(STDERR, "mimishell: cd: %s: No such file or directory\n", arg);
	else if (errno == EACCES)
		dprintf(STDERR, "mimishell: cd: %s: Permission denied\n", arg);
	update_last_cmd_status(FAILURE);
}

static void	check_cd_error(char **arg)
{
	if (arg[1] && arg[2])
		too_many_arg();
	else if (chdir(arg[1]) == FAILURE)
		erno_error(arg[1]);
	else
		update_last_cmd_status(SUCCESS);
}

static void	update_pwds(char **arg)
{
	char	*cwd[PATH_MAX];
	
	chdir(arg);
	env_change_value("OLDPWD", env_get_value("PWD"));
	env_change_value("PWD", getcwd(cwd, PATH_MAX));
}

void	builtin_cd(char **arg)
{
	t_data	*data;
	
	data = _data();
	check_error_cd(arg);
	if (data->last_cmd_status == FAILURE)
		return ;
	if (!arg[1])
		chdir(getenv("HOME"));
	else
		update_pwds(arg);
}