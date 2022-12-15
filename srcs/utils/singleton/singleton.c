/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:27:20 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 16:49:02 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*_data(void)
{
	static t_data	data;
	static int		init = 0;

	if (init == 0)
	{
		ft_bzero(&data, sizeof(t_data));
		init++;
	}
	return (&data);
}

t_list	**_list(void)
{
	t_data	*data;

	data = _data();
	return (&data->env);
}

t_scanner	*_scanner(void)
{
	t_data	*data;

	data = _data();
	return (&data->scanner);
}

t_tree	**_tree(void)
{
	t_data	*data;

	data = _data();
	return (&data->tree);
}

t_info_cmd	*_info_cmd(void)
{
	t_data	*data;

	data = _data();
	return (&data->info_cmd);
}
