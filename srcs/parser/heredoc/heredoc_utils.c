/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:34:31 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 17:34:44 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_file(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->nb_file_in)
	{
		if (token->infile[i].type == HEREDOC)
			unlink(token->infile[i].file);
		i++;
	}
}

void	unlink_heredoc(t_tree *node)
{
	if (!node)
		return ;
	unlink_heredoc(node->left);
	if (node->token->nb_file_in)
		unlink_file(node->token);
	unlink_heredoc(node->right);
}
