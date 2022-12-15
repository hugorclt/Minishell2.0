/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 07:27:18 by hrecolet         ###   ########.fr       */
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
	char		**env;
	
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
			env = env_to_matrix();
			if (execve(join_cmdpath(node->token->cmd[0]), node->token->cmd, env) 
				== -1)
			{
				free_matrix(env);
				info_cmd->index_cmd++;
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(node->token->cmd[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				update_last_cmd_status(1);
				free_all(QUIT);
			}
		}
		info_cmd->index_cmd++;
	}
}
