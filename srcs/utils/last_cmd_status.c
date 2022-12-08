/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:09:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/08 16:42:45 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_cmd_status(void)
{
	t_data	*data;

	data = _data();
	return (data->last_cmd_status);
}

void	update_last_cmd_status(int status)
{
	t_data	*data;

	data = _data();
	data->last_cmd_status = (u_char)status;
}
