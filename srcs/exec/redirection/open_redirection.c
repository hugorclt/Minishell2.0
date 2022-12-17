/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:16:58 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/15 17:23:56 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_error_and_close_fd(char *file, int fd, int index, int nb_file)
{
	if (fd == -1)
		error_opening(file);
	else if (index != nb_file - 1)
		close(fd);
}

static void	open_file_in(t_tree *node)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_in)
	{
		fd = open(node->token->infile[i].file, O_RDONLY);
		check_error_and_close_fd(node->token->infile->file, fd, i,
			node->token->nb_file_in);
		i++;
	}
	node->token->fd_in = fd;
}

static void	open_file_out(t_tree *node)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_out)
	{
		if (node->token->outfile->type == OUTFILE)
		{
			fd = open(node->token->outfile[i].file,
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
			check_error_and_close_fd(node->token->outfile->file, fd, i,
				node->token->nb_file_out);
		}
		else if (node->token->outfile->type == OUTFILE_APND)
		{
			fd = open(node->token->outfile[i].file,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			check_error_and_close_fd(node->token->outfile->file, fd, i,
				node->token->nb_file_out);
		}
		i++;
	}
	node->token->fd_out = fd;
}

void	open_file(t_tree *node)
{
	t_data	*data;

	data = _data();
	data->nb_heredoc = 0;
	if (node->token->nb_file_in > 0)
		open_file_in(node);
	if (node->token->nb_file_out > 0)
		open_file_out(node);
}
