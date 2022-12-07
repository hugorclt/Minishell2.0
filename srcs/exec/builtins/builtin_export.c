/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 18:24:02 by lbisson          ###   ########.fr       */
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
	char	*val;

	equal_index = ft_strchr_index(str, '=');
	if (env_get_key(str))
		env_change_value(str, env_get_value(str));
	else if (!equal_index)
	{
		key = ft_substr(str, 0, ft_strlen(str));
		val = NULL;
		env_add_node(key, val);
	}
	else
	{
		key = ft_substr(str, 0, equal_index);
		val = ft_substr(str, equal_index + 1, ft_strlen(str + equal_index + 1));
		env_add_node(key, val);
	}
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
