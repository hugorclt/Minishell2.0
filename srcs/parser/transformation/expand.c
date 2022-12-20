/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:05:55 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 08:57:06 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var(char *cmd)
{
	int		index_dollar;
	char	*key;
	char	*expvalue;
	char	*dollar_value;
	char	*before_dollar;

	expvalue = NULL;
	index_dollar = get_valid_dollar_index(cmd);
	while (index_dollar >= 0)
	{
		before_dollar = get_before_dollar(cmd, index_dollar);
		key = get_key(cmd, index_dollar);
		dollar_value = get_dollar_value(cmd, key, &index_dollar);
		expvalue = ft_expjoin_free(expvalue, before_dollar, BOTH, NO);
		expvalue = ft_expjoin_free(expvalue, dollar_value, BOTH, NO);
		cmd += index_dollar + ft_strlen(key) + ft_strlen("$");
		index_dollar = get_valid_dollar_index(cmd);
		free(key);
	}
	if (*cmd)
		expvalue = ft_expjoin_free(expvalue, cmd, S1, YES);
	return (expvalue);
}

char	**expand(char **cmd)
{
	int		i;
	char	**expcmd;
	t_data	*data;

	i = 0;
	data = _data();
	data->singleq = CLOSE;
	data->doubleq = CLOSE;
	expcmd = ft_calloc(sizeof(char *), tab_len(cmd) + 1);
	while (cmd[i])
	{
		expcmd[i] = expand_env_var(cmd[i]);
		i++;
	}
	expcmd[i] = NULL;
	free_matrix(cmd);
	return (expcmd);
}
