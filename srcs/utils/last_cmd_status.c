/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:09:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/10 19:56:53 by lbisson          ###   ########.fr       */
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
	data->last_cmd_status = (size_t)status;
}
