/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:07 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 12:29:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

static bool	strings_concat(t_tok *t)
{
	return ((t->type == TOK_IDENT
			|| t->type == TOK_STRING_DQ
			|| t->type == TOK_STRING
			|| t->type == TOK_STRING_SQ) && ((t + 1)->type == TOK_IDENT
			|| (t + 1)->type == TOK_STRING_DQ
			|| (t + 1)->type == TOK_STRING
			|| (t + 1)->type == TOK_STRING_SQ));
}

void	collapse_at(t_vec *tokv, t_tok *t)
{
	ft_tstr_free(&t->s);
	ft_memmove(t, t + 1, (tokv->size - 1) * tokv->sizeof_type);
	--tokv->size;
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
			collapse_at(tokv, t);
		i++;
	}
}

void	join_seq(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	var_recon(tokv);
	var_recon_instr(tokv);
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
			collapse_at(tokv, t + 1);
			--i;
		}
		i++;
	}
	clean_spaces(tokv);
}
