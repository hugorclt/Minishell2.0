/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:13:02 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 23:13:30 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(int flag)
{
	t_data	*data;

	data = _data();
	free(data->info_cmd.pid);
	ft_bzero(&data->info_cmd, sizeof(t_info_cmd));
	free_tree(data->tree);
	if (flag == QUIT)
	{
		free_env();
		exit(get_last_cmd_status());
	}
}
