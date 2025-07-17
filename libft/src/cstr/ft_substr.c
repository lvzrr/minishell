/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*out;
	size_t			ls;

	if (!s)
		return (NULL);
	ls = ft_strlen(s);
	if (len == 0 || start >= ls)
		return (ft_strdup(""));
	if (len > ls - start)
		len = ls - start;
	out = ft_alloc(len + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (j < len && s[start])
		out[j++] = s[start++];
	out[j] = 0;
	return (out);
}
