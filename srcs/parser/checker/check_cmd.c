/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:21:01 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/07 17:26:15 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_token_check(void)
{
	t_token	*token;
	char	*cmd;

	token	= malloc(sizeof(t_token));
	if (!token)
		free_all(QUIT);
	cmd = scan_token();
	token->id = find_token_id(cmd);
	if (strjoin_redir(&token, &cmd) == FAILURE)
		return (free(cmd), free(token), NULL);
	token->cmd = split_quoted(cmd);
	if (!token->cmd)
		return (free(cmd), free_token(token), NULL);
	return (free(cmd), token);
}

void	print_error_unexpected(char *cmd)
{
	char	*error_type;

	if (peek_token() == EOL)
		error_type = ft_strdup("newline");
	else
		error_type = ft_strdup(cmd);
	ft_putstr_fd(PINK "mimishell" RESET, 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd("'\n", 2);
	free(error_type);
	update_last_cmd_status(2);
}

static int	check_first_token(void)
{
	t_token	*token;

	if (peek_token() != CMD && peek_token() != LPARENTH && !is_redir(peek_token()))
	{
		token = get_token_check();
		if (!token)
			return (FAILURE);
		print_error_unexpected(token->cmd[0]);
		free_token(token);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_cmd(char *cmd)
{
	int		is_last_token;
	t_token	*token;
	
	init_scanner(cmd);
	is_last_token = -1;
	if (check_first_token())
		return (FAILURE);
	while (peek_token() != EOL)
	{
		token = get_token_check();
		if (!token)
			return (FAILURE);
		if (token->id >= 0 && token->id <= 6 && (is_last_token == 1 || peek_token() == EOL))
		{
			print_error_unexpected(token->cmd[0]);
			return (FAILURE);
		}
		if (token->id >= 0 && token->id <= 6)
			is_last_token = 1;
		else
			is_last_token = 0;
		free_token(token);
	}
	return (SUCCESS);
}
