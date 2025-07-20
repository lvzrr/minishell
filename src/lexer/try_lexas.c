/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_lexas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:33:36 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 20:37:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"

void	try_lexas_spc(t_string *s, t_vec *out, size_t *offst)
{
	t_tok	tmp;

	if (ft_isspace(s->data[*offst]))
	{
		*offst = goto_next(s, *offst);
		tmp = (t_tok){.type = TOK_SPACE,
			.s = ft_tstr_from_cstr(" ")};
		ft_vec_push(out, &tmp, 1);
	}
}

void	try_lexas_ident(t_string *s, t_vec *out, size_t *offst)
{
	size_t	offst2;
	t_tok	tmp;

	if (!s || !s->len)
		return ;
	if (isvalidident(s->data[*offst]) || isunsupported(s->data[*offst]))
	{
		offst2 = eat_ident(s, *offst);
		tmp = (t_tok){.type = TOK_IDENT,
			.s = ft_tstr_from_slice(
				s->data + *offst, offst2 - *offst)};
		if (tmp.s.len < 1)
			return ;
		ft_vec_push(out, &tmp, 1);
		*offst = offst2;
	}
}

void	try_lexas_op(t_string *s, t_vec *out, size_t *offst)
{
	size_t	offst2;
	t_tok	tmp;

	if (!s || !s->len)
		return ;
	if (isvalidop(s->data[*offst]) && ((*offst >= 1
				&& s->data[*offst - 1] != '\\') || *offst == 0))
	{
		offst2 = eat_op(s, *offst);
		tmp = (t_tok){.type = 0,
			.s = ft_tstr_from_slice(
				s->data + *offst, offst2 - *offst)};
		if (tmp.s.len == 1)
		{
			tmp.type = get_token_type_1(&tmp.s);
			if (tmp.type == 0xff)
				tmp.type = get_token_type_1_2(&tmp.s);
		}
		else
			tmp.type = get_token_type_2(&tmp.s);
		if (tmp.s.len < 1)
			return ;
		ft_vec_push(out, &tmp, 1);
		*offst = offst2;
	}
}

bool	try_lexas_qs(t_string *s, t_vec *out, size_t *offst)
{
	size_t	offst2;
	t_tok	tmp;

	offst2 = 0;
	if (s && s->len && s->data[*offst] == '\"')
	{
		tmp.type = TOK_STRING_DQ;
		offst2 = eat_string_dq(s, *offst);
	}
	else if (s && s->len && s->data[*offst] == '\'')
	{
		tmp.type = TOK_STRING_SQ;
		offst2 = eat_string_sq(s, *offst);
	}
	else
		return (true);
	if (offst2 == (size_t) -1)
		return (false);
	tmp.s = ft_tstr_from_slice(s->data + *offst, offst2 - *offst);
	ft_tstr_trim_one(&tmp.s, "\"\'");
	if (tmp.type == TOK_STRING_SQ && ft_tstr_instr(&tmp.s, "$") >= 0)
		tmp.type = TOK_STRING_SQ_NOEXPAND;
	ft_vec_push(out, &tmp, 1);
	return (*offst = offst2, true);
}
