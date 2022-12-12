/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:58:52 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/12 21:28:24 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**expand_wildcard(char *str)
{
	int			i;
	char		**result;
	DIR			*directory;
	t_dirent	*current;

	i = 0;
	result = ft_calloc(sizeof(char *), nb_valid_filename(str) + 1);
	if (!result)
		free_all(QUIT);
	directory = opendir(".");
	current = readdir(directory);
	while (current)
	{
		if (is_valid_filename(str, current->d_name, 0, 0) == TRUE)
		{
			result[i] = ft_strdup(current->d_name);
			if (!result[i])
			{
				free_matrix(result);
				free_all(QUIT);
			}
			i++;
		}
		current = readdir(directory);
	}
	closedir(directory);
	result[i] = NULL;
	return (result);
	
}

static void	insert_matrix(char **to_insert, char **dest, int *j)
{
	int	i;

	i = 0;
	while (to_insert[i])
	{
		dest[*j] = ft_strdup(to_insert[i]);
		if (!dest[*j])
		{
			free_matrix(dest);
			free_matrix(to_insert);
			free_all(QUIT);
		}
		(*j)++;
		i++;
	}
	free_matrix(to_insert);
}

char	**wildcards(char **old_matrix)
{
	int		i;
	int		j;
	int		new_len;
	char	**new_matrix;

	i = 0;
	j = 0;
	new_len = get_new_matrix_len(old_matrix);
	new_matrix = ft_calloc(sizeof(char *), new_len + 1);
	if (!new_matrix)
		free_all(QUIT);
	while (old_matrix[i])
	{
		if (is_valid_wildcard(old_matrix[i])
			&& nb_valid_filename(old_matrix[i]) > 0)
			insert_matrix(expand_wildcard(old_matrix[i]), new_matrix, &j);
		else
		{
			new_matrix[j] = ft_strdup(old_matrix[i]);
			if (!new_matrix[j])
			{
				free_matrix(new_matrix);
				free_all(QUIT);
			}
			j++;
		}
		i++;
	}
	free_matrix(old_matrix);
	return (new_matrix);
}
