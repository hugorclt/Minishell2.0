/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/18 17:29:15 by lbisson          ###   ########.fr       */
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
		env_change_value(key, val, 0);
		return (free(key), free(val));
	}	
	else
		env_add_node(key, val);
}

static void	check_export_args(char *arg)
{
	int		j;
	t_data	*data;

	j = 0;
	data = _data();
	get_valid_dollar_index(arg);
	if (ft_isalpha(arg[0]) == FALSE && arg[0] != '_')
		return (export_invalid_identifier(arg));
	while (arg[j])
	{
		if ((arg[j] == '_' || arg[j] == '=' || arg[j] == ' '
			|| ft_isalnum(arg[j]))
			|| (data->doubleq == CLOSE && data->singleq == CLOSE))
			j++;
		else
			return (export_invalid_identifier(arg));
	}
	if (arg[j] == '\0')
		export_key_and_value(arg);
}

void	builtin_export(char **args)
{
	int	i;

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
