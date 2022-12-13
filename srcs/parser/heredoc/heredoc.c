/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:03:15 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/13 16:06:39 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	start_heredoc(t_tree *node)
{
	if (!node)
		return ;
	start_heredoc(node->left);
	if (node->token->id == CMD)
	{
		create_file(node);
		write_heredoc(node);
	}
	start_heredoc(node->right);
}