/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:16:05 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/12 22:10:46 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_used(t_tree *node)
{
	if (!node)
		return ;
	close_pipe_used(node->left);
	if (node->token->id == PIPE)
	{
		close(node->token->pipe[0]);
		close(node->token->pipe[1]);
	}
	close_pipe_used(node->right);
}

void	pipe_node(t_tree *node)
{
	if (!node)
		return ;
	pipe_node(node->left);
	if (node->token->id == PIPE)
		pipe(node->token->pipe);
	pipe_node(node->right);
}

void	close_pipe_fd(t_tree *node)
{
	if (node->parent && node->parent->token->id == PIPE)
	{
		if (node->parent->token->pipe[1] != node->token->fd_out)
			close(node->parent->token->pipe[1]);
		if (node->parent->token->pipe[0] != node->token->fd_in)
			close(node->parent->token->pipe[0]);
	}
	close_pipe_used(*_tree());
}
