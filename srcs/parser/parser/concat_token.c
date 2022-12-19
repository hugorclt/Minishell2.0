/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:50:05 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 13:45:28 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_strjoin_tab(char **tab1, char **tab2)
{
	char	**ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char *) * (tab_len(tab1) + tab_len(tab2) + 1));
	if (!ret)
		free_all(QUIT);
	i = 0;
	j = 0;
	while (tab1[i])
	{
		ret[j] = ft_strdup(tab1[i]);
		i++;
		j++;
	}
	i = 0;
	while (tab2[i])
	{
		ret[j] = ft_strdup(tab2[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

static void	concat_infile(t_token **ret, t_token *token1, t_token *token2)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < token1->nb_file_in)
	{
		(*ret)->infile[j].type = token1->infile[i].type;
		if (token1->infile[i].type == HEREDOC)
			(*ret)->infile[j].delim = ft_strdup(token1->infile[i].delim);
		else
			(*ret)->infile[j].file = ft_strdup(token1->infile[i].file);
		j++;
	}
	i = 0;
	while (i < token2->nb_file_in)
	{
		(*ret)->infile[j].type = token2->infile[i].type;
		if (token2->infile[i].type == HEREDOC)
			(*ret)->infile[j].delim = ft_strdup(token2->infile[i].delim);
		else
			(*ret)->infile[j].file = ft_strdup(token2->infile[i].file);
		i++;
		j++;
	}
}

static void	concat_outfile(t_token **ret, t_token *token1, t_token *token2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < token1->nb_file_out)
	{
		(*ret)->outfile[j].type = token1->outfile[i].type;
		(*ret)->outfile[j].file = ft_strdup(token1->outfile[i].file);
		i++;
		j++;
	}
	i = 0;
	while (i < token2->nb_file_out)
	{
		(*ret)->outfile[j].type = token2->outfile[i].type;
		(*ret)->outfile[j].file = ft_strdup(token2->outfile[i].file);
		i++;
		j++;
	}
}

static void	concat_file(t_token **ret, t_token *token1, t_token *token2)
{
	(*ret)->nb_file_in = token1->nb_file_in + token2->nb_file_in;
	(*ret)->nb_file_out = token1->nb_file_out + token2->nb_file_out;
	(*ret)->infile = malloc(sizeof(t_file) * (*ret)->nb_file_in);
	(*ret)->outfile = malloc(sizeof(t_file) * (*ret)->nb_file_out);
	if (!(*ret)->infile || !(*ret)->outfile)
	{
		free_token(token1);
		free_token(token2);
		free_all(QUIT);
	}
	concat_infile(ret, token1, token2);
	concat_outfile(ret, token1, token2);
}

t_token	*concat_token(t_token *token1)
{
	t_token	*ret;
	t_token	*token2;

	token2 = get_token();
	ret = malloc(sizeof(t_token));
	if (!ret)
	{
		free_token(token1);
		free_token(token2);
		free_all(QUIT);
	}
	concat_file(&ret, token1, token2);
	ret->cmd = ft_strjoin_tab(token1->cmd, token2->cmd);
	ret->id = token1->id;
	ret->fd_in = 0;
	ret->fd_out = 1;
	free_file(token1);
	free_file(token2);
	free_token(token1);
	free_token(token2);
	return (ret);
}
