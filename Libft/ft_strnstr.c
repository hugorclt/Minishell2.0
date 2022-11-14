/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:39:31 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:34:16 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	to_find = (char *)needle;
	str = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (str);
	while (i < len && haystack[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && i + j < len
			&& str[i + j] == to_find[j])
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
