/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:28:47 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 09:29:12 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_quote_status(int status)
{
	if (status == OPEN)
		status = CLOSE;
	else
		status = OPEN;
	return (status);
}

int	get_valid_dollar_index(char *cmd)
{
	int		index;
	t_data	*data;

	index = 0;
	data = _data();
	while (cmd[index])
	{
		if (cmd[index] == '\'' && data->doubleq == CLOSE)
			data->singleq = change_quote_status(data->singleq);
		if (cmd[index] == '\"' && data->singleq == CLOSE)
			data->doubleq = change_quote_status(data->doubleq);
		if (cmd[index] == '$' && data->singleq == CLOSE)
			return (index);
		index++;
	}
	return (-1);
}

char	*get_key(char *cmd, int index_dollar)
{
	int		len_key;
	int		index;
	char	*key;

	len_key = 0;
	index = index_dollar + 1;
	while (cmd[index] && ft_isalnum(cmd[index]))
	{
		index++;
		len_key++;
	}
	index = index_dollar + 1;
	key = ft_substr(cmd, index, len_key);
	return (key);
}

char	*get_before_dollar(char *cmd, int index_dollar)
{
	char	*before;

	before = ft_substr(cmd, 0, index_dollar);
	if (!before)
		return (NULL);
	return (before);
}

char	*get_dollar_value(char *cmd, char *key, int *index_dollar)
{
	int	after_dollar;

	after_dollar = *index_dollar + 1;
	if (cmd[after_dollar] == '?')
	{
		(*index_dollar)++;
		return (ft_itoa(get_last_cmd_status()));
	}
	else if (!key)
		return (ft_strdup("$"));
	else
		return (env_get_value(key));
}
