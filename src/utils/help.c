/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:15:54 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:16:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	phelp(void)
{
	ft_printf(ANSI_MAGENTA"mini - a POSIX-like shell\n"ANSI_RESET
		"usage: minish [--debug] [-c 'command']\n\n"
		ANSI_YELLOW"options:\n"ANSI_RESET
		"  --debug          enable verbose debug output"
		" (lexer, parser, heredoc streams)\n"
		"  -c <command>     run a one-liner and exit\n\n"
		ANSI_YELLOW"features:\n"ANSI_RESET
		"  heredoc          supported with << and terminator\n"
		"  token joining    adjacent quoted/unquoted strings merge into one\n"
		"  variable syntax  $var and \"quoted $vars\" resolved\n"
		"  builtins         exit\n"
		"\n");
}
