/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:43:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/12 19:33:51 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_file(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->nb_file_in)
	{
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

static void	free_tree(t_tree *root)
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

static void	free_env(void)
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

void	free_all(int flag)
{
	t_data	*data;
	
	data = _data();
	free(data->info_cmd.pid);
	ft_bzero(&data->info_cmd, sizeof(t_info_cmd));
	free_tree(data->tree);
	if (flag == QUIT)
	{
		free_env();
		exit(get_last_cmd_status());
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
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	free_token(t_token *token)
{
	free_matrix(token->cmd);
	free(token);
}
