/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:19:03 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 18:28:07 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && !is_quoted(i, cmd))
			i++;
		else
		{
			len++;
			while (cmd[i] && (cmd[i] != ' ' || (cmd[i] == ' '
						&& is_quoted(i, cmd))))
				i++;
		}
	}
	return (len);
}

static int	count_word_len(char *cmd, int index)
{
	int	len;

	len = 0;
	while (cmd[index])
	{
		if (ft_iswhitespaces(cmd[index]) && !is_quoted(index, cmd))
			break ;
		len++;
		index++;
	}
	return (len);
}

char	**split_quoted(char *cmd)
{
	char	**ret;
	int		i;
	int		word_len;
	int		j;

	if (!cmd)
		return (NULL);
	ret = ft_calloc(sizeof(char *), (count_word(cmd) + 1));
	if (!ret)
		free_all(QUIT);
	j = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && ft_iswhitespaces(cmd[i]) && !is_quoted(i, cmd))
			i++;
		if (!cmd[i])
			break ;
		word_len = count_word_len(cmd, i);
		ret[j] = ft_substr(cmd, i, word_len);
		j++;
		i += word_len;
	}
	ret[j] = NULL;
	return (ret);
}
