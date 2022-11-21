/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:19:48 by lbisson           #+#    #+#             */
/*   Updated: 2022/11/21 20:03:31 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(char *msg)
{
	ft_putstr_fd("mimishell: syntax error near unexpected token " 
		RED "'%s' \n" RESET, msg);
	free_all(FREE);
}
