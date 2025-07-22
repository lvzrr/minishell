/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:18:36 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/22 16:19:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	remove_scaping_singledollar(t_tok *t)
{
	size_t	i;

	i = 0;
	while (i < t->s.len)
	{
		if (i + 1 < t->s.len && t->s.data[i] == '\\'
			&& t->s.data[i + 1] == '$')
			remove_char(&t->s, i);
		i++;
	}
}
