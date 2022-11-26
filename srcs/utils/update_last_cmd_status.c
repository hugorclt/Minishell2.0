/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_cmd_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:18:59 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/26 19:28:33 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last_cmd_status(int status)
{
	t_data	*data;

	data = _data();
	data->last_cmd_status = (u_char)status;
}

void	error_opening(char *str)
{
	update_last_cmd_status(1);
	if (errno == 13)
	{
		ft_putstr_fd(PINK "mimishell: " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(PINK "mimishell: cannot access " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	free_all(FREE);
}