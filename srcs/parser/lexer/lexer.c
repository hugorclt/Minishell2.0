/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/18 17:58:53 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token_id(char *token)
{
	int			i;
	int			j;
	t_scanner	*scanner;

	i = 0;
	j = 0;
	if (!token || !token[0])
		return (10);
	scanner = _scanner();
	skip_whitespaces(token, &j);
	while (scanner->token_tab[i])
	{
		if (!ft_strncmp(token + j, scanner->token_tab[i],
				ft_strlen(scanner->token_tab[i])))
			break ;
		i++;
	}
	return (i);
}

int	peek_token(void)
{
	int			end;
	int			type;
	char		*cmd;
	t_scanner	*scanner;

	scanner = _scanner();
	end = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, end);
	type = find_token_id(cmd);
	return (free(cmd), type);
}

int	peek_token_tree(void)
{
	int			end;
	int			type;
	char		*cmd;
	t_scanner	*scanner;

	scanner = _scanner();
	end = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, end);
	type = find_token_id(cmd);
	if (type >= OUTFILE_APND && type <= INFILE)
		return (free(cmd), CMD);
	return (free(cmd), type);
}

char	*scan_token(void)
{
	char		*cmd;
	t_scanner	*scanner;

	scanner = _scanner();
	if (scanner->start_pos == ft_strlen(scanner->cmd))
		return (NULL);
	scanner->end_pos = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, scanner->end_pos);
	scanner->start_pos = scanner->end_pos;
	return (cmd);
}

t_token	*get_token(void)
{
	char	*cmd;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		free_all(QUIT);
	cmd = scan_token();
	token->id = find_token_id(cmd);
	if (strjoin_redir(&token, &cmd) == FAILURE)
		return (free(cmd), free(token), NULL);
	token->cmd = split_quoted(cmd);
	token->cmd = expand(token->cmd);
	token->cmd = wildcards(token->cmd);
	parse_redirection(&token, token->cmd);
	token->cmd = clean_redirection(token->cmd,
			token->nb_file_in, token->nb_file_out);
	token->cmd = unquote(token->cmd);
	token->fd_in = 0;
	token->fd_out = 1;
	if (!token->cmd)
		return (free(cmd), free_token(token), NULL);
	return (free(cmd), token);
}
