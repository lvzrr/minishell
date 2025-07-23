/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_collapse_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:58:59 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/23 14:59:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	try_collapse_redir(t_tok *t, t_vec *tokv, size_t i)
{
	bool	r;

	r = true;
	if (t->type == TOK_RR)
		r = rr(t, tokv, i);
	else if (t->type == TOK_LR)
		r = rl(t, tokv, i);
	else if (t->type == TOK_REDIR)
		r = rd_nn(t, tokv, i);
	else if (t->type == TOK_RAPPEND)
		r = rapp(t, tokv, i);
	if (!r)
		return (false);
	return (true);
}
