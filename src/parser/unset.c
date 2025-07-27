/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:16:20 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/27 13:18:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	free_var_wrapper(void *ptr)
{
	t_var	*var;

	if (!ptr)
		return ;
	var = ptr;
	free_var(var);
}

void	unset_var(t_string *name, t_data *data)
{
	t_var		*v;
	size_t		i;

	if (!name)
		return ;
	i = 0;
	while (i < data->env.size)
	{
		v = ft_vec_get_mut(&data->env, i);
		if (v && !ft_strcmp(name->data, v->name.data))
		{
			ft_vec_remove_f(&data->env, i, free_var_wrapper);
			return ;
		}
		++i;
	}
}

bool	look4err(t_tok *t, t_vec *tokv, size_t i)
{
	while (i < tokv->size && ((t + i)->type == TOK_IDENT
			|| (t + i)->type == TOK_SPACE))
		++i;
	if (i < tokv->size && isstringtoken(t + i))
		return (syntax_err("unset statement cannot end in a string\n"), false);
	else if (i < tokv->size && !isoperator(t + i))
		return (syntax_err("cannot redirect input to unset\n"), false);
	return (true);
}

bool	unset_builtin(t_tok *t, t_vec *tokv, t_data *data, size_t i)
{
	if (i > 1 && !isoperator(t - 1))
		return (true);
	if (!look4err(t, tokv, i))
		return (false);
	while (i < tokv->size && ((t + 1)->type == TOK_IDENT
			|| (t + 1)->type == TOK_SPACE))
	{
		if (t->type == TOK_SPACE)
		{
			collapse_at(tokv, i);
			continue ;
		}
		unset_var(&(t + 1)->s, data);
		collapse_at(tokv, i);
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, "__builtin_unset", 15);
	}
	return (true);
}
