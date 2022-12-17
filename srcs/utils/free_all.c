/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:13:02 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/15 17:29:40 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(int flag)
{
	t_data	*data;

	data = _data();
	free(data->info_cmd.pid);
	if (data->info_cmd.nb_cmd)
		free_tree(data->tree);
	ft_bzero(&data->info_cmd, sizeof(t_info_cmd));
	close(data->save_in);
	close(data->save_out);
	if (flag == QUIT)
	{
		free_env();
		exit(get_last_cmd_status());
	}
}

void	free_all_fork(int flag)
{
	t_data	*data;

	data = _data();
	free(data->info_cmd.pid);
	if (data->info_cmd.nb_cmd)
		free_tree(data->tree);
	ft_bzero(&data->info_cmd, sizeof(t_info_cmd));
	close(data->save_in);
	close(data->save_out);
	if (flag == QUIT)
	{
		free_env();
		exit(get_last_cmd_status());
	}
}
