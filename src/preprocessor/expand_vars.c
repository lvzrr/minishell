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

void	expand_var(t_tok *t, t_data *data)
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
		v = getvar(t->s.data, &data->env, data);
		ft_tstr_clear(&t->s);
		if (!v)
			t->type = TOK_STRING_EMPTY;
		else
			ft_tstr_pushslice(&t->s, v->value.data, v->value.len);
	}
}

void	look_and_insert(t_tok *t, size_t pos,
	t_string *vname, t_data *data)
{
	t_var		*var;
	t_string	newstr;

	if (t->s.data[pos] == '\\' && !(pos + 1 < t->s.len
			&& t->s.data[pos + 1] == '$'))
		remove_char(&t->s, pos);
	var = getvar(vname->data, &data->env, data);
	if (!var)
	{
		if (!t->s.len)
			t->type = TOK_STRING_EMPTY;
		else
			t->type = TOK_STRING_DQ;
		return ;
	}
	newstr = ft_tstr_from_slice(t->s.data, pos);
	ft_tstr_pushslice(&newstr, var->value.data, var->value.len);
	ft_tstr_pushslice(&newstr, t->s.data + pos, t->s.len - pos);
	ft_tstr_free(&t->s);
	t->s = newstr;
}

ssize_t	get_dollar_notscaped(t_tok *t, size_t *offset)
{
	size_t	i;

	i = *offset;
	while (i < t->s.len)
	{
		if (i + 1 < t->s.len && t->s.data[i] == '$'
			&& (ft_isspace(t->s.data[i + 1]) || t->s.data[i + 1] == '\\'
				|| t->s.data[i + 1] == '\''))
			*offset = i++;
		else if (i > 0 && t->s.data[i] == '$' && t->s.data[i - 1] != '\\')
			return (i);
		else if (i == 0 && t->s.data[i] == '$' && !ft_isspace(t->s.data[i + 1]))
			return (i);
		i++;
	}
	return (-1);
}

void	expand_string(t_tok *t, t_data *data)
{
	ssize_t		pos;
	size_t		l;
	size_t		offset;
	t_string	vname;

	offset = 0;
	pos = get_dollar_notscaped(t, &offset);
	while (pos >= 0)
	{
		remove_char(&t->s, (size_t)pos);
		l = 0;
		while (pos + l < t->s.len && !ft_isspace(t->s.data[pos + l])
			&& t->s.data[pos + l] != '\\' && t->s.data[pos + l] != '$'
			&& t->s.data[pos + l] != '\'')
			++l;
		vname = ft_tstr_from_slice(t->s.data + (size_t)pos, l);
		while (l-- > 0)
			remove_char(&t->s, pos);
		look_and_insert(t, pos, &vname, data);
		ft_tstr_free(&vname);
		pos = get_dollar_notscaped(t, &offset);
	}
	t->type = TOK_STRING_DQ;
}

/*
 *	Tenemos que manejar export DURANTE EL PARSING, por que si no,
 *	cosas como:
 *
 *	$ export miau="miau miau" && "$miau"
 *
 *	no se expandría, se quedarían como dos nodos en el arbol,
 *	en el cual hay un nodo con una string vacia, y habría que
 *	pasar el comando dos veces, cosa que no queremos.
*/

bool	expand_vars(t_vec *tokv, t_data *data)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i++);
		if (t && (t->type == TOK_SUBS_START || t->type == TOK_SUBSTITUTION))
			delete_subs(tokv, --i);
		else if (t && t->type == TOK_IDENT && !ft_strncmp(t->s.data, "export",
				5) && !builtin_export(&t, tokv, data, i - 1))
			return (false);
		else if (t && t->type == TOK_IDENT && !ft_strncmp(t->s.data, "unset", 5)
			&& !unset_builtin(t, tokv, data, i))
			return (false);
		if (t && t->type == TOK_VAR)
			expand_var(t, data);
		else if (t && t->type == TOK_STRING_TOEXPAND)
			(expand_string(t, data), remove_scaping_singledollar(t));
		else if (t && t->type == TOK_EQ)
			t->type = TOK_IDENT;
	}
	if (data->debug)
		dump_tokenstream("POST EXPANSION", tokv);
	return (true);
}
