/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 00:05:09 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/20 18:29:14 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(char **arg)
{
	if (!arg[1])
	{
		dprintf(STDERR, "unset: not enough arguments\n");
		update_last_cmd_status(FAILURE);
		return ;
	}
	
}
