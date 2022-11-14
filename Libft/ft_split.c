/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:38:32 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:33:38 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sep(char *str, char charset)
{
	if (*str == charset)
		return (1);
	return (0);
}

static int	ft_letter_count(char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && !(ft_is_sep(str + i, charset)))
		i++;
	return (i);
}

static int	word_count(char *str, char charset)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		if (*str && ft_is_sep(str, charset))
			str++;
		i = ft_letter_count(str, charset);
		str += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*word_cpy(char *str, int size)
{
	char	*dest;

	dest = malloc(sizeof(char) * size + 1);
	if (dest == NULL)
		return (NULL);
	dest[size] = '\0';
	while (size--)
		dest[size] = str[size];
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		size;
	int		j;

	i = 0;
	size = word_count((char *)s, c);
	matrix = malloc(sizeof(char *) * (size + 1));
	if (matrix == NULL)
		return (NULL);
	while (i < size)
	{
		while (*s && ft_is_sep((char *)s, c))
			s++;
		j = ft_letter_count((char *)s, c);
		matrix[i] = word_cpy((char *)s, j);
		if (matrix[i] == NULL)
			return (NULL);
		s += j;
		i++;
	}
	matrix[size] = 0;
	return (matrix);
}
