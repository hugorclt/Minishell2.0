/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 00:05:05 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/23 21:14:28 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_nl_flag(char *arg)
{
	int	i;

	i = 0;
	if (ft_strncmp(arg, "-n", 2) == 0)
		i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (TRUE);
	return (FALSE);
}

void	builtin_echo(char **arg)
{
	int	i;
	int	print_nl;

	i = 0;
	print_nl = TRUE;
	while (arg[i] && is_nl_flag(arg[i]))
	{
		printf("here\n");
		i++;
		print_nl = FALSE;
	}
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
