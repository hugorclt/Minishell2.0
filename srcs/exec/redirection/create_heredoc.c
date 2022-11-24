/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:20:34 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/24 15:07:32 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_opening(char *str)
{
	update_last_cmd_status(1);
	if (errno == 13)
	{
		ft_putstr_fd(PINK "mimishell: " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(PINK "mimishell: cannot access " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	free_all(FREE);
}

char	*get_name()
{
	t_data	*data;
	char	*nb;
	char	*name;

	data = _data();
	data->nb_heredoc++;
	printf("%d\n", data->nb_heredoc);
	nb = ft_itoa(data->nb_heredoc);
	name = ft_strjoin(".heredoc_temp", nb);
	free(nb);
	return (name);
}

int	open_heredoc(t_token **token, int index)
{
	int		fd;

	(*token)->infile[index].file = get_name();
	fd = open((*token)->infile[index].file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		error_opening((*token)->infile[index].file);
	return (fd);
}

void	write_heredoc(int fd, char *delim)
{
	int		pid;
	char	*line;

	pid = fork();
	if (pid == -1)
		free_all(QUIT);
	else if (pid == 0)
	{
		while (42)
		{
			line = readline(" >");
			if (!ft_strncmp(line, delim, ft_strlen(line)))
				break ;
			if (write(fd, line, ft_strlen(line)) == -1)
				free_all(QUIT);
		}
	}
	else
		wait(NULL);
}

void	create_temp_file(t_token **token, char *delimiter, int index)
{
	int	fd;
	
	fd = open_heredoc(token, index);
	sig_choice(SIG_HEREDOC);
	write_heredoc(fd, delimiter);
	sig_choice(SIG_EXEC);
	unlink((*token)->infile[index].file);
	close(fd);
}