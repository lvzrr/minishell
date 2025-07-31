/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:04:51 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/27 14:06:14 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	syntax_err(char *msg)
{
	ft_fprintf(2, ANSI_RED"syntax error: "ANSI_RESET
		"%s", msg);
}

void	err(char *msg)
{
	ft_fprintf(2, ANSI_RED"error: "ANSI_RESET
		"%s", msg);
}

void	warn(char *msg)
{
	ft_fprintf(2, ANSI_YELLOW"warning: "ANSI_RESET
		"%s", msg);
}

void	err_file(char *msg, char *fname)
{
	ft_fprintf(2, ANSI_RED"error: "ANSI_RESET
		"'%s': %s", fname, msg);
}
