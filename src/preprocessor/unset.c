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

static bool	flags_last_cond(size_t i, t_tok *t, size_t x, t_vec *tokv)
{
	if (x == SIZE_MAX)
		return (i == 2 && (!ft_strcmp((t + i)->s.data, "-f")
				|| !ft_strcmp((t + i)->s.data, "-v")));
	else
		return (x + i < tokv->size && !isoperator(t + i)
			&& (t + i)->type != TOK_RPAREN);
}

/*
*
*	el statement tiene que ser:
*
*	unset[]ident[]ident[]ident[FIN]
*
*	unset no puede no tener argumentos, es decir
*
*	$ unset
*	$ unset && ...
*	& ...&& unset
*
* 	NO SON VALIDOS.
*
*	tampoco se pude borrar el PATH, lo demás si.
*
*	en el final no puede haber:
*		- strings con espacios (las variables no tienen espacios)
*		- redirecciones (¿para que quieres usar stdin en unset?)
*
*	esta funcion va al final del statement y comprueba estas normas.
*/

bool	look4err(t_tok *t, t_vec *tokv, size_t idx, t_data *data)
{
	bool	hasident;
	size_t	i;

	i = 1;
	hasident = false;
	while (idx + i < tokv->size && ((t + i)->type == TOK_IDENT
			|| (t + i)->type == TOK_SPACE))
	{
		if ((t + i)->type == TOK_IDENT)
			hasident = true;
		check_forbidden_unset(t, i, data);
		if (flags_last_cond(i, t, SIZE_MAX, tokv))
			return (err("unset doesn't support flags\n"), false);
		++i;
	}
	if (idx + i < tokv->size && (isstringtoken(t + i)
			|| (t + i)->type == TOK_VAR))
		return (syntax_err("unset statement can contain identifiers only\n"),
			false);
	else if (!hasident)
		return (syntax_err("unset statement cannot be empty\n"), false);
	else if (flags_last_cond(i, t, idx, tokv))
		return (syntax_err("cannot redirect input to unset\n"), false);
	return (true);
}

/*
*	NOTA:
*		i empieza en el token SIGUIENTE a t.
*
*	- comprueba que la secuencia no sea:
*		echo unset,
*	por que en ese caso no se interpreta como comando
*	despues busca errores con look4err, si no los hay
*	colapsa el vector en el token siguiente al unset,
*	hasta que en dicho elemento no haya ni un espacio ni
*	un identificador, y despues cambia el identificador
*	'unset' por '__builtin_unset'.
*
*	es decir, que puede borrar varias variables de una vez,
*
*	$unset hello world
*
*	borraria tanto '$hello' como '$world'
*/

bool	unset_builtin(t_tok *t, t_vec *tokv, t_data *data, size_t i)
{
	if (i > 1 && !isoperator(t - 1) && (t - 1)->type != TOK_LPAREN)
		return (true);
	if (!look4err(t, tokv, i - 1, data))
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
		ft_tstr_pushslice(&t->s, "_sh__builtin_unset", 18);
	}
	return (load_hot_vars(data), true);
}
