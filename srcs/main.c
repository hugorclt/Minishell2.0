/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 17:06:48 by hrecolet         ###   ########.fr       */
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
		start_heredoc();
		sig_choice(SIG_EXEC);
		pipe_node(*_tree());
		link_fd(*_tree());
		launch_exec(*_tree());
		wait_cmd(*_tree());
		unlink_heredoc(*(_tree()));
	}
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_data	*data;

	(void)ac;
	(void)av;
	using_history();
	env_init_list(env);
	data = _data();
	while (42)
	{
		*(_tree()) = NULL;
		data->nb_heredoc = 0;
		data->save_in = dup(STDIN);
		data->save_out = dup(STDOUT);
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
