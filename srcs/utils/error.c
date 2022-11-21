/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:19:48 by lbisson           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/19 22:15:14 by lbisson          ###   ########.fr       */
=======
/*   Updated: 2022/11/21 14:02:28 by hrecolet         ###   ########.fr       */
>>>>>>> hugo
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_parsing(char *msg)
{
<<<<<<< HEAD
	dprintf(STDERR, "mimishell: syntax error near unexpected token "
			RED "'%s' \n" RESET, msg);
=======
	ft_putstr_fd("mimishell: syntax error near unexpected token " 
		RED "'%s' \n" RESET, msg);
>>>>>>> hugo
	free_all(FREE);
}
