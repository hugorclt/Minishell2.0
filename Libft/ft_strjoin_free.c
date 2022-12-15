/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:16:27 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/15 18:21:39 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s2)
		return (s1);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!output)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		++i;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		++j;
	}
	output[i + j] = '\0';
	return (free(s1), output);
}

char	*ft_strjoin_dfree(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s2)
		return (s1);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!output)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		++i;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		++j;
	}
	output[i + j] = '\0';
	return (free(s1), free(s2), output);
}

char	*ft_strjoin_char(char *cmd, char c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!ret)
		return (free(cmd), NULL);
	while (cmd[i])
	{
		ret[i] = cmd[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (free(cmd), ret);
}

char	*ft_expjoin_free(char *s1, char *s2, int to_free)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1)
	{
		s1 = ft_strdup(s2);
		return (free(s2), s1);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_len + 1);
	ft_strlcpy(new_str + s1_len, s2, s2_len + 1);
	if (to_free == S1)
		free(s1);
	else if (to_free == S2)
		free(s2);
	else if (to_free == BOTH)
	{
		free(s1);
		free(s2);
	}
	return (new_str);
}
