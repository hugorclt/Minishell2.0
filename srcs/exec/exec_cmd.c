/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 19:31:46 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_io(int in, int out)
{
	dup2(in, STDIN);
	dup2(out, STDOUT);
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
			if (execve(join_cmdpath(node->token->cmd[0]), node->token->cmd, env_to_matrix()) == -1)
			{
				info_cmd->index_cmd++;
				dprintf(2, "bash: %s: command not found\n", node->token->cmd[0]);
				free_all(QUIT);
			}
		}
		info_cmd->index_cmd++;
	}
}

