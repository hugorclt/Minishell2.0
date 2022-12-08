/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:16:58 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/08 14:39:45 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_file_in(t_tree *node)
{
	int	i;
	int fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile->type == INFILE)
		{
			fd = open(node->token->infile->file, O_RDONLY);
			if (fd == -1)
				error_opening(node->token->infile);
			else if (i != node->token->nb_file_in - 1)
				close(fd);
		}
		i++;
	}
	node->token->fd_in = fd;
}

static void	open_file_out(t_tree *node)
{
	int	i;
	int fd;

	i = 0;
	fd = 0;
	while (i < node->token->nb_file_out)
	{
		if (node->token->outfile->type == OUTFILE)
		{
			fd = open(node->token->outfile->file, O_RDWR | O_TRUNC | O_CREAT);
			if (fd == -1)
				error_opening(node->token->outfile);
			else if (i != node->token->nb_file_out - 1)
				close(fd);
		}
		else if (node->token->outfile->type == OUTFILE_APND)
		{
			fd = open(node->token->outfile->file, O_APPEND | O_CREAT);
			if (fd == -1)
				error_opening(node->token->outfile);
			else if (i != node->token->nb_file_out - 1)
				close(fd);
		}
		i++;
	}
	node->token->fd_out = fd;
}

void	open_file(t_tree *node)
{
	if (node->token->nb_file_in > 0)
		open_file_in(node);
	if (node->token->nb_file_out > 0)
		open_file_out(node);
}
