/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:05:55 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 21:32:58 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_env_var(char *cmd)
{
	char	*key;
	char	*expvalue;
	char	*dollar_value;
	char	*before_dollar;
	
	expvalue = NULL;
	while (ft_strchr(cmd, '$'))
	{
		before_dollar = get_before_dollar(cmd);
		key = get_key(cmd);
		dollar_value = get_dollar_value(cmd, key, before_dollar);
		expvalue = ft_expjoin_free(expvalue, before_dollar, BOTH);
		expvalue = ft_expjoin_free(expvalue, dollar_value, BOTH);
		cmd = ft_strchr(cmd, '$') + ft_strlen(key) + 1;
		free(key);
	}
	if (*cmd && (cmd[1] != '\0' || *cmd != '\''))
		expvalue = ft_expjoin_free(expvalue, cmd, S1);
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
