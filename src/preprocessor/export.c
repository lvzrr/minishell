/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:06:47 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/31 14:07:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	inject_builtin(t_vec *tokv, size_t i)
{
	t_string	news;

	news = ft_tstr_from_cstr("_sh__builtin_export");
	tok_push_indexed(tokv, &news, i);
	ft_tstr_free(&news);
}

void	expand_and_load(t_tok *name, t_tok *val, t_data *data)
{
	if (val->type == TOK_STRING_TOEXPAND)
		expand_string(val, data);
	else if (val->type == TOK_VAR)
		expand_var(val, data);
	load_var(&name->s, &val->s, data);
}

/*
*	A este punto tienen que llegar los NOMBRES de las variables
*	
*	Casos:
*	- FOO = BAR	-> invalido
*	- FOO =BAR	-> invalido
*	- FOO=BAR	-> valido
*	- FOO= BAR	-> valido
*
*	export hello hello -> valido, como no tienen un
*	igual despues del espacio, lo borramos.
*
*	export hello -> valido, se borra
*/

bool	check_and_export(t_tok **t, t_vec *tokv, t_data *data, size_t i)
{
	t_string	empty;

	if (i + 1 < tokv->size && (*t + 1)->type == TOK_EQ)
	{
		if (i + 2 < tokv->size && isassignable(t))
			expand_and_load(*t, *t + 2, data);
		else if (i + 2 < tokv->size && (*t + 2)->type == TOK_SPACE)
		{
			empty = ft_tstr_from_cstr("");
			(load_var(&(*t)->s, &empty, data), ft_tstr_free(&empty));
		}
		else if (i + 1 == tokv->size - 1 && (*t + 1)->type == TOK_EQ)
		{
			empty = ft_tstr_from_cstr("");
			(load_var(&(*t)->s, &empty, data), ft_tstr_free(&empty));
		}
		else
			return (syntax_err("assignments have to be strings\n"), false);
		(collapse_at(tokv, i), collapse_at(tokv, i), collapse_at(tokv, i));
		return (true);
	}
	else if (i + 2 < tokv->size && (*t + 1)->type == TOK_SPACE
		&& (*t + 2)->type == TOK_EQ)
		return (syntax_err("bad assignment\n"), false);
	return (collapse_at(tokv, i), true);
}

bool	builtin_export(t_tok **t, t_vec *tokv, t_data *data, size_t i)
{
	if ((i > 0 && (isstringtoken(*t - 1) || (*t - 1)->type == TOK_SPACE))
		|| (i + 1 < tokv->size && isstringtoken(*t + 1)))
		return (true);
	collapse_at(tokv, i);
	if (!tokv->size || i == tokv->size - 1)
	{
		(inject_builtin(tokv, i), *t = ft_vec_get_mut(tokv, i));
		return (true);
	}
	while (tokv->size)
	{
		if (isoperator(*t))
			break ;
		else if ((*t)->type == TOK_SPACE)
			collapse_at(tokv, i);
		else if ((*t)->type == TOK_IDENT && !check_and_export(t, tokv, data, i))
			return (false);
	}
	return (inject_builtin(tokv, i), *t = ft_vec_get_mut(tokv, i), true);
}
