/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:39:55 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 20:41:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"
#include "core.h"

static bool	strings_concat(t_tok *t)
{
	if (t->type == TOK_STRING_EMPTY && ((t + 1)->type == TOK_STRING_DQ
			|| (t + 1)->type == TOK_IDENT || (t + 1)->type == TOK_STRING
			|| (t + 1)->type == TOK_STRING_SQ))
		return (true);
	return ((t->type == TOK_IDENT
			|| t->type == TOK_STRING_DQ
			|| t->type == TOK_STRING
			|| t->type == TOK_STRING_SQ) && ((t + 1)->type == TOK_IDENT
			|| (t + 1)->type == TOK_STRING_DQ
			|| (t + 1)->type == TOK_STRING
			|| (t + 1)->type == TOK_STRING_SQ));
}

static void	clean_spaces(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_SPACE)
			collapse_at(tokv, i);
		i++;
	}
}

static void	try_varcollapse(t_vec *tokv, t_tok *t, size_t *i)
{
	if (*i + 1 < tokv->size && (((t->type == TOK_STRING_DQ
					|| t->type == TOK_STRING
					|| t->type == TOK_IDENT
					|| t->type == TOK_STRING_TOEXPAND
					|| t->type == TOK_STRING_SQ)
				&& ((t + 1)->type == TOK_VAR
					|| (t + 1)->type == TOK_STRING_TOEXPAND))
			|| (((t + 1)->type == TOK_STRING_DQ
					|| (t + 1)->type == TOK_STRING_SQ
					|| (t + 1)->type == TOK_STRING
					|| (t + 1)->type == TOK_IDENT
					|| (t + 1)->type == TOK_STRING_TOEXPAND)
				&& (t->type == TOK_VAR
					|| t->type == TOK_STRING_TOEXPAND))))
	{
		t->type = TOK_STRING_TOEXPAND;
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		if (*i < tokv->size - 1)
			collapse_at(tokv, *i + 1);
		else
			collapse_at(tokv, *i + 2);
		(*i)--;
	}
}

void	post_process(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	detect_vars(tokv);
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (strings_concat(t))
		{
			t->type = TOK_STRING;
			ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
			collapse_at(tokv, i + 1);
			--i;
		}
		try_varcollapse(tokv, t, &i);
		i++;
	}
	clean_spaces(tokv);
}
