/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:38:46 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/12 22:35:33 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		size;

	size = ft_strlen(s1);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		free_all(QUIT);
	result[size] = '\0';
	while (size--)
		result[size] = s1[size];
	return (result);
}
