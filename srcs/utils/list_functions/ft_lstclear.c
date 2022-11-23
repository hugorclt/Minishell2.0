/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:35:35 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/15 00:31:29 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*t;

	if (lst || *lst || del)
	{
		while (lst && *lst)
		{
			t = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = t;
		}
	}
}
