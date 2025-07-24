/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_vec_helpers_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:17:43 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/24 14:17:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	vec_push_indexed(t_vec *a, t_string *b, size_t *idx)
{
	t_vec			c;
	t_tok			newtok;

	newtok = (t_tok){.type = TOK_WRITE_IN, .s = ft_tstr_clone(b)};
	c = ft_vec(a->size + 1, sizeof(t_tok));
	copy_helper(a, &newtok, &c, *idx);
	vec_deep_copy(&c, a, (*idx)++);
	clean_tokenstream(a);
	ft_vec_free(a);
	ft_tstr_clear(b);
	*a = c;
}
