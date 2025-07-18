/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 05:52:16 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 05:52:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"
#include "minish.h"

void	clean_tokenstream(t_vec *v)
{
	size_t	i;
	t_tok	*t;

	if (!v || !v->size || !v->data)
		return ;
	i = 0;
	while (i < v->size)
	{
		t = (t_tok *)ft_vec_get(v, i++);
		if (!t)
			continue ;
		ft_tstr_free(&t->s);
	}
	ft_vec_free(v);
}

static void	clean_err(char *str, t_vec *out)
{
	write(2, str, ft_strlen(str));
	clean_tokenstream(out);
}

static void	manage_paren(t_tok *t, size_t *paren_l)
{
	if (!t || !t->s.data || !t->s.len)
		return ;
	if (t->type == TOK_LPAREN)
		(*paren_l)++;
	else if (t->type == TOK_RPAREN)
		(*paren_l)--;
}

t_vec	lex(t_string *s)
{
	t_vec	out;
	size_t	offst;
	size_t	paren_l;

	if (!s || !s->len)
		return ((t_vec){0});
	paren_l = 0;
	offst = 0;
	out = ft_vec(10, sizeof(t_tok));
	while (offst < s->len)
	{
		try_lexas_spc(s, &out, &offst);
		if (offst == SIZE_MAX)
			return (clean_tokenstream(&out), (t_vec){0});
		if (!try_lexas_qs(s, &out, &offst))
			return (clean_tokenstream(&out), (t_vec){0});
		try_lexas_ident(s, &out, &offst);
		try_lexas_op(s, &out, &offst);
		manage_paren((t_tok *)ft_vec_peek_last(&out), &paren_l);
	}
	if (paren_l != 0)
		return (clean_err(ANSI_RED"error: "ANSI_RESET"unclosed paren\n", &out),
			(t_vec){0});
	return (out);
}
