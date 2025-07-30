/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:56:38 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/29 18:56:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

size_t	getcmdlen(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i);
		if (!isstringtoken(t))
			break ;
		++i;
	}
	return (i);
}

t_vec	create_redirs(t_tok *t, t_vec *tokv)
{
	t_vec	redir_v;
	t_tok	newtok;

	redir_v = ft_vec(4, sizeof(t_tok));
	while (tokv->size && isredirect(t->type))
	{
		newtok.type = ((t_tok *)tokv->data)[0].type;
		newtok.s = ft_tstr_clone(&((t_tok *)tokv->data)->s);
		collapse_at(tokv, 0);
		ft_vec_push(&redir_v, &newtok, 1);
	}
	return (redir_v);
}
