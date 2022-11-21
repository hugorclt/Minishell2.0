/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:47:25 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/21 14:08:16 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_node(t_token *token, t_tree *l_child, t_tree *r_child)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	node->token = token;
	node->left = l_child;
	node->right = r_child;
	return (node);
}
