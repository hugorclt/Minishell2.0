/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 17:00:10 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_exec(t_tree *node)
{
	if (!node)
		return ;
	launch_exec(node->left);
	exec_choice(node);
	exec_choice(node->right);
}
