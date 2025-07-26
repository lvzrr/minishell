/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:44:45 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/26 17:45:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	pre_clean(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && t->type == TOK_SPACE && (isoperator(t + 1)
				|| (i > 0 && isoperator(t - 1) && isstringtoken(t + 1))))
		{
			collapse_at(tokv, i);
			continue ;
		}
		if (t && ((isoperator(t) && isoperator(t + 1))
				|| (i > 0 && isoperator(t) && isoperator(t - 1))))
			return (ft_fprintf(2, ANSI_RED"syntax error: "ANSI_RESET
					"consecutive operators are not allowed\n"), false);
		i++;
	}
	return (true);
}

bool	check_interpret(t_tok *t, size_t i)
{
	if (i > 0 && (t - 1)->type == TOK_SPACE && i > 5 && isoperator(t - 5))
		return (false);
	else if (i > 3 && isoperator(t - 4))
		return (false);
	else if (i > 3 && !isoperator(t - 4))
		return (true);
	return (false);
}
