/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:03:15 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 15:45:21 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_one_file(int fd, char *delimiter)
{
	char	*line;
	t_data	*data;

	data = _data();
	while (42)
	{
		line = readline(">");
		if (!line)
		{
			if (data->nb_heredoc == -1)
			{
				close_all_heredoc(*(_tree()));
				update_last_cmd_status(1);
				free_all(QUIT);
			}
			heredoc_error(delimiter);
			return ;
		}
		line = expand_env_var(line);
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), (void)close(fd));
		line = ft_strjoin_char(line, '\n');
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	write_node_heredoc(t_tree *node)
{
	int		i;

	i = 0;
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile[i].type == HEREDOC)
			write_one_file(node->token->infile[i].fd,
				node->token->infile[i].delim);
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
		sig_choice(SIG_HEREDOC);
		write_forked(*(_tree()));
		free_all(QUIT);
	}
	else
		wait(NULL);
}

void	start_heredoc(void)
{	
	create_heredoc(*(_tree()));
	write_heredoc();
	close_all_heredoc(*(_tree()));
}
