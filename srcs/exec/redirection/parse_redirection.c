/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:15:41 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 07:27:22 by hrecolet         ###   ########.fr       */
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
	int	i;
	int	j;

	j = 0;
	i = 0;
	(*token)->outfile = malloc(sizeof(t_file) * (count_outfile(token, cmd)));
	if (!(*token)->outfile)
		free_all(QUIT);
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], ">>", 2))
		{
			(*token)->outfile[j].file = ft_strdup(cmd[i + 1]);
			(*token)->outfile[j].type = OUTFILE_APND;
			j++;
		}
		else if (!ft_strncmp(cmd[i], ">", 1))
		{
			(*token)->outfile[j].file = ft_strdup(cmd[i + 1]);
			(*token)->outfile[j].type = OUTFILE;
			j++;
		}
		i++;
	}
}

void	parse_infile(t_token **token, char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	(*token)->infile = malloc(sizeof(t_file) * (count_infile(token, cmd)));
	if (!(*token)->infile)
		free_all(QUIT);
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "<<", 2))
		{
			(*token)->infile[j].delim = ft_strdup(cmd[i + 1]);
			(*token)->infile[j].type = HEREDOC;
			j++;
		}
		else if (!ft_strncmp(cmd[i], "<", 1))
		{
			(*token)->infile[j].file = ft_strdup(cmd[i + 1]);
			(*token)->infile[j].type = INFILE;
			j++;
		}
		i++;
	}
}

void	parse_redirection(t_token **token, char **cmd)
{
	parse_infile(token, cmd);
	parse_outfile(token, cmd);
}
