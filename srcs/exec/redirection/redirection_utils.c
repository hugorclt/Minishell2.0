/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:32:06 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/20 18:33:20 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_infile_utils(t_token **token, char *cmd, int flag, int j)
{
	char	*line;

	line = ft_strdup(cmd);
	if (flag == HEREDOC)
		(*token)->infile[j].delim = unquote_line(line);
	else if (flag == INFILE)
		(*token)->infile[j].file = unquote_line(line);
	free(line);
	(*token)->infile[j].type = flag;
}

void	parse_outfile_utils(t_token **token, char *cmd, int flag, int j)
{
	char	*line;

	line = ft_strdup(cmd);
	(*token)->outfile[j].file = unquote_line(line);
	free(line);
	(*token)->outfile[j].type = flag;
}
