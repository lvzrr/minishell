/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_forbidden.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:46:46 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/24 19:47:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	catch_forbidden(t_vec *tokv)
{
	size_t		i;
	t_tok		*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && t->type == TOK_IDENT && (!ft_strcmp(t->s.data, "if")
				|| !ft_strcmp(t->s.data, "for")
				|| !ft_strcmp(t->s.data, "while")))
		{
			ft_fprintf(2, ANSI_RED"error: "ANSI_RESET"control "
				"expressions aren't supported\n");
			return (false);
		}
		i++;
	}
	if (tokv->size && !isstringtoken(t) && !isredirect(t->type))
	{
		ft_fprintf(2, ANSI_RED"syntax error: "ANSI_RESET
			"expected identifier or redirect as last token\n");
		return (false);
	}
	return (true);
}
