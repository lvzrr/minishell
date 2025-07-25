/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:38:23 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/25 12:39:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

/*
 *	export hello = world	expresion invalida
 *
 *	export hello=world		expresion valida
 *	export hello= world		expresion valida, pero la asignacion esta
 *	                                          vacía.
 */

static void	load_exported(t_tok *t, t_data *data, t_vec *tokv, size_t i)
{
	t_string	empty;

	if (i + 1 >= tokv->size || (t + 1)->type == TOK_SPACE)
	{
		empty = ft_tstr_new(1);
		load_var(&(t - 1)->s, &empty, &data->env);
		ft_tstr_free(&empty);
	}
	else if (i + 1 < tokv->size && isstringtoken(t + 1))
	{
		ft_tstr_trim(&(t - 1)->s, "$");
		load_var(&(t - 1)->s, &(t + 1)->s, &data->env);
	}
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
}

static bool	isexported(t_tok *t, size_t i)
{
	if (i > 2 && (t - 3)->type == TOK_IDENT
		&& !ft_strcmp("export", (t - 3)->s.data))
		return (true);
	else if (i > 3 && (t - 4)->type == TOK_IDENT
		&& !ft_strcmp("export", (t - 4)->s.data))
		return (true);
	return (false);
}

/*
*	Los numeros magicos son básicamente un
*	rewind, por que al limpiar del stream la
*	expresion del export, el puntero 't', se
*	queda en una región invalida del vector,
*	y hay que llevarlo al indice que le corresponde
*	cuando la seccion ha sido borrada.
*
*
*	los checks y colapsos de salida son para cuando
*	el export es parte de una secuencia como:
*
*	$ miau && export ...
*
*	borran el '&&' para que no tire error de 'operador en token
*	terminador', ya que no es culpa del usuario.
*
*/

size_t	varexp_parser(t_tok **t, t_vec *tokv, t_data *data, size_t i)
{
	bool	exported;

	exported = isexported(*t, i);
	if ((i > 0 && ((*t) - 1)->type != TOK_IDENT) || i == 0)
	{
		(*t)->type = TOK_IDENT;
		if (exported)
			return ((*t) -= 1, false);
	}
	if (exported)
	{
		load_exported(*t, data, tokv, i);
		if (tokv->size > 1 && isoperator((t_tok *)ft_vec_peek_last(tokv) - 1))
			collapse_at(tokv, tokv->size - 1);
		else if (tokv->size && isoperator((t_tok *)ft_vec_peek_last(tokv)))
			collapse_at(tokv, tokv->size);
		return ((*t) -= 3, true);
	}
	return ((*t) -= 1, true);
}
