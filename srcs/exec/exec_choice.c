/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_choice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:14:18 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/07 16:43:53 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_choice	*init_tchoice(void)
{
	t_choice	funchoice[7];

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
	return (funchoice);
}

static t_fptr	dispatch(char *str)
{
	int			index;
	t_choice	*funchoice = init_tchoice();

	index = 0;
	while (index < 7)
	{
		if (ft_strncmp(funchoice[index].fun_name, str, ft_strlen(str)) == 0)
			return (funchoice[index].callback);
		index++;
	}
	return (NULL);
}

void	exec_choice(char **cmd)
{
	t_fptr	builtin;
	
	builtin = dispatch(cmd[0]);
	if (builtin)
		(*builtin)(cmd);
}
