/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 07:26:39 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pid(void)
{
	t_info_cmd	*info_cmd;
	t_tree		*tree;

	tree = *_tree();
	info_cmd = _info_cmd();
	init_nb_cmd(tree);
	info_cmd->pid = malloc(sizeof(int) * info_cmd->nb_cmd);
	if (!info_cmd->pid)
		free_all(QUIT);
}

void	shell_process(char *cmd)
{
	init_scanner(cmd);
	if (create_tree() == SUCCESS)
	{
		init_pid();
		sig_choice(SIG_EXEC);
		pipe_node(*_tree());
		link_fd(*_tree());
		launch_exec(*_tree());
		wait_cmd(*_tree());
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*cmd;
	t_data	*data;
	t_tree	*tree;
	
	using_history();
	env_init_list(env);
	data = _data();
	tree = *_tree();
	while (42)
	{
		data->nb_heredoc = 0;
		sig_choice(SIG_PARSE);
		cmd = readline(PINK "mimishell ⚡>" RESET);
		if (!cmd)
			free_all(QUIT);
		add_history(cmd);
		if (check_cmd(cmd) == SUCCESS)
			shell_process(cmd);
		free_all(FREE);
	}
}
