/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:38:03 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/31 17:40:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	collapse_extra(t_tok **t, t_vec *tokv, size_t i)
{
	if ((*t)->type == TOK_IDENT && i + 1 < tokv->size && isoperator(*t + 1))
		collapse_at(tokv, i);
	if ((*t)->type == TOK_IDENT && i + 3 < tokv->size
		&& (*t + 1)->type == TOK_SPACE && (*t + 2)->type == TOK_IDENT
		&& (*t + 3)->type == TOK_EQ)
		(collapse_at(tokv, i), collapse_at(tokv, i));
	if ((*t)->type == TOK_IDENT && i + 1 >= tokv->size)
		(collapse_at(tokv, i));
}
