/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:47:57 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/18 20:28:28 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("|%s|\n", tab[i]);
		i++;
	}
}

void	print_lst(void)
{
	t_list	*lst;

	lst = *_list();
	while (lst)
	{
		printf("------\n");
		printf("*%s*\n", lst->token->cmd);
		lst = lst->next;
	}
}

static void	print_tree_utils(t_tree *root, int space)
{
	int	i;

	i = STEP_PRINT_TREE;
	if (!root)
		return ;
	space += STEP_PRINT_TREE;
	print_tree_utils(root->right, space);
	printf("\n");
	while (i < space)
	{
		printf(" ");
		i++;
	}
	printf("%s\n", root->token->cmd);
	print_tree_utils(root->left, space);
}

void	print_tree(void)
{
	t_tree	**tree;
	t_tree	*tmp;

	tree = _tree();
	tmp = (*tree);
	print_tree_utils(tmp, 0);
}

void	print_all_token(void)
{
	t_token	*token;
	int		i;
	
	i = 0;
	while ((token = scan_token()))
	{
		printf("[%d]:%s\n", i, token->cmd);
		i++;
	}
}