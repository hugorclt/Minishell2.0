/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:49:10 by hrecolet          #+#    #+#             */
/*   Updated: 2022/11/16 20:54:20 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token_types(void)
{
	t_data	*data;
	
	data = _data();
//	data->token_tab = (char *[]){"&&", "||", ">>", "<<", ">", "<", "|", NULL};
	data->token_tab[0] = "&&";
	data->token_tab[1] = "||";
	data->token_tab[2] = ">>";
	data->token_tab[3] = "<<";
	data->token_tab[4] = ">";
	data->token_tab[5] = "<";
	data->token_tab[6] = "|";
	data->token_tab[7] = NULL;
}

static char	*get_token(char *cmd, int index_start)
{
	int		i;
	t_data	*data;

	i = 0;
	data = _data();
	while (data->token_tab[i] && ft_strncmp(cmd + index_start, data->token_tab[i], 
		ft_strlen(data->token_tab[i])))
		i++;
	return (data->token_tab[i]);
}

t_token	*create_new_token(char *token)
{
	t_token *new_tok;
	t_data	*data;
	int		i;

	i = 0;
	new_tok = malloc(sizeof(t_token));
	data = _data();
	if (!token)
		free_all();
	while (data->token_tab[i] && ft_strncmp(token, data->token_tab[i], 
		ft_strlen(data->token_tab[i])))
		i++;
	new_tok->id = i;
	new_tok->cmd = ft_strdup(token);
	return (new_tok);
}

void	insert_two_token(char *cmd, char *token, int start, int end)
{
	t_list	**lst;
	char	*cmd_to_insert;

	lst = _list();
	cmd_to_insert = ft_substring(cmd, start, end);
	printf("%s, %d, %d\n", cmd_to_insert, start, end);
	printf("isnull: %d\n", cmd_to_insert == NULL);
	if (cmd_to_insert)
	{
		printf("wtf\n");
		ft_lstadd_back(lst, ft_lstnew(create_new_token(cmd_to_insert)));
	}
	ft_lstadd_back(lst, ft_lstnew(create_new_token(token)));
}

void	lexer(char *cmd)
{
	int		i;
	int		start;
	char	*token;
	t_list	**lst;

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
		ft_lstadd_back(lst, ft_lstnew(create_new_token(ft_substring(cmd, start, i))));
	}
}
