/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:16:58 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/20 13:40:10 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_error_and_close_fd(char *file, int fd, int index, int nb_file)
{
	if (fd == -1)
	{
		error_opening(file);
		return (FAILURE);
	}
	else if (index != nb_file - 1)
		close(fd);
	return (SUCCESS);
}

static int	open_file_in(t_tree *node)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_in)
	{
		fd = open(node->token->infile[i].file, O_RDONLY);
		if (check_error_and_close_fd(node->token->infile->file, fd, i,
				node->token->nb_file_in) == FAILURE)
			return (FAILURE);
		i++;
	}
	node->token->fd_in = fd;
	return (SUCCESS);
}

static int	open_file_out_utils(t_tree *node, int fd, int i)
{
	fd = open(node->token->outfile[i].file,
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (check_error_and_close_fd(node->token->outfile->file, fd, i,
			node->token->nb_file_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	open_file_out(t_tree *node)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_out)
	{
		if (node->token->outfile->type == OUTFILE)
		{
			if (open_file_out_utils(node, fd, i) == FAILURE)
				return (FAILURE);
		}
		else if (node->token->outfile->type == OUTFILE_APND)
		{
			fd = open(node->token->outfile[i].file,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (check_error_and_close_fd(node->token->outfile->file, fd, i,
					node->token->nb_file_out) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	node->token->fd_out = fd;
	return (SUCCESS);
}

int	open_file(t_tree *node)
{
	t_data	*data;
	int		ret;

	data = _data();
	ret = SUCCESS;
	data->nb_heredoc = 0;
	if (node->token->nb_file_in > 0)
		ret = open_file_in(node);
	if (node->token->nb_file_out > 0)
		ret = open_file_out(node);
	return (ret);
}
