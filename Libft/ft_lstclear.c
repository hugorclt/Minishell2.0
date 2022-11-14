/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:35:35 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:32:28 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
