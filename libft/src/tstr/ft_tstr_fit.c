/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_fit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tstr.h"

void	ft_tstr_fit(t_string *str)
{
	char	*new;

	if (!str || str->len + 1 == str->alloc_size)
		return ;
	new = ft_realloc(str->data, str->alloc_size, str->len + 1);
	if (!new)
		return ;
	str->data = new;
	str->alloc_size = str->len + 1;
}
