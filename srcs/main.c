/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 15:32:22 by hrecolet         ###   ########.fr       */
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
			execve(join_cmdpath(node->token->cmd[0]), node->token->cmd, env_to_matrix());
		}
		else
			wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*cmd;
	t_data	*data;
	
	using_history();
	env_init_list(env);
	data = _data();
	while (42)
	{
		data->nb_heredoc = -1;
		sig_choice(SIG_PARSE);
		cmd = readline(PINK "mimishell $>" RESET);
		if (!cmd)
			free_all(QUIT);
		add_history(cmd);
		if (check_cmd(cmd) == SUCCESS)
		{
			init_scanner(cmd);
			if (create_tree() == SUCCESS)
			{
				sig_choice(SIG_EXEC);
				print_tree();
				exec_cmd(*_tree());
			}
		}
		free_all(FREE);
	}
}
