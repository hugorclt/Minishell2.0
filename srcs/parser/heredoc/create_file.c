/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:27:59 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/14 13:28:21 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_file(t_tree *node)
{
	t_data	*data;
	char	*nb;
	int		i;

	i = 0;
	data = _data();
	while (i < node->token->nb_file_in)
	{
		if (node->token->infile[i].type == HEREDOC)
		{
			nb = ft_itoa(data->nb_heredoc);
			node->token->infile[i].file = ft_strjoin(".heredoc_file", nb);
			free(nb);
			data->nb_heredoc++;
		}
		i++;
	}
}

void	create_heredoc(t_tree *node)
{
	if (!node)
		return ;
	create_heredoc(node->left);
	if (node->token->id == CMD)
		create_file(node);
	create_heredoc(node->right);
}