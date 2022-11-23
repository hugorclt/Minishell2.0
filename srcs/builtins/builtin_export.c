/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/23 16:23:05 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_export_error(char **arg)
{
	if (!arg[1])
		update_last_cmd_status(FAILURE);
	if (ft_isalpha(arg[1][0]) == FALSE && arg[1][0] != '_')
	{
		dprintf(STDERR, "mimishell: export: '%c': not a valiid identifier \n",
						arg[1][0]);
		update_last_cmd_status(FAILURE);
	}
}

static void	export_key_and_value(char *str)
{
	int		equal_index;
	char	*key;
	char	*value;

	equal_index = ft_strchr(str, '=');
	key = ft_substring(str, 0, equal_index);
	value = ft_substring(str, equal_index, ft_strlen(str[equal_index]));
	env_add_node(key, value);
}

void	builtin_export(char **arg)
{
	int		i;
	t_data	*data;
	
	i = 1;
	data = _data();
	check_export_error(arg);
	if (data->last_cmd_status == FAILURE)
		return;
	while (arg[i])
	{
		export_key_and_value(arg[i]);
		i++;
	}
	update_last_cmd_status(SUCCESS);
}
