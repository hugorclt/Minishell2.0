/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:18:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/24 08:19:04 by hrecolet         ###   ########.fr       */
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
	if (!node->token)
		return (NULL);
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
	if (!node->token)
		return (NULL);
	if (peek_token() == INFILE || peek_token() == OUTFILE || peek_token() == HEREDOC || peek_token() == OUTFILE_APND)
		node->right = create_redirection();
	if (peek_token() == CMD)
		node->token = append_two_token(node->token, get_token());
	return (node);
}

t_tree	*add_node(t_token *token, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	node->token = token;
	node->left = left;
	node->right = right;
	return (node);
}

t_tree	*create_command(void)
{
	if (peek_token() == CMD)
		return (create_simple_cmd());
	else
	{
		free(get_token());
		return (create_and_or());
	}
}

t_tree	*create_pipeline(void)
{
	t_token	*token;
	t_tree	*left;
	t_tree	*right;

	left = create_command();
	while (42)
	{
		if (peek_token() == EOL)
			return (left);
		else if (peek_token() == PIPE)
		{
			token = get_token();
			if (!token)
				return (NULL);
			right = create_command();
			left = add_node(token, left, right);
		}
		else if (peek_token() == RPARENTH)
			free(get_token());
		else
			return (left);
	}
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
		if (peek_token() == EOL)
			return (left);
		else if (peek_token() == AND || peek_token() == OR)
		{
			token = get_token();
			if (!token)
				return (NULL);
			right = create_pipeline();
			left = add_node(token, left, right);
		}
		else if (peek_token() == RPARENTH)
			free(get_token());
	}
}

int	create_tree(void)
{
	t_tree 	**tree;

	tree = _tree();
	(*tree) = create_and_or();
	if (!*tree)
		return (FAILURE);
	return (SUCCESS);
}