/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/18 18:10:47 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipeline()
{
	
}

void	create_tree()
{
	t_tree	**tree;

	tree = _tree();
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *cmd;
	
	while (42)
	{
		cmd = readline("minishell$>");
		init_scanner(cmd);
		
		t_tree *node1 = create_node(scan_token(), create_node(scan_token(), NULL, NULL), create_node(scan_token(), NULL, NULL));
		t_tree	**tree = _tree();
		(*tree) = node1;
		print_tree();
		//create_tree();
	}
}
