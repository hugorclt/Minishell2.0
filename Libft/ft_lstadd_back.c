/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:35:19 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:32:20 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last_elem;

	if (alst)
	{
		if (*alst)
		{
			last_elem = ft_lstlast(*alst);
			last_elem->next = new;
			new->next = 0;
		}
		else
			*alst = new;
	}
}
