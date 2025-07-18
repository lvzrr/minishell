/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_vec_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:48:26 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 19:48:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

bool	check_vec_eq(t_vec *a, t_vec *b)
{
	size_t	i;
	t_tok	*t1;
	t_tok	*t2;

	if (a == b)
		return (true);
	if ((!a && b) || (a && !b))
		return (false);
	i = 0;
	while (i + 1 < a->size)
	{
		t1 = (t_tok *)ft_vec_get(a, i);
		t2 = (t_tok *)ft_vec_get(b, i);
		if (t1->type != t2->type)
			return (false);
		if (ft_strcmp(t1->s.data, t2->s.data))
			return (false);
		i++;
	}
	return (true);
}

void	vec_push_tokens(t_vec *a, t_vec *b)
{
	size_t	i;
	t_tok	t;

	i = 0;
	while (i < b->size)
	{
		t = *((t_tok *)ft_vec_get(b, i));
		t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(b, i))->s);
		ft_vec_push(a, &t, 1);
		i++;
	}
}

void	vec_push_tokens_from(t_vec *a, t_vec *b, size_t w)
{
	size_t	i;
	t_tok	t;

	i = w;
	while (i < b->size)
	{
		t = *((t_tok *)ft_vec_get(b, i));
		t.s = ft_tstr_clone(&((t_tok *)ft_vec_get(b, i))->s);
		ft_tstr_free(&((t_tok *)ft_vec_get(b, i))->s);
		ft_vec_push(a, &t, 1);
		i++;
	}
}
