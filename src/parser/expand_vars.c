/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:40:30 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/22 01:40:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"
#include "env.h"

static void	expand_var(t_tok *t, t_data *data)
{
	t_var	*v;

	t->type = TOK_STRING_DQ;
	if (!ft_strcmp(t->s.data, "PATH"))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, data->path->data, data->path->len);
	}
	else if (!ft_strcmp(t->s.data, "PWD"))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, data->pwd->data, data->pwd->len);
	}
	else
	{
		v = getvar(t->s.data, &data->env);
		ft_tstr_clear(&t->s);
		if (!v)
			t->type = TOK_STRING_EMPTY;
		else
			ft_tstr_pushslice(&t->s, v->value.data, v->value.len);
	}
}

static void	expand_string(t_tok *t, t_data *data)
{
	ssize_t	pos;
	size_t	slicelen;
	char	*vname;
	t_var	*var;

	pos = ft_tstr_instr(&t->s, "$");
	while (pos >= 0)
	{
		slicelen = (size_t)pos;
		while (slicelen < t->s.len && (!ft_isspace(t->s.data[slicelen])
				|| t->s.data[slicelen] != '\\'))
			++slicelen;
		vname = ft_memclone(t->s.data + pos + 1, slicelen);
		var = getvar(vname, &data->env);
		while (--slicelen >= (size_t)pos)
			remove_char(&t->s, pos);
		if (var)
			ft_tstr_insert(&t->s, var->value.data, var->value.len, pos);
		pos = ft_tstr_instr(&t->s, "$");
		ft_free((void **)&vname);
	}
	if (!t->s.len)
		t->type = TOK_STRING_EMPTY;
	else
		t->type = TOK_STRING_DQ;
}

void	expand_vars(t_vec *tokv, t_data *data)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i++);
		if (!t || (t->type != TOK_VAR && t->type != TOK_STRING_TOEXPAND))
			continue ;
		if (t->type == TOK_VAR)
			expand_var(t, data);
		else
			expand_string(t, data);
	}
}
