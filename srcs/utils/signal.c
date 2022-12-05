/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:28:04 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/05 16:19:34 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		update_last_cmd_status(130);
	}
	else if (sig == SIGQUIT)
		update_last_cmd_status(131);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	open("/dev/stdin", O_RDWR);
}

void	sig_choice(int choice)
{
	if (choice == SIG_PARSE)
	{
		signal(SIGINT, sig_handle);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (choice == SIG_EXEC)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (choice == SIG_HEREDOC)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
