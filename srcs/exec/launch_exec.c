/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/08 16:57:34 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(t_tree *node)
{
	int			status;
	t_info_cmd	*info_cmd;

	info_cmd = _info_cmd();
	if (node->parent)
		close_pipe_used(node->left);
	else
		close_pipe_used(node);
	while (info_cmd->index_cmd_start < info_cmd->index_cmd)
	{
		waitpid(info_cmd->pid[info_cmd->index_cmd_start], &status, 0);
		update_last_cmd_status(WEXITSTATUS(status));
		info_cmd->index_cmd_start++;
	}
}

void	close_pipe_used(t_tree *node)
{
	if (!node)
		return ;
	close_pipe_used(node->left);
	if (node->token->id == PIPE)
	{
		printf("%d\t%d\n", node->token->pipe[1], node->token->pipe[0]);
		close(node->token->pipe[0]);
		close(node->token->pipe[1]);
	}
	close_pipe_used(node->right);
}

void	launch_exec(t_tree *node)
{
	if (!node)
		return ;
	launch_exec(node->left);
	if (node->token->id == AND)
	{
		wait_cmd(node);
		if (get_last_cmd_status() != 0)
			return ;
	}
	else if (node->token->id == OR)
	{
		wait_cmd(node);
		if (get_last_cmd_status() == 0)
			return ;
	}
	exec_choice(node);
	launch_exec(node->right);
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

void	link_fd(t_tree *node)
{
	if (!node)
		return ;
	link_fd(node->left);
	if (node->token->id == PIPE)
	{
		if (node->left->token->id == CMD)
		{
			node->left->token->fd_in = STDIN;
			node->left->token->fd_out = node->token->pipe[1];
		}
		if (node->right->token->id == CMD && node->parent && node->parent->token->id == PIPE)
		{
			node->right->token->fd_in = node->token->pipe[0];
			node->right->token->fd_out = node->parent->token->pipe[1];
		}
		else if (node->right->token->id == CMD)
		{
			node->right->token->fd_in = node->token->pipe[0];
			node->right->token->fd_out = STDOUT;
		}
	}
}


// si node == PIPE

// si nb_cmd == 1 && node->token->id == CMD
// 	return ;

// si index_cmd == 0
// alors node->left->fd_out = node->pid[0]

// si index_cmd != 0 || index_cmd != nb_cmd
// alors node->left->fd_in = node->pid[1]
// alors node->left->fd_out = node->pid[0]

// si index_cmd == nb_cmd
// alors node->left->fd_in = node->pid[1]