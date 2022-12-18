/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:33:12 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/18 17:38:58 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	export_is_valid_char(char *arg, int index)
{
	t_data	*data;

	data = _data();
	get_valid_dollar_index(arg);
	if ((arg[index] == '_' || arg[index] == '=' || arg[index] == ' '
			|| ft_isalnum(arg[index]))
		|| (data->doubleq == CLOSE && data->singleq == CLOSE))
		return (TRUE);
	return (FALSE);
}
