/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_vec_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:48:26 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 19:48:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
*	Mira que un vector sea igual que otro
*/

bool	check_vec_eq(t_vec *a, t_vec *b)
{
	size_t	i;
	t_tok	*t1;
	t_tok	*t2;

	if (a == b)
		return (true);
	if ((!a && b) || (a && !b) || a->size != b->size)
		return (false);
	i = 0;
	while (i < a->size)
	{
		t1 = (t_tok *)ft_vec_get(a, i);
		t2 = (t_tok *)ft_vec_get(b, i);
		if (t1->type != t2->type)
			return (false);
		if (ft_strcmp(t1->s.data, t2->s.data))
			return (false);
		i++;
	}
	return (true);
}

/*
*	Copia los tokens y sus strings de un vector a otro
*/

void	vec_deep_copy(t_vec *a, t_vec *b, size_t s)
{
	size_t	i;
	t_tok	t;

	i = s;
	ft_vec_reserve(a, b->size);
	while (i < b->size)
	{
		t = *((t_tok *)ft_vec_get(b, i));
		t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(b, i))->s);
		ft_vec_push(a, &t, 1);
		i++;
	}
}

/*
*	las siguentes funciones son terrorificas, cualquier cosa
*	a mi directo, pero en resumen para los heredoc:
*
*	vec_push_tokens_from:
*
*	token_stream: [a, b, c, <<, d, ..., delim]
*
*	pasan a ser:
*
*	token_stream: [a, b, c , delim, ...]
*	                     ^ idx
*	hdoc_exit: [d]
*	=================================
*
*	copy_helper y vec_push_tokens
*	
*	token_stream [a, b, c]
*                       ^ idx
*   primero, si idx es el ultimp lugar, mete tokens sin
*   mas, si no, primero copia todo lo de a hasta idx en
*   un nuevo vector, pone los elementos nuevos, y copia
*   el resto de a en el vector nuevo, limpia el vector
*   inyectado y el de tokens antiguo, cambiandolo por el
*   nuevo.
*/

void	copy_helper(t_vec *a, t_tok *b, t_vec *c, size_t idx)
{
	size_t	i;
	t_tok	t;

	i = 0;
	while (i < idx)
	{
		t = *((t_tok *)ft_vec_get(a, i));
		t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(a, i))->s);
		ft_vec_push(c, &t, 1);
		i++;
	}
	ft_vec_push(c, b, 1);
}

void	vec_push_hdoc(t_vec *a, t_string *b, size_t *idx)
{
	t_tok			newtok;
	t_tok			*old;

	ft_tstr_push(b, '\n');
	if (*idx == a->size)
	{
		old = ((t_tok *)ft_vec_peek_last(a));
		if (old && old->type == TOK_WRITE_IN)
			ft_tstr_pushslice(&old->s, b->data, b->len);
		else
		{
			newtok = (t_tok){.type = TOK_WRITE_IN, .s = ft_tstr_clone(b)};
			ft_vec_push(a, &newtok, 1);
			(*idx)++;
		}
		ft_tstr_free(b);
		return ;
	}
	vec_push_indexed(a, b, idx);
}

/*
*	Esto antes molaba (era un loop que pillaba hasta el delimeter)
*	PERO BASH SOLO PILLA EL PRIMER TOKEN
*
*
*	para los de atras:
*
*	[a, <<, b, ...]
*	     ^ idx
*
*	luego colapsa dos veces en idx tal que
*	[a, ...]
*	 ^ idx
*
*	y todo lo que añadamos en idx va detras de a, y quitamos
*	lo sobrante del stream de tokens
*
*	me estoy volviendo loco
*/

void	vec_push_tokens_from(t_vec *a, t_vec *b, size_t idx)
{
	size_t	i;
	t_tok	t;

	i = idx;
	collapse_at(b, i);
	t = *((t_tok *)ft_vec_get(b, i));
	t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(b, i))->s);
	ft_vec_push(a, &t, 1);
	collapse_at(b, i);
}
