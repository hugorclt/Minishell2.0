/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 23:24:54 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/05 16:38:42 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_node(char *key, char *value)
{
	t_list	**lst;
	
	lst = _list();
	ft_lstadd_back(lst, ft_lstnew(key, value));
}

void	env_init_list(char **env)
{
	int		i;
	char	**splited_env;

	i = 0;
	while (env[i])
	{
		splited_env = ft_split(env[i], '=');
		if (!splited_env || !splited_env[0])
			break ;
		env_add_node(splited_env[0], splited_env[1]);
		i++;
	}
	free_matrix(splited_env);
}

void	env_change_value(char *key, char *new_value)
{
	t_list	*env;

	env	= *_list();
	while (env && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
	{
		free(env->value);
		env->value = ft_strdup(new_value);
	}
}

void	env_unset_key(char *key)
{
	t_list	**env;

	env = _list();
	ft_lst_remove_if(env, key);
}

char	*env_get_value(char	*key)
{
	t_list	*env;

	env = *_list();
	if (ft_strncmp(key, "?", 1) == 0)
		return(ft_itoa(get_last_cmd_status()));
	while (env && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (env && ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		return (ft_strdup(env->value));
	return (ft_strdup(""));
}
