/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 00:05:09 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/05 16:19:34 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		env_unset_key(arg[i]);
		i++;
	}
	update_last_cmd_status(SUCCESS);	
}
