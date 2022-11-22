/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/22 01:40:56 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token_id(char *token)
{
	t_scanner	*scanner;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!token[0] || !token)
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

int 	peek_token(void)
{
	t_scanner	*scanner;
	int			end;
	char		*cmd;
	int 		type;

	scanner = _scanner();
	end = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, end);
	type = find_token_id(cmd);
	return (free(cmd), type);
}

char	*scan_token(void)
{
	t_scanner	*scanner;
	char		*cmd;

	scanner = _scanner();
	if (scanner->start_pos == ft_strlen(scanner->cmd))
		return (NULL);
	scanner->end_pos = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, scanner->end_pos);
	scanner->start_pos = scanner->end_pos;
	return (cmd);
}
