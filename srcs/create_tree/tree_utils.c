/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:05:04 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/22 01:21:53 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**append_tab(char **tab, char **tab2)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = malloc(sizeof(char *) * (tab_len(tab) + tab_len(tab2) + 1));
	if (!new_tab)
		free_all(QUIT);
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	while (tab2[j])
	{
		new_tab[i] = ft_strdup(tab2[j]);
		i++;
		j++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

t_token	*append_two_token(t_token *tokone, t_token *toketwo)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		free_all(QUIT);
	token->cmd = append_tab(tokone->cmd, toketwo->cmd);
	token->id = tokone->id;
	free_matrix(tokone->cmd);
	free_matrix(toketwo->cmd);
	free(tokone);
	free(toketwo);
	return (token);
}
