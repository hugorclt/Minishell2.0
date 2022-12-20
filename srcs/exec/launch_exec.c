/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 12:13:02 by hrecolet         ###   ########.fr       */
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
		if (WIFSIGNALED(status))
		{
			if (WCOREDUMP(status))
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else
				status += 128;
		}
		else
			status = WEXITSTATUS(status);
		update_last_cmd_status(status);
		info_cmd->index_cmd_start++;
	}
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
		if (node->right->token->id == CMD && node->parent
			&& node->parent->token->id == PIPE)
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
