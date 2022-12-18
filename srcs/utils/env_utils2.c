/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:55:27 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/18 14:49:22 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get_value(char	*key)
{
	t_list	*env;

	env = *_list();
	while (env && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (env && ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		return (ft_strdup(env->value));
	return (ft_strdup(""));
}

char	*env_get_key(char *key)
{
	t_list	*env;

	env = *_list();
	if (ft_strncmp(key, "", 1) == 0)
		return (NULL);
	while (env && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (env && ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		return (env->key);
	return (NULL);
}

char	**env_to_matrix(void)
{
	int		index;
	int		lstsize;
	char	**matrix;
	t_list	*env;

	index = 0;
	env = *_list();
	lstsize = ft_lstsize(env);
	matrix = ft_calloc(sizeof(char *), lstsize + 1);
	while (index < lstsize - 1)
	{
		matrix[index] = ft_strdup(env->key);
		matrix[index] = ft_strjoin_char(matrix[index], '=');
		matrix[index] = ft_strjoin_free(matrix[index], env->value);
		env = env->next;
		index++;
	}
	matrix[index] = NULL;
	return (matrix);
}
