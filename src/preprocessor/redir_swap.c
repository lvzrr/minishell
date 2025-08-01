/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:49:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/08/01 16:58:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

/*
*
*	para casos como:
*
*	foo.txt < cat
*
*	y redirecciones que se anteponen al comando,
*	lo que hacemos es literalmente cambiarlas
*	de sitio a despues del comando, para
*	que no haya problemas en el parser, se normalizan
*	los comandos a:
*
*	cmd flag flag ... flag redir ... redir OP ...
*/

void	push_tok_indexed(t_vec *a, t_tok *b, size_t idx)
{
	t_vec			c;

	c = ft_vec(a->size + 1, sizeof(t_tok));
	copy_helper_nocollapse(a, b, &c, idx);
	vec_deep_copy(&c, a, idx);
	clean_tokenstream(a);
	ft_vec_free(a);
	*a = c;
}

static void	put_redir_after_command(t_tok **t, t_vec *tokv, size_t i)
{
	t_tok	new_tok;
	size_t	i2;

	new_tok = **t;
	new_tok.s = ft_tstr_clone(&(*t)->s);
	i2 = 0;
	collapse_at(tokv, i);
	if ((*t)->type == TOK_HDOC)
		i += 2;
	while (i + i2 < tokv->size)
	{
		if (!isredirect((*t + i2)->type))
			break ;
		++i2;
	}
	while (i + i2 < tokv->size)
	{
		if (!isstringtoken(*t + i2))
			break ;
		++i2;
	}
	push_tok_indexed(tokv, &new_tok, i + i2);
	*t = ft_vec_get_mut(tokv, i);
}

bool	catch_redir_alone(t_tok *t, t_vec *tokv, size_t i)
{
	if (isredirect(t->type) && i == 0 && tokv->size == 1)
		return (false);
	if (isredirect(t->type) && i > 0 && i + 1 < tokv->size
		&& (t - 1)->type == TOK_LPAREN && isoperator(t + 1))
		return (false);
	if (isredirect(t->type) && i > 0 && i + 1 < tokv->size
		&& (t + 1)->type == TOK_RPAREN && isoperator(t - 1))
		return (false);
	if (isredirect(t->type) && i > 0 && i + 1 == tokv->size
		&& isoperator(t - 1))
		return (false);
	while (i < tokv->size)
	{
		if (!isredirect(t->type))
			break ;
		++i;
		++t;
	}
	return (i != tokv->size && !isoperator(t) && t->type != TOK_RPAREN);
}

bool	fix_redirs(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i);
		if (t && isredirect(t->type) && ((i > 0
					&& (isoperator(t - 1)
						|| (t - 1)->type == TOK_LPAREN)) || i == 0))
		{
			if (t && !catch_redir_alone(t, tokv, i))
			{
				err("cannot interpret redirect as a command\n");
				return (false);
			}
			put_redir_after_command(&t, tokv, i);
			continue ;
		}
		++i;
	}
	return (true);
}
