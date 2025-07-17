/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_membroadcast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	ft_membroadcast(void *dst, void *src, size_t chunks, size_t n)
{
	size_t	i;

	if (!dst || !src || !chunks || !n)
		return ;
	i = 0;
	while (i + (2 * chunks) < n)
	{
		ft_memcpy((t_u8 *)dst + i, src, chunks);
		i += chunks;
		ft_memcpy((t_u8 *)dst + i, src, chunks);
		i += chunks;
	}
	while (i < n)
	{
		ft_memcpy((t_u8 *)dst + i, src, chunks);
		i += chunks;
	}
}
