/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_strrchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tstr.h"

char	*ft_tstr_strrchr(const t_string *haystack, int needle)
{
	t_u8	*l_o;
	size_t	s;

	if (!haystack || !haystack->len || !haystack->alloc_size)
		return (NULL);
	l_o = NULL;
	s = haystack->len;
	if (needle == '\0')
		return ((char *)&(haystack->data[s]));
	while (s--)
		if (haystack->data[s] == (char)needle)
			return ((char *)&(haystack->data[s]));
	return ((char *)l_o);
}
