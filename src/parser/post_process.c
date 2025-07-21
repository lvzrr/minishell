/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:39:55 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 20:41:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

/*
*	Condicion para que una string se concatene con otra,
*	basicamente que no esten separadas por un espacio,
*	lo que quiere decir que "hola"mundo -> holamundo,
*	pero hola mundo -> hola mundo
*/

static bool	strings_concat(t_tok *t)
{
	return ((t->type == TOK_IDENT
			|| t->type == TOK_STRING_DQ
			|| t->type == TOK_STRING
			|| t->type == TOK_STRING_EMPTY
			|| t->type == TOK_STRING_SQ) && ((t + 1)->type == TOK_IDENT
			|| (t + 1)->type == TOK_STRING_DQ
			|| (t + 1)->type == TOK_STRING_EMPTY
			|| (t + 1)->type == TOK_STRING
			|| (t + 1)->type == TOK_STRING_SQ));
}

/*
*	Una vez que todo lo concatenable esta concatenado,
*	esto quita los espacios de en medio para poder analizar
*	los tokens mejor
*/

static void	clean_spaces(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || (!t->s.len && t->type != TOK_STRING_EMPTY))
		{
			i++;
			continue ;
		}
		if (t->type == TOK_SPACE)
			collapse_at(tokv, i);
		i++;
	}
}

/*
*	Funcion principal del 'parser'
*	colapsa secuencias de tokens y reconoce (y expande)
*	variables en principio,
*
*	TODO: hacer una funcion antes
*	de esta que encuentre asignaciones "inline", aunque
*	se puede dejar asi por ahora.
*
*	El reconocimento de variables deberá ser greedy,
*	es decir, si tenemos
*
*	$hola
*	y el string es
*	$holamundo
*
*	debe dar error, deberemos usar
*	$hola\mundo para que funcione
*	las secuencias $hola\mundo
*	se marcan como TOK_STRING_TOEXPAND
*	así que podemos identificarlas después
*/

void	post_process(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	detect_vars(tokv);
	// TODO: expandir variables aqui
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || (!t->s.len && t->type != TOK_STRING_EMPTY))
		{
			collapse_at(tokv, i);
			continue ;
		}
		if (strings_concat(t))
		{
			t->type = TOK_STRING;
			ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
			collapse_at(tokv, i + 1);
			--i;
		}
		i++;
	}
	clean_spaces(tokv);
}
