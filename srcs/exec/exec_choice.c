/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_choice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:14:18 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 13:37:41 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fptr	dispatch(char *str)
{
	int			index;
	t_choice	funchoice[7];

	index = -1;
	funchoice[0].callback = builtin_cd;
	funchoice[0].fun_name = "cd";
	funchoice[1].callback = builtin_echo;
	funchoice[1].fun_name = "echo";
	funchoice[2].callback = builtin_env;
	funchoice[2].fun_name = "env";
	funchoice[3].callback = builtin_exit;
	funchoice[3].fun_name = "exit";
	funchoice[4].callback = builtin_export;
	funchoice[4].fun_name = "export";
	funchoice[5].callback = builtin_pwd;
	funchoice[5].fun_name = "pwd";
	funchoice[6].callback = builtin_unset;
	funchoice[6].fun_name = "unset";
	while (++index < 7)
	{
		if (ft_strncmp(funchoice[index].fun_name, str,
				ft_strlen(funchoice[index].fun_name)) == 0)
			return (funchoice[index].callback);
	}
	return (NULL);
}

void	exec_choice(t_tree *node)
{
	t_fptr		builtin;
	t_info_cmd	*info_cmd;

	info_cmd = _info_cmd();
	if (!node)
		return ;
	if (node->token->cmd[0])
	{
		builtin = dispatch(node->token->cmd[0]);
		if (builtin && info_cmd->nb_cmd == 1)
			exec_one_builtin(node);
		else
			exec_cmd(node);
	}
	else
		exec_cmd(node);
}
