/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	ft_vec_free(t_vec *v)
{
	void	*tmp;

	if (!v)
		return ;
	tmp = (void *)v->data;
	ft_free(&tmp);
	v->data = NULL;
	v->size = 0;
	v->alloc_size = 0;
	v->sizeof_type = 0;
}
