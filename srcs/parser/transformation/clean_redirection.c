/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 07:22:19 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 17:55:21 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**clean_redirection(char **str, int nb_in, int nb_out)
{
	int		i;
	char	**ret;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * ((tab_len(str) - (nb_in * 2 + nb_out * 2)) + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		while (!ft_strcmp(str[i], ">") || !ft_strcmp(str[i], "<") 
			|| !ft_strcmp(str[i], "<<") || !ft_strcmp(str[i], ">>"))
			i += 2;
		if (!str[i])
			break ;
		ret[j] = ft_strdup(str[i]);
		j++;
		i++;
	}
	ret[j] = NULL;
	free_matrix(str);
	return (ret);
}