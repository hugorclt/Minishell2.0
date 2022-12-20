/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 17:34:51 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	export_key_and_value(char *key, char *val)
{
	if (env_get_key(key))
	{
		env_change_value(key, val, 0);
		return (free(key), free(val));
	}	
	else
		env_add_node(key, val);
}

static void	check_export_args(char *arg)
{
	int		equal_index;
	char	*key;
	char	*val;

	equal_index = ft_strchr_index(arg, '=');
	key = init_key(arg, equal_index);
	val = init_value(arg, equal_index);
	if (ft_isalpha(key[0]) == FALSE && key[0] != '_')
	{
		export_invalid_identifier(key);
		return (free(key), free(val));
	}
	else
		export_key_and_value(key, val);
}

void	builtin_export(char **args)
{
	int		i;

	i = 1;
	update_last_cmd_status(SUCCESS);
	if (!args[1])
		export_invalid_identifier(args[i]);
	while (args[i])
	{
		check_export_args(args[i]);
		i++;
	}
}
