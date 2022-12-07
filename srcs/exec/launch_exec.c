/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 19:35:49 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(void)
{
	int			status;
	t_info_cmd	*info_cmd;

	info_cmd = _info_cmd();
	while (info_cmd->index_cmd_start < info_cmd->index_cmd)
	{
		waitpid(info_cmd->pid[info_cmd->index_cmd_start], &status, 0);
		update_last_cmd_status(WEXITSTATUS(status));
		info_cmd->index_cmd_start++;
	}
}

void	launch_exec(t_tree *node)
{
	if (!node)
		return ;
	launch_exec(node->left);
	if (node->token->id == AND && get_last_cmd_status() != 0)
	{
		wait_cmd();
		return ;
	}
	else if (node->token->id == OR && get_last_cmd_status() == 0)
	{
		wait_cmd();
		return ;
	}
	exec_choice(node);
	exec_choice(node->right);
}

void	link_fd(t_tree *node)
{
	if (!node)
		return ;
	if (node->token->id == PIPE)
	{
		pipe(node->token->pipe);
		if (node->left->token->id == PIPE)
			node->left->right->token->fd_out = node->token->pipe[1];
		else
			node->left->token->fd_out = node->token->pipe[1];
		node->right->token->fd_in = node->token->pipe[0];
	}
	link_fd(node->left);
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