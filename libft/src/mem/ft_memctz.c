/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memctz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

FT_INLINE_HOT inline t_u8	ft_memctz_u32(t_u32 x)
{
	t_u8	c;

	c = 0;
	if (x == 0)
		return (32);
	while (!(x & 0xF))
	{
		c += 4;
		x >>= 4;
	}
	while (!(x & 0x3))
	{
		c += 2;
		x >>= 2;
	}
	while (!(x & 1))
	{
		c++;
		x >>= 1;
	}
	return (c);
}

FT_INLINE_HOT inline t_u8	ft_memctz_u64(t_u64 x)
{
	t_u8	c;

	c = 0;
	if (x == 0)
		return (32);
	while (!(x & 0xF))
	{
		c += 4;
		x >>= 4;
	}
	while (!(x & 0x3))
	{
		c += 2;
		x >>= 2;
	}
	while (!(x & 1))
	{
		c++;
		x >>= 1;
	}
	return (c);
}

FT_INLINE_HOT inline t_u8	ft_memctz_u128(t_u128 x)
{
	t_u8	c;

	c = 0;
	if (x == 0)
		return (32);
	while (!(x & 0xF))
	{
		c += 4;
		x >>= 4;
	}
	while (!(x & 0x3))
	{
		c += 2;
		x >>= 2;
	}
	while (!(x & 1))
	{
		c++;
		x >>= 1;
	}
	return (c);
}
