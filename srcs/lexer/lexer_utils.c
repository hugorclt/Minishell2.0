/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:50:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/18 20:45:13 by hrecolet         ###   ########.fr       */
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

int	is_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	find_token_id(char *token)
{
	t_scanner	*scanner;
	int	i;

	i = 0;
	scanner = _scanner();
	while (scanner->token_tab[i])
	{
		if (ft_strncmp(token, scanner->token_tab[i], ft_strlen(scanner->token_tab[i])))
			break ;
		i++;
	}
	return (i);
}

int	is_quoted(int index, char *cmd)
{
	int	i;
	int	nb_quotes;
	int	nb_dquotes;

	i = 0;
	nb_quotes = 0;
	nb_dquotes = 0;
	while (i <= index)
	{
		if (cmd[i] == '\'')
			nb_quotes++;
		else if (cmd[i] == '"')
			nb_dquotes++;
		i++;
	}
	if (nb_quotes % 2 != 0)
		return (1);
	if (nb_dquotes % 2 != 0)
		return (1);
	return (0);
}

void	skip_whitespaces(char *cmd, int *i)
{
	while (cmd[*i] && ((cmd[*i] >= '\t' && cmd[*i] <= '\r') || cmd[*i] == ' '))
		(*i)++;
}

int	find_end(void)
{
	t_scanner	*scanner;
	int			i;
	int			is_tok;
	int			j;
	
	scanner = _scanner();
	i = scanner->start_pos;
	skip_whitespaces(scanner->cmd, &i);
	is_tok = is_token(scanner->cmd[i]);
	while (scanner->cmd[i])
	{
		j = 0;
		while (scanner->token_tab[j])
		{
			if (!ft_strncmp(scanner->cmd + i, scanner->token_tab[j], ft_strlen(scanner->token_tab[j]))
			&& !is_quoted(i, scanner->cmd))
			{
				if (is_tok)
					i += ft_strlen(scanner->token_tab[j]);
				printf("i = %d, is tok = %d, len tok = %d char = %c\n", i, is_tok, ft_strlen(scanner->token_tab[j]), scanner->cmd[i]);
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i);
}