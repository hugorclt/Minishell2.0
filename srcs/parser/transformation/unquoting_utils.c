/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:39:04 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/17 10:41:12 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unquote_line_init(char *cmd, int *j, int *len, char **ret)
{
	*j = 0;
	(*len) = len_wo_quote(cmd);
	if ((*len) == -1)
		return (-1);
	(*ret) = ft_calloc(sizeof(char), (*len) + 1);
	if (!(*ret))
		free_all(QUIT);
	return (1);
}
