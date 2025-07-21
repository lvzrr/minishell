/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_isblob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:54:01 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 03:55:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cstr.h"

bool	ft_s_isblob(char *s)
{
	while (*s)
	{
		if (ft_isspace(*s) || !ft_isalnum(*s))
			return (false);
		s++;
	}
	return (true);
}
