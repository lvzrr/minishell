/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft.h"

inline t_u8	ft_isnumeric(const char *__restrict__ s)
{
	t_u8	has_digit;

	if (!s || !*s)
		return (0);
	has_digit = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			has_digit = 1;
		else if (*s != '-' && *s != '+' && *s != ' ')
			return (0);
		s++;
	}
	return (has_digit);
}
