/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:36:27 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:33:00 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	letter;
	char	*str;

	i = 0;
	letter = (char)c;
	str = (char *)s;
	while (i < n)
	{
		if (str[i] == letter)
			return (str + i);
		i++;
	}
	return (NULL);
}
