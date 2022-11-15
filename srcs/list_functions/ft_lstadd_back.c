/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:35:19 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/15 17:45:25 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
