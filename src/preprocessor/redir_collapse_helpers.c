/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_collapse_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:58:59 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/23 14:59:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	isredirect(t_toktype t)
{
	return (t == TOK_REDIR_NN || t == TOK_REDIR_IN
		|| t == TOK_REDIR_TO || t == TOK_APPEND_TO || t == TOK_REDIR_FROM_FD
		|| t == TOK_APPEND_FROM_FD || t == TOK_WRITE_IN || t == TOK_HDOC);
}

bool	delete_redundant(t_vec *tokv, size_t i)
{
	collapse_at(tokv, i);
	collapse_at(tokv, i);
	collapse_at(tokv, i - 1);
	return (true);
}

/*
*	Vale, esto deja secuencias de comandos seguidos
*	por un cojon de redirecciones.
*
*	bloquea cosas como
*	echo && > hello
*	pero deja pasar:
*	cat < miau >> texto 1>&2
*/

bool	is_preceded_by_ident(t_tok *t)
{
	size_t	i;

	i = 1;
	while ((t - i)->type == TOK_SPACE || isredirect((t - i)->type))
		i++;
	if (isstringtoken(t - i))
		return (true);
	else
		return (false);
}

bool	rhdoc(t_tok *t, t_vec *tokv, size_t i)
{
	if (i + 1 < tokv->size && isstringtoken(t + 1))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, i + 1);
	}
	else
		return (syntax_err("'<<' must be followed by an identifier\n"), false);
	return (true);
}

bool	try_collapse_redir(t_tok *t, t_vec *tokv, size_t i)
{
	bool	r;

	r = true;
	if (t->type == TOK_RR)
		r = rr(t, tokv, i);
	else if (t->type == TOK_LR)
		r = rl(t, tokv, i);
	else if (t->type == TOK_REDIR)
		r = rd_nn(t, tokv, i);
	else if (t->type == TOK_RAPPEND)
		r = rapp(t, tokv, i);
	else if (t->type == TOK_HDOC)
		r = rhdoc(t, tokv, i);
	if (!r)
		return (false);
	return (true);
}
