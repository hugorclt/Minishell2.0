/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:53:28 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 23:39:38 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	too_many_arg(void)
{
	ft_putstr_fd("mimishell: cd: too many arguments\n", 2);
	update_last_cmd_status(FAILURE);
}

static void	erno_error(char *arg)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("mimishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("mimishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	update_last_cmd_status(FAILURE);
}

static void	check_cd_error(char **arg)
{
	if (arg[1] && arg[2])
		too_many_arg();
	else if (chdir(arg[1]) == -1)
		erno_error(arg[1]);
}

static void	update_pwds(char *arg)
{
	char	cwd[PATH_MAX];

	chdir(arg);
	env_change_value("OLDPWD", env_get_value("PWD"));
	env_change_value("PWD", getcwd(cwd, PATH_MAX));
}

void	builtin_cd(char **arg)
{
	check_cd_error(arg);
	if (get_last_cmd_status() == FAILURE)
		return ;
	if (!arg[1])
		chdir((const char *)getenv("HOME"));
	else
		update_pwds(*arg);
	update_last_cmd_status(SUCCESS);
}
