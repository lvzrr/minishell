/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	ft_defer(void *p)
{
	ft_free((void **)p);
}

void	ft_defer_arr(void ***p)
{
	ft_free_array((void ***)p);
}
