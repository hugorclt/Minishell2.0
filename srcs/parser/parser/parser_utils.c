/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 22:56:19 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 22:56:50 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parent(t_tree *node, t_tree *parent)
{
	if (!node)
		return ;
	init_parent(node->left, node);
	node->parent = parent;
	init_parent(node->right, node);
}

t_tree	*add_node(t_token *token, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	node->token = token;
	node->left = left;
	node->right = right;
	return (node);
}
