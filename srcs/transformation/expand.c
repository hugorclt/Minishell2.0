/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:05:55 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/23 21:20:46 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*************************************************************************/

static int	print_last_cmd_status(char **args)
{
	int		printed;
	char	*status;
	t_data	*data;

	printed = FALSE;
	data = _data();
	status = (char *)&data->last_cmd_status;
	if (ft_strncmp(args[0], "echo", 4) == 0
		&& ft_strncmp(args[1], "$?", 2) == 0)
	{
		printf("conditon passed\n");
		printf("%d\n", data->last_cmd_status);
		builtin_echo(&status);
		printed = TRUE;
	}
	return (printed);
}

void	expand(char **args)
{
	int		i;
	int		j;
	char	**key;
	char	**value;

	if (ft_strncmp(args[0], "echo", 4) != 0)
		return ;
	if (print_last_cmd_status(args))
		return ;
	i = 1;
	while (args[i])
	{
		j = 0;
		key = ft_split(args[i], '$');
		value = malloc(sizeof(char *) * tab_len(key));
		while (key[j])
		{
			value[j] = env_get_value(key[j]);
			j++;
		}
		builtin_echo(value);
		free_matrix(value);
		i++;
	}
	free_matrix(key);
}
