/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/20 19:46:10 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*peek_token(void)
{
	t_scanner	*scanner;
	int			end;
	char		*cmd;
	
	scanner = _scanner();
	end = find_end();
	cmd = ft_substring(scanner->cmd, scanner->start_pos, end);
	return (cmd);
}

t_token	*scan_token(void)
{
	t_scanner	*scanner;
	t_token		*token;
	
	scanner = _scanner();
	if (scanner->start_pos == ft_strlen(scanner->cmd))
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		free_all(QUIT);
	scanner->end_pos = find_end();
	token->cmd = ft_substring(scanner->cmd, scanner->start_pos, scanner->end_pos);
	token->id = find_token_id(token->cmd);
	printf("id: %d\n", token->id);
	scanner->start_pos = scanner->end_pos;
	return (token);
}
