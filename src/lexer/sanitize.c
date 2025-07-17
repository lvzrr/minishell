/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:41:07 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 17:41:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"

void	remove_scape(t_string *s, size_t offst)
{
	while (offst < s->len && s->data[offst] != '\\')
		offst++;
	ft_memmove(s->data + offst, s->data + offst + 1, s->len - offst);
	s->data[--s->len] = 0;
}
