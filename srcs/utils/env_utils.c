/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:24:54 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/18 14:50:45 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_node(char *key, char *value)
{
	t_list	**lst;

	lst = _list();
	ft_lstadd_back(lst, ft_lstnew(key, value));
}

static int	find_first_equal(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			return (i);
		i++;
	}
	return (FALSE);
}

void	env_init_list(char **env)
{
	int		i;
	int		equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = find_first_equal(env[i]);
		if (equal_pos == FALSE)
			env_add_node(env[i], NULL);
		else
		{
			env_add_node(ft_substring(env[i], 0, equal_pos),
				ft_substring(env[i], equal_pos + 1, ft_strlen(env[i])));
		}
		i++;
	}
}

void	env_change_value(char *key, char *new_value, int flag)
{
	t_list	*env;

	env = *_list();
	while (env && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
	{
		free(env->value);
		if (!new_value)
			env->value = NULL;
		else
			env->value = ft_strdup(new_value);
	}
	if (flag == FREE)
		free(new_value);
}

void	env_unset_key(char *key)
{
	t_list	**env;

	env = _list();
	ft_lst_remove_if(env, key);
}
