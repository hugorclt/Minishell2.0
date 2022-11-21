/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 00:05:05 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/20 02:10:19 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_no_nl(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		if (ft_strncmp(arg[i], "-n", 2) == 0)
			j = 1;
		while (arg[i][j] && arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			return(i);
		i++;
	}
	return (i);
}

void	builtin_echo(char **arg)
{
	int	i;
	int	print_nl;

	i = 0;
	print_nl = TRUE;
	i = skip_no_nl(arg);
	if (i > 1)
		print_nl = FALSE;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl == TRUE)
		printf("\n");
	update_last_cmd_status(SUCCESS);
}
