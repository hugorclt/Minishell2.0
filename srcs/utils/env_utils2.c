/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:55:27 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 16:18:41 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_matrix(void)
{
	int		index;
	char	**matrix;
	t_list	*env;

	index = 0;
	env = *_list();
	matrix = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	while (env)
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
