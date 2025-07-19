/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 05:19:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 05:19:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	del_unused(t_vec *tokv, size_t idx)
{
	t_tok	*t;

	t = (t_tok *)ft_vec_get(tokv, idx);
	if (idx + 1 < tokv->size && t->type == TOK_HDOC
		&& ((t_tok *)ft_vec_get(tokv, idx + 1))->type == TOK_IDENT)
	{
		ft_tstr_free(&((t_tok *)tokv->data)[idx].s);
		ft_memmove(&((t_tok *)tokv->data)[idx],
			&((t_tok *)tokv->data)[idx + 1],
			(tokv->size - idx - 1) * sizeof(t_tok));
		tokv->size--;
		ft_tstr_free(&((t_tok *)tokv->data)[idx].s);
		ft_memmove(&((t_tok *)tokv->data)[idx],
			&((t_tok *)tokv->data)[idx + 1],
			(tokv->size - idx - 1) * sizeof(t_tok));
		tokv->size--;
	}
	else if (t->type == TOK_HDOC)
	{
		ft_tstr_free(&((t_tok *)tokv->data)[idx].s);
		ft_memmove(&((t_tok *)tokv->data)[idx],
			&((t_tok *)tokv->data)[idx + 1],
			(tokv->size - idx - 1) * sizeof(t_tok));
		tokv->size--;
	}
}
