/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/18 19:25:45 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipeline()
{
	
}

void	create_tree()
{
	t_tree	**root;
	t_tree	*tree;

	root = _tree();
	tree = (*root);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *cmd;
	
	while (42)
	{
		cmd = readline(PINK "mimishell $>" RESET);
		init_scanner(cmd);
		//printf("%s, %s, %s\n", scan_token()->cmd, scan_token()->cmd, scan_token()->cmd);
		t_tree	**tree;

		tree = _tree();
		(*tree) = create_node(scan_token(), create_node(scan_token(), NULL, NULL ), create_node(scan_token(), NULL, NULL));
		//create_tree();
		print_tree();
	}
}
