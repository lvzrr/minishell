/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collapser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:38:30 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/20 17:40:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

static void	free_tok(void *v)
{
	t_tok	*t;

	if (!v)
		return ;
	t = (t_tok *)v;
	ft_tstr_free(&t->s);
}

void	collapse_at(t_vec *tokv, size_t i)
{
	ft_vec_remove_f(tokv, i, free_tok);
}
