/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:55:27 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 17:36:33 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
