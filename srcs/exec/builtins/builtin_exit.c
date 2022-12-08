/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:33:26 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 23:30:05 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_non_num_arg(char *arg)
{
	dprintf(STDERR, "mimishell: exit: %s: numeric argument required\n", arg);
	update_last_cmd_status(EXIT_NUM_ARG_REQUIRED);
}

static void	error_too_many_args(void)
{
	dprintf(STDERR, "mimishell: exit: too many arguments\n");
	update_last_cmd_status(EXIT_TOO_MANY_ARGS);
}

static int	is_num_arg(char *str)
{
	if (*str && (*str == '-' || *str == '+'))
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{	
		if (ft_isdigit(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	check_error_exit(char **arg)
{
	int	status;
	
	if (!arg[1])
		return ;
	status = ft_atoi(arg[1]);
	if (arg[1] && is_num_arg(arg[1]) == FALSE)
		error_non_num_arg(arg[1]);
	else if (arg[2])
		error_too_many_args();
	else
		update_last_cmd_status(status);
		
}

void	builtin_exit(char **arg)
{
	t_data	*data;
	
	data = _data();
	printf("exit\n");
	check_error_exit(arg);
	if (data->info_cmd.last_cmd_status == EXIT_TOO_MANY_ARGS)
		return;
	free_all(QUIT);
}
