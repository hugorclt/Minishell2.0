/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 18:27:46 by hrecolet         ###   ########.fr       */
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
	free(data->info_cmd.pid);
	data->info_cmd.pid = NULL;
	data->info_cmd.nb_cmd = 0;
	//free_tree(&(data->tree));
	if (flag == QUIT)
	{
		//free env
		exit(get_last_cmd_status());
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

void	free_token(t_token *token)
{
	free_matrix(token->cmd);
	free(token);
}
