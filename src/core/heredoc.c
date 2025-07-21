/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:50:08 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 19:50:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
*	Busca tokens << en el stream,
*	si los hubiera, devuelve donde está el primero
*	de ellos, si no, devuelve SIZE_MAX.
*/

size_t	look4hdoc(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			++i;
			continue ;
		}
		if (t->type == TOK_HDOC)
			return (i);
		i++;
	}
	return (SIZE_MAX);
}

/*
*	se cerciona de que el heredoc
*	tiene un identificador detras, si no,
*	lanza un error.
*
*	Ademas borra el identificador del stream
*	a la vez que la secuencia de terminacion
*/

t_vec	check_heredoc(t_vec *tokv, size_t idx)
{
	t_tok	*t;
	t_vec	tokenseq_end;

	t = (t_tok *)ft_vec_get(tokv, idx);
	if (t->type == TOK_HDOC && idx + 1 < tokv->size
		&& (t + 1)->type == TOK_IDENT)
	{
		tokenseq_end = ft_vec(tokv->size - idx, sizeof(t_tok));
		vec_push_tokens_from(&tokenseq_end, tokv, idx);
		return (tokenseq_end);
	}
	return ((t_vec){0});
}

/*
*	Loop principal del heredoc,
*	primero lee la linea, la tokeniza,
*	despues, ignora si hay heredocs dentro,
*	compara si es la secuencia de salida,
*	si lo es, limpia la condicion y sale,
*	si no, añade al stream los tokens en
*	la posición correspondiente.
*/

static bool	hdoc_loop(t_vec *hdoc_exit, size_t idx,
	t_vec *tokv, t_data *data)
{
	t_vec	hdoc_ret;

	while (1)
	{
		read_l(&data->prompt, &hdoc_ret, false);
		omit_hdoc(&hdoc_ret);
		if (!hdoc_ret.size && !hdoc_ret.data)
		{
			clean_tokenstream(&hdoc_ret);
			continue ;
		}
		post_process(&hdoc_ret);
		if (check_vec_eq(&hdoc_ret, hdoc_exit))
			return (clean_tokenstream(&hdoc_ret),
				clean_tokenstream(hdoc_exit), default_prompt(data)
				, true);
		else
		{
			vec_push_tokens(tokv, &hdoc_ret, &idx);
			if (data->debug)
				dump_tokenstream("HDOC STREAM", tokv);
		}
	}
}

/*
*	Mira si hay heredocs en la string, mientras haya,
*	no sale, es decir, bloquea todo hasta que no quede
*	ninguno, lo que hace que pueda manejar varios en el
*	input
*/

bool	heredoc(t_vec *tokv, t_data *data)
{
	size_t	idx;

	idx = look4hdoc(tokv);
	while (idx != SIZE_MAX)
	{
		if (!heredoc_routine(tokv, data, idx))
			return (false);
		idx = look4hdoc(tokv);
	}
	return (true);
}

/*
*	Propaga el error de check_heredoc, y pone el loop
*	a punto con el prompt
*/

bool	heredoc_routine(t_vec *tokv, t_data *data, size_t idx)
{
	t_vec	hdoc_exit;

	if (!tokv || !tokv->size || !tokv->data)
		return (true);
	hdoc_exit = check_heredoc(tokv, idx);
	if (!hdoc_exit.size
		&& ((((t_tok *)ft_vec_peek_last(tokv))->type == TOK_HDOC)
			|| (((t_tok *)ft_vec_get(tokv, idx)) + 1)->type != TOK_IDENT))
		return (ft_fprintf(2, ANSI_RED"syntax error: "
				ANSI_RESET"no hdoc terminator\n"), false);
	else if (!hdoc_exit.size)
		return (true);
	if (data->debug)
		dump_tokenstream("HDOC RETURN SEQ", &hdoc_exit);
	hdoc_prompt(data);
	hdoc_loop(&hdoc_exit, idx, tokv, data);
	if (data->debug)
		dump_tokenstream("HDOC OUT", tokv);
	return (true);
}
