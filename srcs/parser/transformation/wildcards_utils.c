/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:22:50 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 21:24:03 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_wildcard(char *str)
{
	if (ft_strchr(str, '*') && !ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (TRUE);
	return (FALSE);
}

bool	is_valid_filename(char *request, char *filename, int i, int j)
{
	if (filename[0] == '.')
		return (FALSE);
	while (request[i])
	{
		while (request[i] == '*')
		{
			if (request[i + 1] == '\0')
				return (TRUE);
			while (filename[j] && filename[j] !=request[i + 1])
				j++;
			if (filename[j] == '\0')
				return (FALSE);
			i++;
		}
		if (request[i] != filename[j])
			return (FALSE);
		else if (request[i] == filename[j])
		{
			i++;
			j++;
		}
	}
	if (request[i] == '\0' && filename[j] == '\0')
		return (TRUE);
	return (FALSE);
}

int nb_valid_filename(char *str)
{
	int			nb;
	DIR			*directory;
	t_dirent	*current;

	nb = 0;
	directory = opendir(".");
	if (!directory)
		return (0);
	current = readdir(directory);
	while (current)
	{
		if (*(current->d_name) != '.')
			nb += is_valid_filename(str, current->d_name, 0, 0);
		current = readdir(directory);
	}
	closedir(directory);
	return (nb);
}

int	get_new_matrix_len(char **old_matrix)
{
	int	i;
	int	new_len;

	i = 0;
	new_len = 0;
	while (old_matrix[i])
	{
		if (is_valid_wildcard(old_matrix[i]) == TRUE)
			new_len += nb_valid_filename(old_matrix[i]);
		i++;
	}
	new_len += tab_len(old_matrix);
	return (new_len);
}
