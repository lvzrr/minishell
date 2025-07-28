/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_vec_helpers_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:17:43 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/24 14:17:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

bool	copy_helper(t_vec *a, t_tok *b, t_vec *c, size_t idx)
{
	size_t	i;
	t_tok	*t2;
	t_tok	t;

	i = 0;
	while (i < idx)
	{
		t = *((t_tok *)ft_vec_get(a, i));
		t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(a, i))->s);
		ft_vec_push(c, &t, 1);
		i++;
	}
	t2 = ft_vec_peek_last(c);
	if (t2 && t2->type == TOK_WRITE_IN)
	{
		ft_tstr_pushslice(&t2->s, b->s.data, b->s.len);
		free_tok(b);
		return (true);
	}
	else
		ft_vec_push(c, b, 1);
	return (false);
}

void	vec_push_indexed(t_vec *a, t_string *b, size_t *idx)
{
	t_vec			c;
	t_tok			newtok;

	newtok = (t_tok){.type = TOK_WRITE_IN, .s = ft_tstr_clone(b)};
	c = ft_vec(a->size + 1, sizeof(t_tok));
	if (copy_helper(a, &newtok, &c, *idx))
		vec_deep_copy(&c, a, *idx);
	else
		vec_deep_copy(&c, a, (*idx)++);
	clean_tokenstream(a);
	ft_vec_free(a);
	ft_tstr_clear(b);
	*a = c;
}

static void	copy_helper_nocollapse(t_vec *a, t_tok *b, t_vec *c, size_t idx)
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

void	tok_push_indexed(t_vec *a, t_string *b, size_t idx)
{
	t_vec			c;
	t_tok			newtok;

	newtok = (t_tok){.type = TOK_IDENT, .s = ft_tstr_clone(b)};
	c = ft_vec(a->size + 1, sizeof(t_tok));
	copy_helper_nocollapse(a, &newtok, &c, idx);
	vec_deep_copy(&c, a, idx);
	clean_tokenstream(a);
	ft_vec_free(a);
	ft_tstr_clear(b);
	*a = c;
}

void	tok_push_space(t_vec *a, size_t idx)
{
	t_vec			c;
	t_tok			newtok;

	newtok = (t_tok){.type = TOK_SPACE, .s = ft_tstr_from_cstr(" ")};
	c = ft_vec(a->size + 1, sizeof(t_tok));
	copy_helper_nocollapse(a, &newtok, &c, idx);
	vec_deep_copy(&c, a, idx);
	clean_tokenstream(a);
	ft_vec_free(a);
	*a = c;
}
