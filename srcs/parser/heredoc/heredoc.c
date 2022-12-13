/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:03:15 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/13 17:00:14 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(t_tree *node)
{
	t_data	*data;
	char	*nb;
	int		i;

	i = 0;
	data = _data();
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile[i].type == HEREDOC)
		{
			nb = ft_itoa(data->nb_heredoc);
			node->token->infile[i].file = ft_strjoin(".heredoc_file", nb);
			free(nb); 
		}
		i++;
	}
}

void	create_heredoc(t_tree *node)
{
	if (!node)
		return ;
	create_heredoc(node->left);
	if (node->token->id == CMD)
		create_file(node);
	create_heredoc(node->right);
}

void	heredoc_error(char *delim)
{
	(void)delim;
	free_all(QUIT);
}

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
			printf("%d\n", data->nb_heredoc);
			if (data->nb_heredoc == -1)
				return (heredoc_error(delimiter));
			return ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			return ((void)close(fd));
		ft_putstr_fd(line, fd);
	}
}

void	write_node_heredoc(t_tree *node)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
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