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

static bool	isexported(t_tok *t, size_t i)
{
	if (i > 2 && (t - 3)->type == TOK_IDENT
		&& !ft_strcmp("export", (t - 3)->s.data))
		return (true);
	return (false);
}

void	varexp_parser(t_tok *t, t_vec *tokv, t_data *data, size_t i)
{
	bool	exported;

	(void)tokv;
	(void)data;
	dump_tokenstream("hello", tokv);
	if ((i > 0 && !isstringtoken(t - 1)) || i == 0)
		t->type = TOK_IDENT;
	exported = isexported(t, i);
	(void)exported;
}
