/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:33:26 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/18 14:11:46 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit_non_num_arg(arg[1]);
	else if (arg[2])
		exit_too_many_args();
	else
		update_last_cmd_status(status);
}

void	builtin_exit(char **arg)
{
	printf("exit\n");
	check_error_exit(arg);
	if (get_last_cmd_status() == EXIT_TOO_MANY_ARGS)
		return ;
	free_all(QUIT);
}
