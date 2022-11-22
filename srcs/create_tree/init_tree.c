/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:18:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/22 01:40:46 by hrecolet         ###   ########.fr       */
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
	if (peek_token() == INFILE || peek_token() == OUTFILE || peek_token() == HEREDOC || peek_token() == OUTFILE_APND) /// error si y'a {echo > in bjr}
		node->right = create_redirection();
	if (peek_token() == CMD)
		node->token = append_two_token(node->token, get_token());
	return (node);
}

t_tree 	*create_pipeline(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	ft_bzero(node, sizeof(t_tree));
	node->left = create_simple_cmd();
	if (peek_token() == PIPE)
	{
		node->token = get_token();
		node->right = create_simple_cmd();
	}
	else if (peek_token() == AND || peek_token() == OR || peek_token() == RPARENTH)
	{
		node->token = get_token();
		node->right = create_and_or();
	}
			
	return (node);
}

t_tree 	*create_and_or(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	ft_bzero(node, sizeof(t_tree));
	node->left = create_pipeline();
	if (peek_token() == AND || peek_token() == OR)
	{
		node->token = get_token();
		node->right = create_pipeline();
	}
	return (node);
}

void	create_tree(void)
{
	t_tree 	**tree;

	tree = _tree();
	(*tree) = create_and_or();
}



				