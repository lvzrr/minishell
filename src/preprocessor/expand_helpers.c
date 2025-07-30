/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:18:36 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/22 16:19:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	remove_scaping_singledollar(t_tok *t)
{
	size_t	i;

	i = 0;
	while (i < t->s.len)
	{
		if (i + 1 < t->s.len && t->s.data[i] == '\\'
			&& t->s.data[i + 1] == '$')
			remove_char(&t->s, i);
		i++;
	}
}

void	delete_subs(t_vec *tokv, size_t start)
{
	size_t	plevel;
	t_tok	*t;

	ft_fprintf(2, ANSI_YELLOW"(┛ಠДಠ)┛彡┻━┻ WARNING: Command substitutions"
		" are not supported (yet): it will be ommited  ᕙ(⇀‸↼‶)ᕗ\n"ANSI_RESET);
	t = ft_vec_get_mut(tokv, start);
	if (t && t->type == TOK_SUBSTITUTION)
	{
		collapse_at(tokv, start);
		return ;
	}
	plevel = 0;
	collapse_at(tokv, start);
	while (start < tokv->size)
	{
		if (t->type == TOK_LPAREN)
			plevel++;
		else if (t->type == TOK_RPAREN)
			plevel--;
		if (plevel == 0)
			break ;
		collapse_at(tokv, start);
	}
	if (t->type == TOK_RPAREN)
		collapse_at(tokv, start);
}
