/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:27:20 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/17 13:49:51 by hrecolet         ###   ########.fr       */
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
	return (&data->grammar_lst);
}

t_scanner	*_scanner(void)
{
	t_data	*data;

	data = _data();
	return (&data->scanner);
}