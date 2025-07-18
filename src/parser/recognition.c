/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:04:13 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:04:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	var_recon(t_vec *tokv)
{
	size_t		i;
	t_tok		*t;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_DOLLAR && (t + 1)->type == TOK_IDENT)
		{
			ft_memswap(t, t + 1, sizeof(t_tok));
			t->type = TOK_VAR;
			collapse_at(tokv, t + 1);
		}
		i++;
	}
}

void	var_recon_instr(t_vec *tokv)
{
	size_t		i;
	t_tok		*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_STRING_DQ && *t->s.data == '$'
			&& ft_s_isblob(t->s.data))
		{
			t->type = TOK_VAR;
			ft_memmove(t->s.data, t->s.data + 1, t->s.len--);
			t->s.data[t->s.len] = 0;
		}
		i++;
	}
}
