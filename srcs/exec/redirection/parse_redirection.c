/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:15:41 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/20 18:33:29 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_infile(t_token **token, char **cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "<<", 2))
		{
			i += 1;
			len++;
		}
		else if (!ft_strncmp(cmd[i], "<", 1))
			len++;
		i++;
	}
	(*token)->nb_file_in = len;
	return (len);
}

static int	count_outfile(t_token **token, char **cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">>", 2))
		{
			i += 1;
			len++;
		}
		else if (!ft_strncmp(cmd[i], ">", 1))
			len++;
		i++;
	}
	(*token)->nb_file_out = len;
	return (len);
}

void	parse_outfile(t_token **token, char **cmd)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	(*token)->outfile = malloc(sizeof(t_file) * (count_outfile(token, cmd)));
	if (!(*token)->outfile)
		free_all(QUIT);
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">>", 2))
		{
			parse_outfile_utils(token, cmd[i + 1], OUTFILE_APND, j);
			j++;
		}
		else if (!ft_strncmp(cmd[i], ">", 1))
		{
			parse_outfile_utils(token, cmd[i + 1], OUTFILE, j);
			j++;
		}
		i++;
	}
}

void	parse_infile(t_token **token, char **cmd)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	(*token)->infile = malloc(sizeof(t_file) * (count_infile(token, cmd)));
	if (!(*token)->infile)
		free_all(QUIT);
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "<<", 2))
		{
			parse_infile_utils(token, cmd[i + 1], HEREDOC, j);
			j++;
		}
		else if (!ft_strncmp(cmd[i], "<", 1))
		{
			parse_infile_utils(token, cmd[i + 1], INFILE, j);
			j++;
		}
		i++;
	}
}

void	parse_redirection(t_token **token, char **cmd)
{
	count_outfile(token, cmd);
	count_infile(token, cmd);
	(*token)->infile = NULL;
	(*token)->outfile = NULL;
	if ((*token)->nb_file_in)
		parse_infile(token, cmd);
	if ((*token)->nb_file_out)
		parse_outfile(token, cmd);
}
