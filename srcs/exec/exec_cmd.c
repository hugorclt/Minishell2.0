/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/20 17:07:51 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_io(int in, int out)
{
	dup2(in, STDIN);
	dup2(out, STDOUT);
}

int	exec_fd(t_tree *node)
{
	int	ret;

	ret = open_file(node);
	dup2_io(node->token->fd_in, node->token->fd_out);
	if (node->token->fd_in != 0)
		close(node->token->fd_in);
	if (node->token->fd_out != 1)
		close(node->token->fd_out);
	close_pipe_fd(node);
	return (ret);
}

void	exec_builtin(t_tree	*node, int flag)
{
	t_fptr		builtin;

	if (node->token->cmd[0])
	{
		builtin = dispatch(node->token->cmd[0]);
		if (builtin)
		{
			(*builtin)(node->token->cmd);
			if (flag == FORK)
				free_all(QUIT);
		}
	}
	else
		if (flag == FORK)
			free_all(QUIT);
}

void	exec_one_builtin(t_tree *node)
{
	t_data	*data;

	data = _data();
	if (exec_fd(node) == FAILURE)
	{
		dup2_io(data->save_in, data->save_out);
		return ;
	}
	else
	{	
		exec_builtin(node, MAIN);
		dup2_io(data->save_in, data->save_out);
		if (node->token->fd_in != 0)
			close(node->token->fd_in);
		if (node->token->fd_out != 1)
			close(node->token->fd_out);
	}
}

void	exec_cmd(t_tree *node)
{
	t_info_cmd	*info_cmd;
	char		**env;
	char		*cmd;

	info_cmd = _info_cmd();
	if (node->token->id == CMD)
	{
		info_cmd->pid[info_cmd->index_cmd] = fork();
		if (info_cmd->pid[info_cmd->index_cmd] == -1)
			free_all(FREE);
		if (info_cmd->pid[info_cmd->index_cmd] == 0)
		{
			sig_choice(SIG_EXEC_FORK);
			if (exec_fd(node) == FAILURE)
				free_all(QUIT);
			exec_builtin(node, FORK);
			env = env_to_matrix();
			cmd = join_cmdpath(node->token->cmd[0]);
			if (execve(cmd, node->token->cmd, env) == -1)
				exec_error(node->token->cmd[0], env, cmd);
		}
		info_cmd->index_cmd++;
	}
}
