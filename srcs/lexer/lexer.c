/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/15 19:04:36 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token_types(void)
{
	t_data	*data;
	
	data = _data();
	data->token_list[0] = "&&\0";
	data->token_list[1] = "||\0";
	data->token_list[2] = ">>\0";
	data->token_list[3] = "<<\0";
	data->token_list[4] = ">\0";
	data->token_list[5] = "<\0";
	data->token_list[6] = "|\0";
	data->token_list[7] = NULL;
}

static char	*get_token(char *cmd, int index_start)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	while (data->token_list[i] && ft_strncmp(cmd + index_start, data->token_list[i], 
		ft_strlen(data->token_list[i])))
		i++;
	return (data->token_list[i]);
}

int	get_id(char *token)
{
	t_data	*data;
	int		i;

	i = 0;
	data = _data();
	if (!token)
		free_all();
	while (data->token_list[i] && ft_strncmp(token, data->token_list[i], 
		ft_strlen(data->token_list[i])))
		i++;
	return (i);
}

void	insert_two_token(char *cmd, char *token, int start, int end)
{
	t_list	*lst;
	char	*cmd_to_insert;

	lst = _list();
	cmd_to_insert = ft_substring(cmd, start, end);
	ft_lstadd_back(&lst, ft_lstnew(get_id(cmd_to_insert), cmd_to_insert));
	ft_lstadd_back(&lst, ft_lstnew(get_id(token), token));
	printf("element inserted= %p\n", lst->token);
}

void	lexer(char *cmd)
{
	int		i;
	int		start;
	char	*token;
	t_list	*lst;
	char	*cmd_to_insert;

	i = 0;
	start = 0;
	lst	= _list();
	init_token_types();
	while (cmd[i])
	{
		token = get_token(cmd, i);
		if (token)
		{
			insert_two_token(cmd, token, start, i);
			i += ft_strlen(token);
			start = i;
		}
		else
			i++;
	}
	if (start != i)
	{
		cmd_to_insert = ft_substring(cmd, start, i);
		ft_lstadd_back(&lst, ft_lstnew(get_id(cmd_to_insert), cmd_to_insert));
		free(cmd_to_insert);
	}
}
