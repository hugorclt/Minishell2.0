/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:47:37 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/21 14:08:50 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_error(char c)
{
	write(2, "mimishell: error: ", 19);
	write(2, &c, 1);
	write(2, " quote not closed\n", 18);
	free_all(FREE);
}

static int	len_wo_quote(char *cmd)
{
	int		len;
	int		i;
	char	first_quotes;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '"'))
		{
			len++;
			first_quotes = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != first_quotes)
				i++;
			if (!cmd[i])
				quote_error(first_quotes);
			else
				len++;
		}
		i++;
	}
	return (i - len);
}

static void	copy_interior(char *cmd, int *i, int *j, char **ret)
{
	char	first_quotes;

	first_quotes = cmd[(*i)];
	(*i)++;
	while (cmd[(*i)])
	{
		if (cmd[(*i)] == first_quotes)
			break ;
		(*ret)[(*j)] = cmd[(*i)];
		(*j)++;
		(*i)++;
	}
	(*i)++;
}

char	*unquote_line(char *cmd)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * len_wo_quote(cmd) + 1);
	if (!ret)
		free_all(QUIT);
	while (cmd[i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '"'))
		{
			copy_interior(cmd, &i, &j, &ret);
			if (!cmd[i])
				break ;
		}
		ret[j] = cmd[i];
		if (!cmd[i])
			break ;
		i++;
		j++;
	}
	ret[j] = '\0';
	return (free(cmd), ret);
}

char	**unquote(char **cmd)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (tab_len(cmd) + 1));
	if (!ret)
		free_all(QUIT);
	while (cmd[i])
	{
		ret[i] = unquote_line(cmd[i]);
		i++;
	}
	ret[i] = NULL;
	return (free(cmd), ret);
}
