/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:47:57 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/16 20:41:06 by hrecolet         ###   ########.fr       */
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
