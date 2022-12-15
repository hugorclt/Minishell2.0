/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:50:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/12 22:54:12 by lbisson          ###   ########.fr       */
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

int	is_token(char *str, int index)
{
	int			i;
	t_scanner	*scanner;

	i = 0;
	scanner = _scanner();
	while (scanner->token_tab[i])
	{
		if (!ft_strncmp(str + index, scanner->token_tab[i],
				ft_strlen(scanner->token_tab[i])))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	skip_whitespaces(char *cmd, int *i)
{
	while (cmd[*i] && ((cmd[*i] >= '\t' && cmd[*i] <= '\r') || cmd[*i] == ' '))
		(*i)++;
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
		if (cmd[i] == '\'' && nb_dquotes % 2 == 0)
			nb_quotes++;
		else if (cmd[i] == '"' && nb_quotes % 2 == 0)
			nb_dquotes++;
		i++;
	}
	if (nb_quotes % 2 != 0)
		return (TRUE);
	if (nb_dquotes % 2 != 0)
		return (TRUE);
	return (FALSE);
}

int	find_end(void)
{
	t_scanner	*scanner;
	int			i;
	int			j;
	int			is_tok;

	scanner = _scanner();
	i = scanner->start_pos;
	skip_whitespaces(scanner->cmd, &i);
	is_tok = is_token(scanner->cmd, i);
	while (scanner->cmd[i])
	{
		j = 0;
		while (scanner->token_tab[j])
		{
			if (!ft_strncmp(scanner->cmd + i, scanner->token_tab[j],
					ft_strlen(scanner->token_tab[j]))
				&& !is_quoted(i, scanner->cmd))
			{
				if (is_tok)
					i += ft_strlen(scanner->token_tab[j]);
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i);
}
