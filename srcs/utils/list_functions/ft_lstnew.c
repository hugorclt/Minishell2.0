/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:36:07 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/12 22:37:05 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *key, char *value)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		free_all(QUIT);
	lst->key = key;
	lst->value = value;
	lst->next = NULL;
	return (lst);
}
