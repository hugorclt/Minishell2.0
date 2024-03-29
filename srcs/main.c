/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/20 13:39:31 by hrecolet         ###   ########.fr       */
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

void	calc_nb_heredoc(t_tree *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	calc_nb_heredoc(node->left);
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile[i].type == HEREDOC)
			_data()->nb_hd += 1;
		i++;
	}
	calc_nb_heredoc(node->right);
}

void	shell_process(char *cmd)
{
	init_scanner(cmd);
	if (create_tree() == SUCCESS)
	{
		init_pid();
		calc_nb_heredoc((*_tree()));
		if (_data()->nb_hd > 0)
			start_heredoc();
		sig_choice(SIG_EXEC);
		pipe_node(*_tree());
		link_fd(*_tree());
		launch_exec(*_tree());
		wait_cmd(*_tree());
		unlink_heredoc(*(_tree()));
	}
}

static void	init_shell(void)
{
	t_data	*data;

	data = _data();
	sig_choice(SIG_PARSE);
	*(_tree()) = NULL;
	data->nb_heredoc = 0;
	data->save_in = dup(STDIN);
	data->save_out = dup(STDOUT);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;

	(void)ac;
	(void)av;
	using_history();
	env_init_list(env);
	while (42)
	{
		init_shell();
		cmd = readline(PINK "mimishell ⚡>" RESET);
		if (!cmd)
		{
			ft_putstr_fd("\n", STDOUT);
			free_all(QUIT);
		}
		add_history(cmd);
		if (check_cmd(cmd) == SUCCESS)
			shell_process(cmd);
		free_all(FREE);
	}
}
