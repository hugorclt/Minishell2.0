/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 01:20:43 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/19 19:16:00 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_remove_if(t_list **begin_list, char *key_ref)
{
	t_list	*cur;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	cur = *begin_list;
	if (ft_strncmp(cur->key, key_ref, ft_strlen(key_ref)) == 0)
	{
		*begin_list = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		return ;
	}
	cur = *begin_list;
	ft_lst_remove_if(&cur->next, key_ref);
}
