/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:18:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/23 15:55:45 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree 	*create_redirection(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	ft_bzero(node, sizeof(t_tree));
	node->token = get_token();
	return (node);
}

t_tree 	*create_simple_cmd(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	ft_bzero(node, sizeof(t_tree));
	if (peek_token() == INFILE || peek_token() == OUTFILE || peek_token() == HEREDOC || peek_token() == OUTFILE_APND)
		node->left = create_redirection();
	node->token = get_token();
	if (peek_token() == INFILE || peek_token() == OUTFILE || peek_token() == HEREDOC || peek_token() == OUTFILE_APND)
		node->right = create_redirection();
	if (peek_token() == CMD)
		node->token = append_two_token(node->token, get_token());
	return (node);
}

t_tree	*add_node(t_token *token, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = calloc(1, sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	node->token = token;
	node->left = left;
	node->right = right;
	return (node->left);
}

t_tree	*create_pipeline(void)
{
	return (NULL);
}

t_tree 	*create_and_or(void)
{
	t_token	*token;
	t_tree	*left;
	t_tree	*right;
	
	left = create_pipeline();
	while (42)
	{
		if (peek_token() == 12)
			return (left);
		if (peek_token() == AND || peek_token() == OR)
		{
			token = get_token();
			right = create_pipeline();
			left = add_node(token, left, right);
		}
	}
}

void	create_tree(void)
{
	t_tree 	**tree;

	tree = _tree();
	(*tree) = create_and_or();
}



				