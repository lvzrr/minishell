/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

const void	*ft_vec_get(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}

void	*ft_vec_get_mut(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (raw + (vec->sizeof_type * idx));
}

void	*ft_vec_get_clone(t_vec *vec, size_t idx)
{
	t_u8	*raw;

	if (!vec || !vec->size || idx > vec->size)
		return (NULL);
	raw = (t_u8 *)vec->data;
	return (ft_memclone(raw + (vec->sizeof_type * idx),
			vec->sizeof_type));
}
