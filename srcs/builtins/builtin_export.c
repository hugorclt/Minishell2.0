/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:54:08 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/21 22:15:12 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_export_error(char **arg)
{
	if (!arg[1])
		return ;
	if (ft_isdigit(arg[1][0]) == TRUE)
	{
		dprintf(STDERR, "export: not an identifier: %c\n", arg[1][0]);
		update_last_cmd_status(FAILURE);
	}
}

void	builtin_export(char **arg)
{
	int		i;
	int		j;
	char	**export_var;
	t_data	*data;
	
	i = 0;
	data = _data();
	if (!arg[1])
		return ;
	check_export_error(arg);
	if (data->last_cmd_status == EXIT_TOO_MANY_ARGS)
		return;
	while (arg[i])
	{
		j = 0;
		export_var = ft_split(arg[i], '=');
		if (!export_var || !export_var[0])
			free_all(QUIT);
		while (export_var[j])
		{
			
		}
		i++;
	}
}
