/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:38:46 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:33:46 by hrecolet         ###   ########.fr       */
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
		return (NULL);
	result[size] = '\0';
	while (size--)
		result[size] = s1[size];
	return (result);
}
