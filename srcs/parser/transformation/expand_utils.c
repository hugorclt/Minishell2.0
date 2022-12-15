/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:28:47 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/15 18:24:07 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_valid_dollar_index(char *cmd)
{
	int		index;
	t_data	*data;

	index = 0;
	data = _data();
	while (cmd[index])
	{
		if (cmd[index] == '\"' && data->doubleq == CLOSE
			&& data->singleq == CLOSE)
			data->doubleq = OPEN;
		else if (cmd[index] == '\"' && data->doubleq == OPEN
			&& data->singleq == CLOSE)
			data->doubleq = CLOSE;
		if (cmd[index] == '\'' && data->singleq == CLOSE
			&& data->doubleq == CLOSE)
			data->singleq = OPEN;
		else if (cmd[index] == '\'' && data->singleq == OPEN
			&& data->doubleq == CLOSE)
			data->singleq = CLOSE;
		if (cmd[index] == '$' && data->singleq == CLOSE)
			return (index);
		index++;
	}
	return (index);
}

char	*get_key(char *cmd)
{
	int		len_key;
	int		index;
	char	*key;

	len_key = 0;
	index = ft_strchr_index(cmd, '$') + 1;
	while (cmd[index] && cmd[index] != '$'
		&& cmd[index] != '\'' && cmd[index] != '"')
	{
		index++;
		len_key++;
	}
	index = ft_strchr_index(cmd, '$') + 1;
	key = ft_substr(cmd, index, len_key);
	return (key);
}

char	*get_before_dollar(char *cmd)
{
	char	*before;

	before = ft_substr(cmd, 0, get_valid_dollar_index(cmd));
	if (!before)
		return (NULL);
	return (before);
}

char	*get_dollar_value(char *cmd, char *key, char *before_dollar)
{
	if (cmd[ft_strlen(before_dollar)] == '\0')
		return (NULL);
	else
		return (env_get_value(key));
}
