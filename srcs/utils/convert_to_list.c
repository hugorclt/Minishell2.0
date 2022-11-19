/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:34:57 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/19 11:44:08 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_equal(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	convert_to_list(char **env)
{
	int	i;
	t_list	**lst;

	i = 0;
	lst = _list();
	while (env[i])
	{
		ft_lstadd_back(lst, 
			ft_lstnew(
				ft_substring(env[i], 0, find_equal(env[i])),
				ft_substring(env[i], find_equal(env[i]) + 1, ft_strlen(env[i]))));
		i++;
	}
}