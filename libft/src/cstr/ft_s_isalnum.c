/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:01 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 00:55:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

bool	ft_s_isblob(char *s)
{
	while (*s)
		if (ft_isspace(*s++))
			return (false);
	return (true);
}
