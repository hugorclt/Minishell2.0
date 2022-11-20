/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/20 00:02:04 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *cmd;
	
	using_history();
	env_init_list(env);
	// print_lst();
	while (42)
	{
		cmd = readline(PINK "mimishell $>" RESET);
		add_history(cmd);
		init_scanner(cmd);
		print_all_token();
		free(cmd);
		free_all(FREE);
		//create_tree();
		//print_tree();
	}
}
