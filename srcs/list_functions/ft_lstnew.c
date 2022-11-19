/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:36:07 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/19 10:46:06 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(int id, char *cmd)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		free_all(QUIT);
	lst->token = malloc(sizeof(t_token));
	if (!lst->token)
		free_all(QUIT);
	lst->token->id = id;
	lst->token->cmd = ft_strdup(cmd);
	if (!lst->token->cmd)
		free_all(QUIT);
	lst->next = NULL;
	return (lst);
}
