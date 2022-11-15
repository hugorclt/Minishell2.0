/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:27:20 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/15 17:50:05 by hrecolet         ###   ########.fr       */
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
	t_list	**lst;

	lst = &(_data()->grammar_list);
	return (lst);
}
