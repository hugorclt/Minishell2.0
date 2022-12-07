/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmdpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:27:55 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 15:31:33 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char *path)
{
	int		i;
	char	**splited_path;
	char	*file_to_test;

	i = 0;
	splited_path = ft_split(path, ':');
	while (splited_path[i])
	{
		splited_path[i] = ft_strjoin_char(splited_path[i], '/');
		file_to_test = ft_strjoin(splited_path[i], cmd);
		if (access(file_to_test, 0) == 0)
			return (free_matrix(splited_path), file_to_test);
		free(file_to_test);
		i++;
	}
	free_matrix(splited_path);
	return (NULL);
}

char	*join_cmdpath(char *cmd)
{
	char	*path_value;
	char	*ret;

	path_value = env_get_value("PATH");
	if (!path_value)
		return (cmd);
	ret = find_path(cmd, path_value);
	free(path_value);
	if (!ret)
		return (cmd);
	return (ret);
}