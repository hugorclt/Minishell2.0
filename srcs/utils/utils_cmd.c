/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:45:24 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 17:31:34 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_nb_cmd(t_tree *tree)
{
	t_data	*data;

	data = _data();
	if (!tree)
		return ;
	init_nb_cmd(tree->left);
	if (tree->token->id == CMD)
		data->info_cmd.nb_cmd++;
	init_nb_cmd(tree->right);
}
