/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_collapse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:36:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/23 01:37:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	rr(t_tok *t, t_vec *tokv, size_t i)
{
	if (i + 1 < tokv->size && isstringtoken(t + 1))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, i + 1);
	}
	else
		return (syntax_err("'>' must be followed by an identifier\n"),
			false);
	if (i > 0 && isstringtoken(t - 1) && ft_isnumeric((t - 1)->s.data))
	{
		ft_tstr_push(&t->s, ':');
		ft_tstr_pushslice(&t->s, (t - 1)->s.data, (t - 1)->s.len);
		t->type = TOK_REDIR_FROM_FD;
		collapse_at(tokv, i - 1);
		return (true);
	}
	t->type = TOK_REDIR_TO;
	return (true);
}

bool	rl(t_tok *t, t_vec *tokv, size_t i)
{
	if (i + 1 < tokv->size && isstringtoken(t + 1))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, i + 1);
	}
	else
		return (syntax_err("'<' must be followed by an identifier\n"), false);
	t->type = TOK_REDIR_IN;
	return (true);
}

bool	rapp(t_tok *t, t_vec *tokv, size_t i)
{
	if (i + 1 < tokv->size && isstringtoken(t + 1))
	{
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, i + 1);
	}
	else
		return (syntax_err("'>>' must be followed by an identifier\n"),
			false);
	if (i > 0 && isstringtoken(t - 1) && ft_isnumeric((t - 1)->s.data))
	{
		ft_tstr_push(&t->s, ':');
		ft_tstr_pushslice(&t->s, (t - 1)->s.data, (t - 1)->s.len);
		t->type = TOK_APPEND_FROM_FD;
		collapse_at(tokv, i - 1);
		return (true);
	}
	t->type = TOK_APPEND_TO;
	return (true);
}

/*
*	CASO ESPECIAL:
*	para 1>&1 y cosas asi donde se "redirige hacia si mismo",
*	simplemente nos cargamos el token, no sirve de nada nada
*	mas que para liar luego.
*/
bool	rd_nn(t_tok *t, t_vec *tokv, size_t i)
{
	if (i + 1 < tokv->size && isstringtoken(t + 1)
		&& i > 0 && isstringtoken(t - 1)
		&& ft_isnumeric((t - 1)->s.data) && ft_isnumeric((t + 1)->s.data))
	{
		if (!ft_strcmp((t + 1)->s.data, (t - 1)->s.data))
			return (delete_redundant(tokv, i));
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, (t - 1)->s.data, (t - 1)->s.len);
		ft_tstr_push(&t->s, ':');
		ft_tstr_pushslice(&t->s, (t + 1)->s.data, (t + 1)->s.len);
		collapse_at(tokv, i - 1);
		collapse_at(tokv, i--);
	}
	else
		return (syntax_err("'>&' should be wrapped in numbers, "
				"like this: [spc]N>&N[spc]\n"), false);
	if (i + 1 < tokv->size && isstringtoken(t))
		return (syntax_err("'>&' must be followed by a delimeter or a newline\n"
			), false);
	(t - 1)->type = TOK_REDIR_NN;
	return (true);
}

bool	manage_redirs(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i);
		if (!t)
		{
			i++;
			continue ;
		}
		if (!try_collapse_redir(t, tokv, i))
			return (false);
		i++;
	}
	return (true);
}
