/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 22:02:48 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_export_error(char **arg)
{
	if (!arg[1])
		update_last_cmd_status(FAILURE);
	else if (ft_isalpha(arg[1][0]) == FALSE && arg[1][0] != '_')
	{
		dprintf(STDERR, "mimishell: export: '%c': not a valiid identifier \n",
			arg[1][0]);
		update_last_cmd_status(FAILURE);
	}
}

static char	*init_key(char *str, int equal_index)
{
	char	*key;

	if (!equal_index)
		key = ft_strdup(str);
	else
		key = ft_substr(str, 0, equal_index);
	return (key);
}

static char	*init_value(char *str, int equal_index)
{
	char	*value;

	if (!equal_index)
		value = NULL;
	else
		value = ft_substr(str, equal_index + 1, -1);
	return (value);
}

static void	export_key_and_value(char *str)
{
	int		equal_index;
	char	*key;
	char	*val;

	equal_index = ft_strchr_index(str, '=');
	key = init_key(str, equal_index);
	val = init_value(str, equal_index);
	if (env_get_key(key))
	{
		env_change_value(key, val);
		return (free(key), free(val));
	}	
	else
		env_add_node(key, val);
}

void	builtin_export(char **arg)
{
	int		i;

	i = 1;
	check_export_error(arg);
	if (get_last_cmd_status() == FAILURE)
		return ;
	while (arg[i])
	{
		export_key_and_value(arg[i]);
		i++;
	}
	update_last_cmd_status(SUCCESS);
}
