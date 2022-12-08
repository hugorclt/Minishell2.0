/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/08 17:14:26 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_io(int in, int out)
{
	dup2(in, STDIN);
	dup2(out, STDOUT);
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

void	exec_cmd(t_tree *node)
{
	t_info_cmd	*info_cmd;
	
	info_cmd = _info_cmd();
	if (node->token->id == CMD)
	{
		info_cmd->pid[info_cmd->index_cmd] = fork();
		if (info_cmd->pid[info_cmd->index_cmd] == -1)
			free_all(FREE);
		if (info_cmd->pid[info_cmd->index_cmd] == 0)
		{
			dup2_io(node->token->fd_in, node->token->fd_out);
			close_pipe_fd(node);
			if (execve(join_cmdpath(node->token->cmd[0]), node->token->cmd, env_to_matrix()) == -1)
			{
				info_cmd->index_cmd++;
				dprintf(2, "bash: %s: command not found\n", node->token->cmd[0]);
				update_last_cmd_status(1);
				free_all(QUIT);
			}
		}
		info_cmd->index_cmd++;
	}
}

