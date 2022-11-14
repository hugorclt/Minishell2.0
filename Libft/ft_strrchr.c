/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:39:37 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:34:21 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*src;

	src = (char *)s;
	i = ft_strlen(s);
	while (i)
	{
		if (src[i] == (char)c)
			return (src + i);
		i--;
	}
	if (src[i] == (char)c)
		return (src + i);
	return (NULL);
}
