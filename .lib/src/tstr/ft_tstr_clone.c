/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_clone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tstr.h"

t_string	ft_tstr_clone(t_string *s)
{
	t_string	new;

	if (!s || !s->alloc_size)
		return ((t_string){0});
	new.data = ft_memclone(s->data, s->alloc_size);
	new.len = s->len;
	new.alloc_size = s->alloc_size;
	return (new);
}
