/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:36:41 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:33:08 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptrdst;

	ptrdst = (unsigned char *)dst;
	if (!dst && !src && n)
		return (NULL);
	while (n--)
		*ptrdst++ = *(unsigned char *)src++;
	return (dst);
}
