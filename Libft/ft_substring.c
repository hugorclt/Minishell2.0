/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:11:52 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/23 15:15:28 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substring(char const *s, unsigned int start, size_t end)
{
	char	*ret;
	size_t	i;
	size_t	j;

	j = start;
	i = 0;
	ret = malloc(sizeof(char) * (end - start + 1));
	if (!s || !ret)
		free_all(QUIT);
	while (j < end && s[start + i])
	{
		ret[i] = s[start + i];
		j++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
