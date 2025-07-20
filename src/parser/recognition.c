/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:04:13 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:04:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

static void	var_recon(t_vec *tokv, t_tok *t, size_t idx)
{
	if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& (t + 1)->type == TOK_IDENT)
	{
		t->type = TOK_VAR;
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, idx + 1);
	}
	else
		if (t->type == TOK_DOLLAR && idx + 1 == tokv->size)
			collapse_at(tokv, idx);
}

static void	var_recon_instr(t_tok *t)
{
	size_t	pos;

	if (t->s.len <= 1)
		return ;
	pos = ft_tstr_instr(&t->s, "$");
	if (pos + 1 < t->s.len && t->s.data[pos + 1] == '(')
		t->type = TOK_SUBSHELL;
	else if (pos == 0 && ft_s_isblob(t->s.data))
	{
		t->type = TOK_VAR;
		return ;
	}
	else if (pos == 0 && !ft_isspace(t->s.data[pos + 1]))
		t->type = TOK_STRING_TOEXPAND;
	else if (pos >= 1 && t->s.data[pos - 1] != '\\')
		t->type = TOK_STRING_TOEXPAND;
	else if (pos >= 1 && t->s.data[pos - 1] == '\\')
		remove_scape(&t->s, pos - 1);
}

void	detect_vars(t_vec *tokv)
{
	t_tok	*t;
	size_t	i;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_DOLLAR)
			var_recon(tokv, t, i);
		if (t->type == TOK_STRING_DQ)
			var_recon_instr(t);
		i++;
	}
}

bool	omit_hdoc(t_vec *tokv)
{
	size_t		i;
	size_t		c;
	t_tok		*t;

	i = 0;
	c = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_HDOC)
		{
			t->type = TOK_IDENT;
			c++;
		}
		i++;
	}
	return (c > 0);
}
