/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 22:44:32 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(void)
{
	t_list *env;

	env = *_list();
	
}

static void	check_export_error(char **arg)
{
	if (!arg[1])
		print_export();
	else if (ft_isalpha(arg[1][0]) == FALSE && arg[1][0] != '_')
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
	if (!equal_index)
	{
		key = ft_strdup(str);
		val = NULL;
	}
	else
	{
		key = ft_substr(str, 0, equal_index);
		val = ft_substr(str, equal_index + 1, -1);
	}
	if (env_get_key(key))
		env_change_value(key, val);
	else
		env_add_node(key, val);
}

void	builtin_export(char **arg)
{
	int		i;
	t_data	*data;
	
	i = 1;
	data = _data();
	check_export_error(arg);
	if (data->info_cmd.last_cmd_status == FAILURE)
		return;
	while (arg[i])
	{
		export_key_and_value(arg[i]);
		i++;
	}
	update_last_cmd_status(SUCCESS);
}
