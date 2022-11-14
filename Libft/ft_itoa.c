/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hugorecolet@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:35:12 by hrecolet          #+#    #+#             */
/*   Updated: 2021/11/24 14:32:13 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_length(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		nb_len;
	long	l_n;

	l_n = n;
	nb_len = number_length(l_n);
	if (l_n < 0)
		nb_len += 1;
	result = malloc(sizeof(char) * (nb_len + 1));
	if (result == NULL)
		return (NULL);
	if (l_n < 0)
	{
		result[0] = '-';
		l_n = -l_n;
	}
	if (l_n == 0)
		result[0] = 0 + '0';
	result[nb_len] = '\0';
	while (l_n != 0)
	{
		result[--nb_len] = l_n % 10 + '0';
		l_n = l_n / 10;
	}
	return (result);
}
