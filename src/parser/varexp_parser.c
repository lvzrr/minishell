/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:38:23 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/25 12:39:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	varexp_parser(t_tok *t, t_vec *tokv, t_data *data, size_t i)
{
	(void)tokv;
	(void)data;
	if ((i > 0 && !isstringtoken(t - 1)) || i == 0)
		t->type = TOK_IDENT;
}
