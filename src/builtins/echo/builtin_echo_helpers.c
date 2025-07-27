/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:38:37 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 00:38:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	else if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (-1);
}

void	write_hex(char *str, size_t *i, size_t len)
{
	int		val;
	size_t	start;
	size_t	count;

	count = 0;
	start = *i + 2;
	val = 0;
	while (start < len && ft_isxdigit(str[start]) && count < 2)
	{
		val = (val << 4) | hex_char_to_int(str[start++]);
		count++;
	}
	if (count > 0)
		write(1, &((char){val}), 1);
	*i = start;
}

void	write_oct(char *str, size_t *i, size_t len)
{
	int		val;
	size_t	start;
	size_t	count;

	val = 0;
	start = *i + 1;
	count = 0;
	while (start < len && str[start] >= '0' && str[start] <= '7' && count < 3)
	{
		val = (val << 3) | (str[start] - '0');
		start++;
		count++;
	}
	if (count > 0)
		write(1, &((char){val}), 1);
	*i = start;
}

bool	manage_scape(char *string, size_t *i, size_t len)
{
	if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'a')
		(write(1, "\a", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'b')
		(write(1, "\b", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'c')
		return (true);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'n')
		(write(1, "\n", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'r')
		(write(1, "\r", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 't')
		(write(1, "\t", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'v')
		(write(1, "\v", 1), *i += 2);
	else if (*i + 1 < len && string[*i] == '\\' && string[*i + 1] == 'x')
		write_hex(string, i, len);
	else if (string[*i] == '\\' && *i + 1 < len && string[*i + 1] >= '0'
		&& string[*i + 1] <= '7')
		write_oct(string, i, len);
	else
		write(1, "\\", 1);
	return (false);
}
