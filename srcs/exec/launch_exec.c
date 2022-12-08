/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/08 11:23:10 by hrecolet         ###   ########.fr       */
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

void	pipe_node(t_tree *node)
{
	if (!node)
		return ;
	pipe_node(node->left);
	if (node->token->id == PIPE)
		pipe(node->token->pipe);
	pipe_node(node->right);
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