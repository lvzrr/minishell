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

void	expand_instr_wrapper(t_tok *t, t_data *data)
{
	expand_string(t, data);
	remove_scaping_singledollar(t);
}

static bool	opbeforeident(t_tok *t, t_vec *tokv, size_t i)
{
	size_t	i2;

	i2 = 2;
	while (i + i2 < tokv->size)
	{
		if (isstringtoken(t + i2) || (t + i2)->type == TOK_VAR)
			return (false);
		else if (isoperator(t + i2))
			return (true);
		++i2;
	}
	return (true);
}

/*
 *	export hello = world	expresion invalida
 *	export hello= world		expresion invalida
 *
 *	export hello=world		expresion valida
 *	export hello= && world	expresion valida
 *
 *	las secuencias que quita son de:
 *	"export hello=world "
 *
 *	deja
 *
 *	" "
 *
 *	es decir, borra hasta justo el valor de despues.
 *
 *	además, acepta asignaciones del tipo:
 *
 *	export hello="$USER"
 *
 *	y expande el usuario antes de guardar la variable
 *	al entorno.
 *
 *	otro quirk que he pillado es que si quieres asignar
 *	una variable vacia, e.g 'export hello=', NO puedes
 *	poner NADA detras, tienes que dejarlo EXPLICITAMENTE
 *	vacio.
 *
 *	puedes hacer:
 *
 *	'echo "hola" && export hello='
 *
 *	pero en el momento que tenga algo detras olvidate.
 *
 *	Es mas larga la descripcion que la funcion XD
 *
 */

static void	load_exported(t_tok *t, t_data *data, t_vec *tokv, size_t i)
{
	t_string	empty;

	if (i + 1 >= tokv->size || (t + 1)->type == TOK_SPACE)
	{
		empty = ft_tstr_new(1);
		load_var(&(t - 1)->s, &empty, data);
		ft_tstr_free(&empty);
	}
	else if (i + 1 < tokv->size
		&& (isstringtoken(t + 1) || (t + 1)->type == TOK_VAR))
	{
		if ((t + 1)->type == TOK_STRING_TOEXPAND)
			expand_instr_wrapper(t + 1, data);
		else if ((t + 1)->type == TOK_VAR)
			expand_var(t + 1, data);
		load_var(&(t - 1)->s, &(t + 1)->s, data);
	}
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
	collapse_at(tokv, i - 3);
}

static bool	isexported(t_tok *t, size_t i)
{
	if (i > 1 && (t - 2)->type != TOK_SPACE)
		return (false);
	else if (i > 2 && (t - 3)->type == TOK_IDENT
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
*	$ miau &&export ...
*
*	borran el '&&' para que no tire error de 'operador en token
*	terminador', ya que no es culpa del usuario.
*
*
*	ADEMAS:
*	esta secuencia no la admito.
*
*	$ export hello= algo
*
*	igual que las shells canonicas no admiten
*
*	$ export hello=world hola
*
*	al interpretar el espacio de hello como la
*	variable en este caso:
*
*	$ export hello= algo
*
* 	'algo' seria en este caso lo que hola al
* 	anterior, por lo tanto no es válido.
*
*
*	NOTA IMPORTANTE 2:
*
*	si tenemos
*	echo export hello=world,
*	NO PASAMOS EL PARSER, tanto export como hello=world
*	pasan a ser identificadores, mientras que
*	echo && export hello=world SI que se parsea como tal
*
*	OTRA NOTA:
*
*	si la asignacion es 'blah=blah', sin export, se va a volver
*	literalmente una string
*
*	WARNING:
*
*	 IMPORTANTE IMPORTANTE IMPORTANTE:
*
*	si encuentra un export, lo borra y lo sustituye por un
*	identificador o comando: __builtin_export, en el arbol
*	lo identificaremos y lo ignoramos como comando con return 0
*	para que no rompa el control flow.
*
*	La asignacion a *t del final es importantisima, el puntero
*	t de el loop donde se llama a varexp_parser mantiene
*	un puntero que libera la funcion tok_push_indexed, asi que
*	hay que cambiarlo al nuevo vector.
*/

size_t	varexp_parser(t_tok **t, t_vec *tokv, t_data *data, size_t *i)
{
	bool		exported;
	t_string	tmp;

	if (*i == 1)
		return ((*t)->type = TOK_IDENT, true);
	exported = isexported(*t, *i - 1);
	if ((exported && check_interpret(*t, *i - 1)) || !exported)
		return ((*t)->type = TOK_IDENT, (*t) -= 1, true);
	if ((*i - 1 > 0 && ((*t) - 1)->type != TOK_IDENT) || *i - 1 == 0)
	{
		(*t)->type = TOK_IDENT;
		if (exported)
			return ((*t) -= 1, false);
	}
	if (exported)
	{
		if (!opbeforeident(*t, tokv, *i - 1))
			return (false);
		load_exported(*t, data, tokv, *i - 1);
		tmp = ft_tstr_from_cstr("_sh__builtin_export");
		tok_push_indexed(tokv, &tmp, *i - 4);
		*t = ft_vec_get_mut(tokv, *i - 4);
		return (ft_tstr_free(&tmp), (*i) -= 3, true);
	}
	return (true);
}
