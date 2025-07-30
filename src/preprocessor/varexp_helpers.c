/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:44:45 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/26 17:45:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	change_tilde(t_tok *t)
{
	ft_tstr_clear(&t->s);
	ft_tstr_pushslice(&t->s, "$HOME", 5);
	t->type = TOK_STRING_DQ;
}

void	clean_last_space(t_vec *tokv)
{
	t_tok	*t;

	t = ft_vec_peek_last(tokv);
	if (!t || t->type != TOK_SPACE)
		return ;
	collapse_at(tokv, tokv->size - 1);
}

static bool	wildcard_condition(t_tok *t, t_vec *tokv, size_t i)
{
	return (t && t->type == TOK_IDENT && t->s.len == 1 && *t->s.data == '*'
		&& !expand_wildcard(t, tokv, i));
}

bool	pre_clean(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (i + 1 < tokv->size && t && t->type == TOK_SPACE
			&& (isoperator(t + 1) || (i > 0 && isoperator(t - 1)
					&& isstringtoken(t + 1))))
		{
			collapse_at(tokv, i);
			continue ;
		}
		if (i + 1 < tokv->size && t && ((isoperator(t) && isoperator(t + 1))
				|| (i > 0 && isoperator(t) && isoperator(t - 1))))
			return (syntax_err("consecutive operators are not allowed\n"),
				false);
		if (t && t->type == TOK_TILDE)
			change_tilde(t);
		if (wildcard_condition(t, tokv, i))
			return (err("no matches found\n"), false);
		i++;
	}
	return (clean_last_space(tokv), true);
}

bool	check_interpret(t_tok *t, size_t i)
{
	if (i > 3 && (t - 4)->type == TOK_LPAREN)
		return (false);
	else if (i > 0 && (t - 1)->type == TOK_SPACE && i > 5 && isoperator(t - 5))
		return (false);
	else if (i > 3 && isoperator(t - 4))
		return (false);
	else if (i > 3 && !isoperator(t - 4))
		return (true);
	return (false);
}
