/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/17 10:43:19 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_io(int in, int out)
{
	dup2(in, STDIN);
	dup2(out, STDOUT);
}

void	exec_fd(t_tree *node)
{
	open_file(node);
	close_pipe_fd(node);
	dup2_io(node->token->fd_in, node->token->fd_out);
}

void	exec_builtin(t_tree	*node, int flag)
{
	t_fptr		builtin;

	builtin = dispatch(node->token->cmd[0]);
	if (builtin)
	{
		(*builtin)(node->token->cmd);
		if (flag == FORK)
			free_all(QUIT);
	}
}

void	exec_one_builtin(t_tree *node)
{
	t_data	*data;

	data = _data();
	exec_fd(node);
	exec_builtin(node, MAIN);
	dup2_io(data->save_in, data->save_out);
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
			exec_fd(node);
			exec_builtin(node, FORK);
			env = env_to_matrix();
			if (execve(join_cmdpath(node->token->cmd[0]),
					node->token->cmd, env) == -1)
				exec_error(node->token->cmd[0], env);
		}
		info_cmd->index_cmd++;
	}
}
