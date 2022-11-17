/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/17 16:21:40 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_scanner(char *cmd)
{
	t_scanner	*scanner;

	scanner = _scanner();
	scanner->token_tab[0] = "&&";
	scanner->token_tab[1] = "||";
	scanner->token_tab[2] = ">>";
	scanner->token_tab[3] = "<<";
	scanner->token_tab[4] = ">";
	scanner->token_tab[5] = "<";
	scanner->token_tab[6] = "|";
	scanner->token_tab[7] = "(";
	scanner->token_tab[8] = ")";
	scanner->token_tab[9] = NULL;
	scanner->start_pos = 0;
	scanner->end_pos = 0;
	scanner->cmd = cmd;
}

static void	skip_space(char *cmd, int *index)
{
	while (cmd[*index] && cmd[*index] == ' ')
		(*index)++;
}

char	*peek_token(void)
{
	
}

char	*scan_token(void)
{
	t_scanner	*scanner;
	
	scanner = _scanner();
	skip_space(cmd, &scanner->start_pos);
}




