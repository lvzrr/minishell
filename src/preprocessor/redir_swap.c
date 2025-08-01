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
	i2 = i;
	collapse_at(tokv, i);
	while (i < tokv->size && isredirect((*t + i)->type))
		++i;
	while (i < tokv->size && isstringtoken(*t + i))
		++i;
	if (i2 != 0)
		++i;
	push_tok_indexed(tokv, &new_tok, i);
	*t = ft_vec_get_mut(tokv, i2);
}

bool	fix_redirs(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i);
		if (t && isredirect(t->type) && i == 0 && tokv->size == 1)
		{
			err("cannot interpret redirect as a command\n");
			return (false);
		}
		if (t && isredirect(t->type) && ((i > 0
					&& (isoperator(t - 1)
						|| (t - 1)->type == TOK_LPAREN)) || i == 0))
		{
			put_redir_after_command(&t, tokv, i);
			continue ;
		}
		++i;
	}
	return (true);
}
