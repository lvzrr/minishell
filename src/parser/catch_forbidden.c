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

/*
*	esto nos deja interpretar export como
*	identificador Y redireccion, pero evitando
*	que se use como comando, por que ya deberia
*	haberlo interpretado post_process.
*/

static bool	check_invalid_export(t_tok *t, size_t i)
{
	return (t && ((i > 0 && isstringtoken(t)
				&& !ft_strcmp("export", t->s.data) && isoperator(t - 1))
			|| (i == 0 && isstringtoken(t)
				&& !ft_strcmp(t->s.data, "export"))));
}

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
			return (ft_fprintf(2, ANSI_RED"error: "ANSI_RESET"control "
					"expressions aren't supported\n"), false);
		else if (check_invalid_export(t, i))
			return (ft_fprintf(2, ANSI_RED"error: "ANSI_RESET"export "
					"not valid in this context\n"), false);
		else if (t && i + 1 < tokv->size && isredirect(t->type)
			&& isstringtoken(t + 1))
			return (ft_fprintf(2, ANSI_RED"error: "ANSI_RESET"redirects "
					"must be followed by another or an operator\n"), false);
		i++;
	}
	if (tokv->size && !isstringtoken(t) && !isredirect(t->type))
		return (ft_fprintf(2, ANSI_RED"syntax error: "ANSI_RESET
				"expected identifier or redirect as last token\n"), false);
	return (true);
}
