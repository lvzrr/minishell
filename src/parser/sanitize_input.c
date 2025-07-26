/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:22:50 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/26 00:23:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	isoperator(t_tok *t)
{
	if (!t)
		return (false);
	return (t->type == TOK_AND || t->type == TOK_OR || t->type == TOK_SCOLON
		|| t->type == TOK_PIPE || t->type == TOK_AMPER);
}

void	clean_operators(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i++);
		if (t && i > 1 && i < tokv->size && isoperator(t) && isoperator(t - 1))
			collapse_at(tokv, i-- - 1);
		else if (i == 1 && isoperator(t))
			collapse_at(tokv, i-- - 1);
		else if (i == tokv->size && isoperator(t))
			collapse_at(tokv, i - 1);
	}
}
