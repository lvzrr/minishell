/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	return (ft_memcmp((void *)s1, (void *)s2, n));
}
