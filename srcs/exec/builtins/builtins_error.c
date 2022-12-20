/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:54:01 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 08:21:45 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_too_many_arg(void)
{
	ft_putstr_fd("mimishell: cd: too many arguments\n", 2);
	update_last_cmd_status(FAILURE);
}

void	cd_erno_error(char *arg)
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

void	exit_non_num_arg(char *arg)
{
	ft_putstr_fd("mimishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	update_last_cmd_status(EXIT_NUM_ARG_REQUIRED);
}

void	exit_too_many_args(void)
{
	ft_putstr_fd("mimishell: exit: too many arguments\n", 2);
	update_last_cmd_status(EXIT_TOO_MANY_ARGS);
}

void	export_invalid_identifier(char *arg)
{
	if (!arg)
		ft_putstr_fd("mimishell: export: at least one argument required\n", 2);
	else
	{
		ft_putstr_fd("mimishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	update_last_cmd_status(FAILURE);
}
