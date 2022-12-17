/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:26:49 by hrecolet          #+#    #+#             */
/*   Updated: 2022/12/17 11:26:58 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_scanner **scanner, int *i, int *is_tok)
{
	(*scanner) = _scanner();
	(*i) = (*scanner)->start_pos;
	skip_whitespaces((*scanner)->cmd, i);
	(*is_tok) = is_token((*scanner)->cmd, *i);
}