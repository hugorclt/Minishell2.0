/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 17:20:40 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_tree *node)
{
	int	pid;
	
	if (node->token->id == CMD)
	{
		pid = fork();
		if (pid == -1)
			free_all(FREE);
		if (pid == 0)
		{
			printf("st : %s\n", node->token->cmd[0]);
			execve(join_cmdpath(node->token->cmd[0]), node->token->cmd, env_to_matrix());
		}
		else
			wait(NULL);
	}
}
