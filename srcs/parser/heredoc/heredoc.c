/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:03:15 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/16 17:32:09 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_one_file(char *file, char *delimiter)
{
	int		fd;
	char	*line;
	t_data	*data;

	data = _data();
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (42)
	{
		line = readline(">");
		if (!line)
		{
			close(fd);
			if (data->nb_heredoc == -1)
				free_all(QUIT);
			heredoc_error(delimiter);
			return ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			return ((void)close(fd));
		ft_putstr_fd(line, fd);
	}
}

void	write_node_heredoc(t_tree *node)
{
	int		i;

	i = 0;
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile[i].type == HEREDOC)
			write_one_file(node->token->infile[i].file, node->token->infile[i].delim);
		i++;
	}
}

void	write_forked(t_tree *node)
{
	if (!node)
		return ;
	write_forked(node->left);
	if (node->token->id == CMD)
		write_node_heredoc(node);
	write_forked(node->right);
}

void	write_heredoc(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_all(QUIT);
	else if (pid == 0)
	{
		write_forked(*(_tree()));
		free_all(QUIT);
	}
	else
		wait(NULL);
}

void	start_heredoc(void)
{
	create_heredoc(*(_tree()));
	sig_choice(SIG_HEREDOC);
	write_heredoc();
}
