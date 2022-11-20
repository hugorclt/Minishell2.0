/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/20 00:55:13 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	free_tree(t_tree **root)
// {
// 	if (!root)
// 		return ;
// 	free((*root)->token->cmd);
// 	free((*root)->token);
// 	free_tree(&((*root)->right));
// 	free_tree(&((*root)->left));
// 	free((*root));
// }

void	free_all(int flag)
{
	t_data	*data;
	
	data = _data();
	//free_tree(&(data->tree));
	if (flag == QUIT)
	{
		//free env
		exit(0);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
