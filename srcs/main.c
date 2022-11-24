/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/24 11:33:12 by hrecolet         ###   ########.fr       */
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
	while (42)
	{
		//init
		cmd = readline(PINK "mimishell $>" RESET);
		if (!cmd)
			free_all(QUIT);
		if (check_cmd(cmd) == SUCCESS)
		{
			init_scanner(cmd);
			add_history(cmd);
			//if (create_tree() == SUCCESS)
			//{

			//	print_tree();
			//}
		}
		free_all(FREE);
	}
}
