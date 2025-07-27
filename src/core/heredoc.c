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
	if (t->type == TOK_HDOC && idx > 0
		&& isoperator(t - 1))
		return (syntax_err("heredoc must be preceded by "
				"a command or redirect\n"), (t_vec){0});
	else if (t->type == TOK_HDOC && idx + 1 < tokv->size
		&& isstringtoken(t + 1))
	{
		tokenseq_end = ft_vec(tokv->size - idx, sizeof(t_tok));
		vec_push_tokens_from(&tokenseq_end, tokv, idx);
		return (tokenseq_end);
	}
	else if (t->type == TOK_HDOC && idx + 1 < tokv->size
		&& !isstringtoken(t + 1))
		return (syntax_err("no hdoc terminator\n"), (t_vec){0});
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
*
*	lo voy a volver a comentar por si vuelve a pasar,
*	hdoc_ret se libera FUERA de vec_push_hdoc.
*
*	hdoc_ret es una GLOBAL EN ESTE SCOPE.
*
*	TODAS LAS LINEAS QUE ENTREN AL HEREDOC SE ALMACENAN
*	EN HDOC_RET. Para ahorrar memoria y ganar accesso rapido
*
*/

static bool	hdoc_loop(t_vec *hdoc_exit, size_t idx,
	t_vec *tokv, t_data *data)
{
	t_string	hdoc_ret;

	hdoc_ret = ft_tstr_new(100);
	while (1)
	{
		if (!read_l_hdoc(&data->prompt, &hdoc_ret))
			continue ;
		if (data->hdoc_terminate)
			return (ft_tstr_free(&hdoc_ret), clean_tokenstream(hdoc_exit),
				default_prompt(data), false);
		if (hdoc_ret.len == ((t_tok *)hdoc_exit->data)[0].s.len
			&& !ft_strcmp(hdoc_ret.data, ((t_tok *)hdoc_exit->data)[0].s.data))
			return (ft_tstr_free(&hdoc_ret), clean_tokenstream(hdoc_exit),
				default_prompt(data), true);
		else
			vec_push_hdoc(tokv, &hdoc_ret, &idx);
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
	if (idx == 0)
		return (syntax_err("no command to pipe heredoc\n"), false);
	while (idx != SIZE_MAX)
	{
		if (!heredoc_routine(tokv, data, idx) || data->hdoc_terminate)
		{
			if (data->hdoc_terminate == true)
			{
				data->hdoc_terminate = false;
				signal_setup();
			}
			return (false);
		}
		if (data->debug)
			dump_tokenstream("HDOC OUT", tokv);
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
	hdoc_signal_setup();
	hdoc_exit = check_heredoc(tokv, idx);
	if (!hdoc_exit.alloc_size)
		return (false);
	else if (!hdoc_exit.size)
		return (ft_vec_free(&hdoc_exit), true);
	if (data->debug)
		dump_tokenstream("HDOC RETURN SEQ", &hdoc_exit);
	hdoc_prompt(data);
	hdoc_loop(&hdoc_exit, idx, tokv, data);
	return (ft_vec_free(&hdoc_exit), true);
}
