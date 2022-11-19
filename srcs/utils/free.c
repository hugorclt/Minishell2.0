/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/19 10:51:33 by hrecolet         ###   ########.fr       */
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
