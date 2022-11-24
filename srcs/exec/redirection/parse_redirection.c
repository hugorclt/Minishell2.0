/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:15:41 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/24 12:18:36 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_infile(char **cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "<<", 2))
		{
			i+= 1;
			len++;
		}
		else if (!ft_strncmp(cmd[i], "<", 1))
			len++;
		i++;
	}
	return (len);
}

int	count_outfile(char **cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">>", 2))
		{
			i+= 1;
			len++;
		}
		else if (!ft_strncmp(cmd[i], ">", 1))
			len++;
		i++;
	}
	return (len);
}