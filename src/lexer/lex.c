/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 05:52:16 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 05:52:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"
#include "minish.h"

t_vec	lex(t_string *s)
{
	t_vec	out;
	size_t	offst;

	if (!s || !s->len)
		return ((t_vec){0});
	offst = 0;
	out = ft_vec(10, sizeof(t_tok));
	while (offst < s->len)
	{
		offst = goto_next(s, offst);
		if (!try_lexas_qs(s, &out, &offst))
			return (out);
		try_lexas_ident(s, &out, &offst);
		try_lexas_op(s, &out, &offst);
	}
	for (size_t j = 0; j < out.size; j++)
	{
		printf("type: %d, tok: %%%s%%\n", ((t_tok *)ft_vec_get(&out, j))->type, ((t_tok *)ft_vec_get(&out, j))->s.data);
		fflush(stdout);
	}
	return (out); // to the parser
}
