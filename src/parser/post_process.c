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
*	los tokens mejor.
*
*	El motivo del check de los operadores es que no es lo mismo:
*	echo "hello" > test
*	que
*	echo "hello" 2> test
*	que
*	echo "hello" 2 > test
*
*	Asi que en la primera pasada quita los espacios que no rompen
*	esta regla, y como manage_redirs cambia los tipos primitivos
*	a TOK_REDIR_TO y cosas así, en la segunda pasada, si no se
*	han colapsado en manage_redirs, ahí si que los quita.
*
*/

static void	clean_spaces(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && ((i + 1 < tokv->size && t->type == TOK_SPACE
					&& (t + 1)->type == TOK_EQ)
				|| (i > 0 && t->type == TOK_SPACE
					&& (t - 1)->type == TOK_EQ)))
			;
		else if (!t || !t->s.data || (t->type == TOK_SPACE
				&& i + 1 < tokv->size
				&& (t + 1)->type != TOK_REDIR
				&& (t + 1)->type != TOK_RAPPEND
				&& (t + 1)->type != TOK_RR
				&& (t + 1)->type != TOK_LR))
		{
			collapse_at(tokv, i);
			continue ;
		}
		i++;
	}
}

static bool	redirs_and_clean(t_vec *tokv)
{
	clean_spaces(tokv);
	if (!manage_redirs(tokv))
		return (false);
	clean_spaces(tokv);
	clean_operators(tokv);
	return (true);
}

/*
*	Funcion principal del 'parser'
*	colapsa secuencias de tokens y reconoce (y expande)
*	variables en principio,
*
*	El reconocimento de variables es greedy,
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
*	
*	en detect_vars() automaticamente se quitan
*	los espacios que no rompen el sentido semantico,
*	ademas de detectar y asignar variables antes de
*	colapsar las strings.
*
*/

bool	post_process(t_vec *tokv, t_data *data)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	if (pre_clean(tokv) && !detect_vars(tokv, data))
		return (false);
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
	return (redirs_and_clean(tokv) && catch_forbidden(tokv));
}

/*
最後のダンス 二人だけの思い消したなら
あこがれを 彼方へとつれて
最後のダンス 気にいりのステップをふみながら
今だけは そう このままでいた
*/
