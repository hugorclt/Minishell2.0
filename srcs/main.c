/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 17:17:47 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				launch_exec(*_tree());
			}
		}
		free_all(FREE);
	}
}
