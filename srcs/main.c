/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:55:50 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/23 18:52:50 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_token(void)
{
	t_token	*token;
	char	*cmd;

	token	= malloc(sizeof(t_token));
	if (!token)
		free_all(QUIT);
	cmd = scan_token();
	token->id = find_token_id(cmd);
	token->cmd = split_quoted(cmd);
	//EXPAND to add here
	token->cmd = unquote(token->cmd);
	return (free(cmd), token);
}

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
			create_tree();
			print_tree();
		}

		free_all(FREE);
	}
}
