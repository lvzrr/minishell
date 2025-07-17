/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*ft_calloc(size_t n, size_t size)
{
	void			*alloc;
	size_t			total;

	total = n * size;
	if (size != 0 && n > SIZE_MAX / size)
		return (0);
	alloc = ft_alloc(total);
	if (!alloc)
		return (NULL);
	ft_memset(alloc, 0, total);
	return (alloc);
}
