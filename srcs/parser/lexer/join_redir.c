/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:33:13 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/24 12:53:40 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(int id)
{
	if (id == OUTFILE_APND || id == HEREDOC || id == INFILE || id == OUTFILE)
		return (TRUE);
	return (FALSE);
}

int	strjoin_redir_redir(t_token **token, char **cmd)
{
	while (is_redir((*token)->id))
	{
		if (peek_token() == CMD)
		{
			*cmd = ft_strjoin_char(*cmd, ' ');
			*cmd = ft_strjoin_dfree(*cmd, scan_token());
			if (!is_redir(peek_token()))
				(*token)->id = CMD;
			else
				*cmd = ft_strjoin_dfree(*cmd, scan_token());
		}
		else
		{
			print_error_unexpected(*cmd);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	strjoin_redir_cmd(t_token **token, char **cmd)
{
	char *tok;
	
	if ((*token)->id == CMD)
	{
		while (is_redir(peek_token()))
		{
			*cmd = ft_strjoin_char(*cmd, ' ');
			*cmd = ft_strjoin_dfree(*cmd, scan_token());
			if (peek_token() == CMD)
			{
				*cmd = ft_strjoin_char(*cmd, ' ');
				*cmd = ft_strjoin_dfree(*cmd, scan_token());
			}
			else
			{
				tok = scan_token();
				print_error_unexpected(tok);
				free(tok);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}
int	strjoin_redir(t_token **token, char **cmd)
{
	if (strjoin_redir_cmd(token, cmd) == FAILURE)
		return (FAILURE);
	if (strjoin_redir_redir(token, cmd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}