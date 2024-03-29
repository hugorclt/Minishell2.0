/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:18:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/19 17:39:33 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_simple_cmd(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		free_all(QUIT);
	ft_bzero(node, sizeof(t_tree));
	node->token = get_token();
	if (!node->token)
		return (free(node), NULL);
	return (node);
}

t_tree	*create_command(void)
{
	if (peek_token_tree() == CMD)
		return (create_simple_cmd());
	else if (peek_token_tree() != EOL)
	{
		free_token(get_token());
		return (create_and_or());
	}
	return (NULL);
}

t_tree	*create_pipeline(void)
{
	t_token	*token;
	t_tree	*left;
	t_tree	*right;

	left = create_command();
	while (42)
	{
		if (peek_token_tree() == EOL)
			return (left);
		else if (peek_token_tree() == PIPE)
		{
			token = get_token();
			if (!token)
				return (NULL);
			right = create_command();
			left = add_node(token, left, right);
		}
		else if (peek_token_tree() == RPARENTH)
			free_token(get_token());
		else if (peek_token_tree() == CMD)
			left->token = concat_token(left->token);
		else
			return (left);
	}
	return (NULL);
}

t_tree	*create_and_or(void)
{
	t_token	*token;
	t_tree	*left;
	t_tree	*right;

	left = create_pipeline();
	while (42)
	{
		if (peek_token_tree() == EOL)
			return (left);
		else if (peek_token_tree() == AND || peek_token_tree() == OR)
		{
			token = get_token();
			if (!token)
				return (NULL);
			right = create_pipeline();
			left = add_node(token, left, right);
		}
		else if (peek_token_tree() == RPARENTH)
			free_token(get_token());
	}
}

int	create_tree(void)
{
	t_tree	**tree;

	tree = _tree();
	(*tree) = create_and_or();
	if (!*tree)
		return (FAILURE);
	init_parent(*tree, NULL);
	return (SUCCESS);
}
