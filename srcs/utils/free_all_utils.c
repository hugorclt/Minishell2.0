/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 16:09:25 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->nb_file_in)
	{
		if (token->infile[i].type == HEREDOC)
			free(token->infile[i].delim);
		free(token->infile[i].file);
		i++;
	}
	free(token->infile);
	i = 0;
	while (i < token->nb_file_out)
	{
		free(token->outfile[i].file);
		i++;
	}
	free(token->outfile);
}

void	free_tree(t_tree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_file(root->token);
	free_matrix(root->token->cmd);
	free(root->token);
	free_tree(root->right);
	free(root);
}

void	free_env(void)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *(_list());
	while (lst)
	{
		tmp = lst->next;
		free(lst->key);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	if (matrix)
		free(matrix);
	matrix = NULL;
}

void	free_token(t_token *token)
{
	free_matrix(token->cmd);
	free(token);
}
