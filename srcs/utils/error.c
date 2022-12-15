/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:19:48 by lbisson           #+#    #+#             */
/*   Updated: 2022/12/15 07:26:00 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(char *msg)
{
	dprintf(2, "mimishell: syntax error near unexpected token "
		RED "'%s' \n" RESET, msg);
	free_all(FREE);
}

void	error_opening(char *str)
{
	update_last_cmd_status(1);
	if (errno == 13)
	{
		ft_putstr_fd(PINK "mimishell: " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(PINK "mimishell: cannot access " RESET, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	free_all(FREE);
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

void	heredoc_error(char *delim)
{
	ft_putstr(PINK "mimishell:" RESET);
	ft_putstr(" warning: here-document at line 1 delimited by end-of-file (wanted `");
	ft_putstr(delim);
	ft_putstr("'\n");
}