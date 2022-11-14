/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:39:05 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:34:01 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = (char *)dst;
	if (!dstsize)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dest[i] = ((char *)src)[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
